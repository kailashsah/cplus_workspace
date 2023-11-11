#include <iostream>
using namespace std;

/*
	1. jthread - advantage that it can be used to stop a thread by releasing resources

	2. A std::jthread instance represents an automatically joining and cooperatively cancellable thread. std::jthread has an exception-safe thread termination flow compared to std::thread and can replace it in most situations with little or no code changes  .
*/

#include <thread>
void comparison() {

	//1.
	{  // Block 
	 //std::thread
		std::thread t([]() {
			std::this_thread::sleep_for(1s);
			});

		//Must be joined explicitly (unless detached).
		//Otherwise t.~thread() calls std::terminate()
		t.join();
	}

	//2.
	{
		//std::jthread
		std::jthread jt([]() {
			std::this_thread::sleep_for(1s);
			});
		//Joins automatically in jt.~jthread()
	}
}