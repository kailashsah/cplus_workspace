#include <iostream>
using namespace std;

/*
	1. atomic.wait()

	2. Performs atomic waiting operations. Behaves as if it repeatedly performs the following steps:

		Compare the value representation of this->load(order) with that of old.
		If those are equal, then blocks until *this is notified by notify_one() or notify_all(), or the thread is unblocked spuriously.
		Otherwise, returns.

	3. The comparison is bitwise (similar to std::memcmp); no comparison operator is used. Padding bits that never participate in an object's value representation are ignored.

	4. notify_all()
		Performs atomic notifying operations.

		Unblocks all threads blocked in atomic waiting operations (i.e. wait()) on *this, if there are any; otherwise does nothing.

*/
void run_atomic_wait();
//
#include <atomic>
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

using namespace std::literals;

void run_atomic_wait() {
	std::atomic<bool> all_tasks_completed{ false };
	std::atomic<unsigned> completion_count{};
	std::future<void> task_futures[16];
	std::atomic<unsigned> outstanding_task_count{ 16 };

	// Spawn several tasks which take different amounts of
	// time, then decrement the outstanding task count.
	for (std::future<void>& task_future : task_futures)
		task_future = std::async([&]
			{
				// This sleep represents doing real work...
				std::this_thread::sleep_for(50ms);

				++completion_count;
				--outstanding_task_count;

				// When the task count falls to zero, notify
				// the waiter (main thread in this case).
				if (outstanding_task_count.load() == 0)
				{
					all_tasks_completed = true;
					all_tasks_completed.notify_one();
				}
			});

	all_tasks_completed.wait(false);

	std::cout << "Tasks completed = " << completion_count.load() << '\n';
}

//int main()
//{
//	run_atomic_wait();
//}

/*
	Tasks completed = 16
*/

