#include <iostream>
using namespace std;

/*
	1. two additional functions
		try_lock_for: Tries to lock till timeout occurs
		try_lock_until: Tries to lock till specified amount of time.

	2. When you use try_lock_for() to lock a mutex, then the second thread [T2] will wait for that amount of time for the first thread [T1] to be unlocked. If it reaches the T2 thread reaches the timeout, then it will simply return.

	3. In try_lock_until(), we wait from current time till the time mentioned. If the timeout occurs it will return false.


*/
void run_try_lock_for();
void run_try_lock_until();
//
#include <iostream>       // std::cout
#include <chrono>         // std::chrono::milliseconds
#include <thread>         // std::thread
#include <mutex>          // std::timed_mutex

// for more tutorials visit www.ProDeveloperTutorial.com

using namespace std;

std::timed_mutex mtx;

int count_num = 0;

void update_value(int i)
{
	//created a try_lock_for mutex
	if (mtx.try_lock_for(std::chrono::seconds(2)))
	{
		count_num++;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		cout << "Thread " << i << " acquired lock" << endl;
		mtx.unlock();
		cout << "Thread unlocked" << endl;
	}
	else
	{
		cout << "Thread " << i << " was not able to acquire lock" << endl;

	}

}
/*
	if 4 seconds in try_lock_for()
		Thread 1 acquired lock
		Thread unlocked
		Thread 2 acquired lock
		Thread unlocked
	if 2 seconds in try_lock_for()
		Thread 1 was not able to acquire lock
		Thread 2 acquired lock
		Thread unlocked

*/
void run_try_lock_for() {
	std::thread t1(update_value, 1);
	std::thread t2(update_value, 2);

	t1.join();
	t2.join();

}
void update_value_v2(int i)
{
	auto now = std::chrono::steady_clock::now();

	//created a try_lock_until mutex
	if (mtx.try_lock_until(now + std::chrono::seconds(2)))
	{
		count_num++;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		cout << "Thread " << i << " acquired lock" << endl;
		mtx.unlock();
		cout << "Thread unlocked" << endl;

	}
	else
	{
		cout << "Thread " << i << " was not able to acquire lock" << endl;

	}
	/*
		if 2 seconds in try_lock_until()
			Thread 1 acquired lock
			Thread unlocked
			Thread 2 acquired lock
			Thread unlocked
	*/

}
void run_try_lock_until() {
	std::thread t1(update_value_v2, 1);
	std::thread t2(update_value_v2, 2);

	t1.join();
	t2.join();

}

//int main()
//{
//	//run_try_lock_for();
//	run_try_lock_until();
//
//	return 0;
//}


