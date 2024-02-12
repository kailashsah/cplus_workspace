#include <iostream>
using namespace std;

/*
	1. std::this_thread::sleep_for()

			will make your thread sleep for a given time (the thread is stopped for a given time).

		std::this_thread::yield()

			will stop the execution of the current thread and give priority to other process/threads (if there are other process/threads waiting in the queue). The execution of the thread is not stopped. (it just release the CPU).

	2. yield() - Provides a hint to the implementation to reschedule the execution of threads, allowing other threads to run.
		The exact behavior of this function depends on the implementation, in particular on the mechanics of the OS scheduler in use and the state of the system. For example, a first-in-first-out realtime scheduler (SCHED_FIFO in Linux) would suspend the current thread and put it on the back of the queue of the same-priority threads that are ready to run (and if there are no other threads at the same priority, yield has no effect).



*/
void run_yield();
//
#include <chrono>
#include <iostream>
#include <thread>

// "busy sleep" while suggesting that other threads run 
// for a small amount of time
void little_sleep(std::chrono::microseconds us)
{
	auto start = std::chrono::high_resolution_clock::now();
	auto end = start + us;
	do
	{
		std::this_thread::yield();
	} while (std::chrono::high_resolution_clock::now() < end);
}

void run_yield() {
	auto start = std::chrono::high_resolution_clock::now();

	little_sleep(std::chrono::microseconds(100));

	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	std::cout << "waited for "
		<< std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()
		<< " microseconds\n";
}
/*
	waited for 222 microseconds
*/

//int main()
//{
//	run_yield();
//}


