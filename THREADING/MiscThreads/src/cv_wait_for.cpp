#include <iostream>
using namespace std;

/*
	1.

*/

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>

void waits(int idx);
void signals();
//
using namespace std::chrono_literals;
std::condition_variable cv;
std::mutex cv_mutex;
int g_i;

void waits(int idx)
{
	std::unique_lock<std::mutex> lk(cv_mutex);
	/*
		auto now = std::chrono::system_clock::now();
		if (cv.wait_until(lk, now + idx*100ms, [](){ return i == 1; }))
	*/
	if (cv.wait_for(lk, idx * 100ms, [] { return g_i == 1; }))
		std::cerr << "Thread " << idx << " finished waiting. i == " << g_i << '\n';
	else
		std::cerr << "Thread " << idx << " timed out. i == " << g_i << '\n';
}

void signals()
{
	std::this_thread::sleep_for(120ms);
	std::cerr << "Notifying...\n";
	cv.notify_all();
	std::this_thread::sleep_for(100ms);
	{
		std::lock_guard<std::mutex> lk(cv_mutex);
		g_i = 1;
	}
	std::cerr << "Notifying again...\n";
	cv.notify_all();
}

void run_wait_for() {
	std::thread t1(waits, 1), t2(waits, 2), t3(waits, 3), t4(signals);
	t1.join();
	t2.join();
	t3.join();
	t4.join();

}

//void main()
//{
//	run_wait_for();
//}

/*
	Thread 1 timed out. i == 0
	Notifying...
	Thread 2 timed out. i == 0
	Notifying again...
	Thread 3 finished waiting. i == 1
*/