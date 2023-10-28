#include <iostream>
using namespace std;

/*
	1. The class template std::promise provides a facility to store a value or an exception that is later acquired asynchronously via a std::future object created by the std::promise object. Note that the std::promise object is meant to be used only once.

	2. Each promise is associated with a shared state, which contains some state information and a result which may be not yet evaluated, evaluated to a value (possibly void) or evaluated to an exception.

	3. This example shows how promise<int> can be used as signals between threads.
*/

#include <chrono>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

//1.
void accumulate_func(std::vector<int>::iterator first,
	std::vector<int>::iterator last,
	std::promise<int>&& accumulate_promise) // also OK , std::promise<int> accumulate_promise
{
	int sum = std::accumulate(first, last, 0);
	accumulate_promise.set_value(sum); // Notify future
}

void run_promise()
{
	// Demonstrate using promise<int> to transmit a result between threads.
	std::vector<int> numbers = { 1, 2, 3, };
	std::promise<int> accumulate_promise;
	std::future<int> accumulate_future = accumulate_promise.get_future();
	std::thread work_thread(accumulate_func,
		numbers.begin(),
		numbers.end(),
		std::move(accumulate_promise));

	// future::get() will wait until the future has a valid result and retrieves it.
	// Calling wait() before get() is not needed
	// accumulate_future.wait(); // wait for result

	std::cout << "result=" << accumulate_future.get() << '\n';
	work_thread.join(); // wait for thread completion


	/*
		result=6
	*/
}

//2.
void do_work(std::promise<void> barrier)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	barrier.set_value();
}
void run_promise_as_signal() {
	// Demonstrate using promise<void> to signal state between threads.
	std::promise<void> barrier;
	std::future<void> barrier_future = barrier.get_future();
	std::thread new_work_thread(do_work, std::move(barrier));
	barrier_future.wait();
	new_work_thread.join();
}

//void main()
//{
//	run_promise_as_signal();
//  run_promise();
//}