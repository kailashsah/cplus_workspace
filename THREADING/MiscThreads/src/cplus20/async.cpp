#include <iostream>
using namespace std;

/*
	1. std::launch::async : the task is executed on a different thread, potentially by creatingand launching it first
		std::launch::deferred : the task is executed on the calling thread the first time its result is requested(lazy evaluation)
	
	2. promise<> - The class template std::promise provides a facility to store a value or an exception that is later acquired asynchronously via a std::future object created by the std::promise object. Note that the std::promise object is meant to be used only once.
		2.1.  Each promise is associated with a shared state, which contains some state information and a result which may be not yet evaluated, evaluated to a value (possibly void) or evaluated to an exception

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

void main()
{
	run_async();
	run_by_promise();
}