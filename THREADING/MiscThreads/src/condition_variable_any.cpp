#include <iostream>
using namespace std;
/*
	1. The condition_variable_any class is a generalization of std::condition_variable. Whereas std::condition_variable works only on std::unique_lock<std::mutex>, condition_variable_any can operate on any lock that meets the BasicLockable requirements.

	2. If the lock is std::unique_lock, std::condition_variable may provide better performance.

		std::condition_variable_any can be used with std::shared_lock in order to wait on a std::shared_mutex in shared ownership mode.

	3. A possible use for std::condition_variable_any with custom Lockable types is to provide convenient interruptible waits.
*/
#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>

std::condition_variable_any cv_any;
std::mutex cv_mutt; // This mutex is used for three purposes:
				 // 1) to synchronize accesses to i
				 // 2) to synchronize accesses to std::cerr
				 // 3) for the condition variable cv
int ii = 0;

void waitss()
{
	std::unique_lock<std::mutex> lk(cv_mutt);
	std::cerr << "Waiting... \n";
	cv_any.wait(lk, [] {return ii == 1; });
	std::cerr << "...finished waiting. i == 1\n";
}

void signalss()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	{
		std::lock_guard<std::mutex> lk(cv_mutt);
		std::cerr << "Notifying...\n";
	}
	cv_any.notify_all();

	std::this_thread::sleep_for(std::chrono::seconds(1));

	{
		std::lock_guard<std::mutex> lk(cv_mutt);
		ii = 1;
		std::cerr << "Notifying again...\n";
	}
	cv_any.notify_all();
}


void run_condition_variable_any() {

	std::thread t1(waitss), t2(waitss), t3(waitss), t4(signalss);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}
/*
	Waiting...
	Waiting...
	Waiting...
	Notifying...
	Notifying again...
	...finished waiting. i == 1
	...finished waiting. i == 1
	...finished waiting. i == 1
*/


//int main()
//{
//	run_condition_variable_any();
//}

