#include <iostream>
using namespace std;

/*
	1. std::jthread utilizes the C++20 cooperative cancellation model. It creates and owns a std::stop_source. If initialized with a function that accepts a std::stop_token, std::jthread gets a stop token from its stop source and passes it to the function.

	2. A std::jthread's top-level function doesn't have to take a stop token, but a long-running thread should always have the means to honor a cancellation request. Here is an example of std::jthread cancellation:

	3. There are two points worth noting here. 
		One, it doesn't seem to be specified whether std::jthread constructor initializes a stop-state or not if the passed function does not take a std::stop_token. 
		Two, std::jthread cannot be initialized with an external std::stop_source. These points could be important in some cases because they can affect the application design.
	
	4. https://www.nextptr.com/tutorial/ta1588653702/stdjthread-and-cooperative-cancellation-with-stop-token

*/
#include <thread>

//1.
void jthread_cancel() {
	using namespace std::literals::chrono_literals;

	//Lambda takes a stop token
	std::jthread jt_first([](std::stop_token stoken) {
		cout << "jthread started first." << endl;
		while (!stoken.stop_requested()) {
			//Working...
			std::this_thread::sleep_for(1s);
		}
		cout << "jthread exited first:" << this_thread::get_id() << endl;
		});

	std::jthread jt_second([](std::stop_token stoken) {
		cout << "jthread started second."  << endl;
		while (!stoken.stop_requested()) {
			//Working...
			std::this_thread::sleep_for(1s);
		}
		cout << "jthread exited:" << this_thread::get_id() << endl;
		});
	
	std::this_thread::sleep_for(2s);
	//Thread is stopped and joined in jt.~jthread() here

	/*
		jthread started first.jthread started second.

		jthread exited:20788
		jthread exited first:12352
	*/
}

//2. this thread is blocking, doesn't return from func() .. case of without "stop_token" class
void jthread_cancel_indefinite_call() {
	using namespace std::literals::chrono_literals;

	std::jthread jt([]() {
		while (true) {
			//Working...
			std::this_thread::sleep_for(1s);
		}
		});

	std::this_thread::sleep_for(2s);
}

//int main()
//{
//	jthread_cancel();
//	//jthread_cancel_indefinite_call();
//	return 1;
//}