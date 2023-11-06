#include <iostream>
using namespace std;

/*
	1. Locks all the objects passed as arguments, alternative is std::scoped_lock.

	2. The function locks the objects using an unspecified sequence of calls to their members lock, try_lock and unlock that ensures that all arguments are locked on return (without producing any deadlocks).

		If the function cannot lock all objects (such as because one of its internal calls threw an exception), the function first unlocks all objects it successfully locked (if any) before failing.

	3. try_lock() - true if the function succeeds in locking the mutex for the thread.
		false otherwise. Attempts to lock the mutex, without blocking. The mutex object is accessed/modified as an atomic operation

	4.  raii vesion is std::scoped_lock
*/

#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::lock

std::mutex foo, bar;

void task_a() {
	// foo.lock(); bar.lock(); // replaced by: // also this causes deadlock if one mem locked here & another somewhere.
	std::lock(foo, bar); // this way no deadlocks // for 2 or more mutexes
	std::cout << "task a\n";
	foo.unlock();
	bar.unlock();
}

void task_b() {
	// bar.lock(); foo.lock(); // replaced by:
	std::lock(bar, foo);
	std::cout << "task b\n";
	bar.unlock();
	foo.unlock();
}

void run_lock()
{
	std::thread th1(task_a);
	std::thread th2(task_b);

	th1.join();
	th2.join();
}


//int main()
//{
//	run_lock();
//	return 1;
//}