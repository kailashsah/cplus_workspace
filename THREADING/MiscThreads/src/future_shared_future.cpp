#include <iostream>
using namespace std;

/*
	1. The class template std::shared_future provides a mechanism to access the result of asynchronous operations, similar to std::future, except that multiple threads are "allowed to wait" for the same shared state.
		1.1 Unlike std::future, which is only moveable (so only one instance can refer to any particular asynchronous result), std::shared_future is copyable and multiple shared future objects may refer to the same shared state.

		1.2 Access to the same shared state from multiple threads is safe if each thread does it through its own copy of a shared_future object.

	2. A shared_future may be used to signal multiple threads simultaneously, similar to std::condition_variable::notify_all().

*/


#include <chrono>
#include <future>
#include <iostream>

void run_shared_future()
{
	std::promise<void> ready_promise, t1_ready_promise, t2_ready_promise;
	std::shared_future<void> ready_future(ready_promise.get_future());

	std::chrono::time_point<std::chrono::high_resolution_clock> start;

	auto fun1 = [&, ready_future]() -> std::chrono::duration<double, std::milli>
	{
		t1_ready_promise.set_value();
		ready_future.wait(); // waits for the signal from main()
		return std::chrono::high_resolution_clock::now() - start;
	};


	auto fun2 = [&, ready_future]() -> std::chrono::duration<double, std::milli>
	{
		t2_ready_promise.set_value();
		ready_future.wait(); // waits for the signal from main()
		return std::chrono::high_resolution_clock::now() - start;
	};

	auto fut1 = t1_ready_promise.get_future();
	auto fut2 = t2_ready_promise.get_future();

	auto result1 = std::async(std::launch::async, fun1);
	auto result2 = std::async(std::launch::async, fun2);

	// wait for the threads to become ready
	fut1.wait();
	fut2.wait();

	// the threads are ready, start the clock
	start = std::chrono::high_resolution_clock::now();

	// signal the threads to go
	ready_promise.set_value(); // it notifies shared_future<>.wait()

	std::cout << "Thread 1 received the signal "
		<< result1.get().count() << " ms after start\n"
		<< "Thread 2 received the signal "
		<< result2.get().count() << " ms after start\n";

	/*
		Thread 1 received the signal 0.072 ms after start
		Thread 2 received the signal 0.041 ms after start
	*/
}