#include <iostream>
using namespace std;

/*
	1. Latches and barriers are coordination types that enable some threads to wait until a counter becomes zero. You can use a std::latch only once, but you can use a std::barrier more than once.

	2. latch - single-use thread barrier

	3. For some reasons to pause threatd, there could be a better approach, like C++20 latch/semaphore/barrier.

*/
void run_latch();
//
#include <iostream>
#include <mutex>
#include <latch>
#include <thread>

std::latch workDone(6);
std::latch goHome(1);                                       // (4)

std::mutex coutMutex;

void synchronizedOut(const std::string s) {                // (1)
	std::lock_guard<std::mutex> lo(coutMutex);
	std::cout << s;
}

class Worker {
public:
	Worker(std::string n) : name(n) { };

	void operator() () {
		// notify the boss when work is done
		synchronizedOut(name + ": " + "Work done!\n");
		workDone.count_down();                          // (2)

		// waiting before going home
		goHome.wait();                                  // (5)
		synchronizedOut(name + ": " + "Good bye!\n");
	}
private:
	std::string name;
};

void run_latch() {

	std::cout << '\n';

	std::cout << "BOSS: START WORKING! " << '\n';

	Worker herb("  Herb");
	std::thread herbWork(herb);

	Worker scott("    Scott");
	std::thread scottWork(scott);

	Worker bjarne("      Bjarne");
	std::thread bjarneWork(bjarne);

	Worker andrei("        Andrei");
	std::thread andreiWork(andrei);

	Worker andrew("          Andrew");
	std::thread andrewWork(andrew);

	Worker david("            David");
	std::thread davidWork(david);

	workDone.wait();                                       // (3)

	std::cout << '\n';

	goHome.count_down();

	std::cout << "BOSS: GO HOME!" << '\n';

	herbWork.join();
	scottWork.join();
	bjarneWork.join();
	andreiWork.join();
	andrewWork.join();
	davidWork.join();

}

//int main() {
//	run_latch();
//
//}

/*
The idea of the workflow is straightforward. The six workers herb, scott, bjarne, andrei, andrew, and david in the main-program have to fulfill their job. When they finished their job, they count down the std::latch workDone (2). The boss (main-thread) is blocked in line (3) until the counter becomes 0. When the counter is 0, the boss uses the second std::latch goHome to signal its workers to go home. In this case, the initial counter is 1 (4). The call goHome.wait (5) blocks until the counter becomes 0.

	BOSS: START WORKING!
		Scott: Work done!
	  Herb: Work done!
			Andrei: Work done!
		  Bjarne: Work done!
				David: Work done!
			  Andrew: Work done!

	BOSS: GO HOME!            David: Good bye!

		  Bjarne: Good bye!
			Andrei: Good bye!
	  Herb: Good bye!
		Scott: Good bye!
			  Andrew: Good bye!

*/