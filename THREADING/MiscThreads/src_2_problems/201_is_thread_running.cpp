#include <iostream>
using namespace std;

/*
	1.	use of if (status == std::future_status::ready) 
*/

#include <future>
#include <thread>
#include <chrono>
#include <iostream>

class X {};
void run_async() {
	using namespace std::chrono_literals;

	/* Run some task on new thread. The launch policy std::launch::async
	   makes sure that the task is run asynchronously on a new thread. */
	auto future = std::async(std::launch::async, [] {
		std::this_thread::sleep_for(1s);
		//return 8;     // (1)
		return new X;   // (2)
		});

	// Use wait_for() with zero milliseconds to check thread status.
	auto status = future.wait_for(0ms);

	// Print status.
	if (status == std::future_status::ready) {
		std::cout << "Thread finished" << std::endl;
	}
	else {
		std::cout << "Thread still running" << std::endl;
	}

	auto result = future.get(); // Get result. // it takes the time here, rest of the stmts return immediatly
	cout << typeid(result).name() << endl; //class X *
}

void run_by_promise() {
	using namespace std::chrono_literals;

	// Create a promise and get its future.
	std::promise<bool> prom;
	auto future = prom.get_future();

	//1. 
	// Run some task on a new thread.
	std::thread t([&prom] {
		std::this_thread::sleep_for(1s);
		prom.set_value(true); // Is done atomically.
		});

	// Get thread status using wait_for as before.
	auto status = future.wait_for(0ms);

	// Print status.
	if (status == std::future_status::ready) {
		std::cout << "Thread finished" << std::endl;
	}
	else {
		std::cout << "Thread still running" << std::endl;
	}

	//2. if used second time same promise
	//auto future1 = prom.get_future(); // std::future_error
	std::thread t1([&prom] {
		std::this_thread::sleep_for(1s);
		prom.set_value(true); // Is done atomically.
		});

	auto result = future.get(); // OK. rest of the code ran fine for second time

	// ending
	t.join(); // Join thread.
}

//void main()
//{
//	run_async();
//	run_by_promise();
//}

