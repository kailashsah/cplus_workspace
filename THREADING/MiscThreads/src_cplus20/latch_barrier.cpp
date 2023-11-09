#include <iostream>
using namespace std;

/*
	1. A std::latch is useful for managing one task by multiple threads;
		a std::barrier helps manage repeated tasks by multiple threads.

	2. https://www.modernescpp.com/index.php/barriers-in-c-20/

	3. Similar to a std::latch, the barrier is initialized with a counter; however, unlike std::latch, the barrier is re-usable and, on top of that, will call an optional completion function before unblocking the waiting threads.

	4. arrive_and_drop() - Decrements the initial expected count for all subsequent phases by one, and then decrements the expected count for the current phase by one.

		This function is executed atomically. The call to this function strongly happens-before the start of the phase completion step for the current phase.
*/


#include <iostream> 
#include <barrier>
#include <mutex>
#include <string>
#include <thread>

std::barrier work_done_barrier(6);
std::mutex cout_mutex_1;

void print(const std::string& s) noexcept {
	std::lock_guard<std::mutex> lo(cout_mutex_1);
	std::cout << s;
}

class FullTimeWorkerr {                                                   // (1)
public:
	FullTimeWorkerr(std::string n) : name(n) { };

	void operator() () {
		print(name + ": " + "Morning work done!\n");
		work_done_barrier.arrive_and_wait();  // Wait until morning work is done     (3)

		print(name + ": " + "Afternoon work done!\n");
		work_done_barrier.arrive_and_wait();  // Wait until afternoon work is done   (4)

	}
private:
	std::string name;
};

class PartTimeWorker {                                                   // (2)
public:
	PartTimeWorker(std::string n) : name(n) { };

	void operator() () {
		print(name + ": " + "Morning work done!\n");
		work_done_barrier.arrive_and_drop();  // Wait until morning work is done  // (5)
	}
private:
	std::string name;
};

void run_barrier() {
	std::cout << '\n';

	FullTimeWorkerr herb("  Herb");
	std::thread herbWork(herb);

	FullTimeWorkerr scott("    Scott");
	std::thread scottWork(scott);

	FullTimeWorkerr bjarne("      Bjarne");
	std::thread bjarneWork(bjarne);

	PartTimeWorker andrei("        Andrei");
	std::thread andreiWork(andrei);

	PartTimeWorker andrew("          Andrew");
	std::thread andrewWork(andrew);

	PartTimeWorker david("            David");
	std::thread davidWork(david);

	herbWork.join();
	scottWork.join();
	bjarneWork.join();
	andreiWork.join();
	andrewWork.join();
	davidWork.join();
}

//int main() {
//    run_barrier();
//}

/*
	This workflow consists of two kinds of workers: full-time workers (1) and part-time workers (2). The part-time worker works in the morning, and the full-time worker in the morning and the afternoon. Consequently, the full-time workers call workDone.arrive_and_wait() (lines (3) and (4)) two times. On the contrary, part-time works call workDone.arrive_and_drop() (5) only once. This workDone.arrive_and_drop() call causes the part-time worker to skip the afternoon work. 
	
	Accordingly, the counter has in the first phase (morning) the value 6, and in the second phase (afternoon) the value 3.

		  Bjarne: Morning work done!
  Herb: Morning work done!
	Scott: Morning work done!
			David: Morning work done!  (part-time)
		  Andrew: Morning work done! (part-time)
		Andrei: Morning work done! (part-time)
	Scott: Afternoon work done!
  Herb: Afternoon work done!
	  Bjarne: Afternoon work done!

*/