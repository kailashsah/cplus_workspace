#include <iostream>
using namespace std;

/*
	1. atomic<shared_ptr<int>>

	2. constructs
		std::atomic<std::shared_ptr<int>> a{};	// 1
		std::atomic<std::shared_ptr<int>> b{a.load()};	// 2
		std::atomic<std::shared_ptr<int>> c{b};	// 3, error // b is not shared_ptr, it is atomic
*/

void run_atomic_shared_ptr();
void run_shared_ptr_without_atomic();
//
#include <thread>

//1.
std::atomic<std::shared_ptr<int>> ptr{ std::make_shared<int>(0) }; // global
void run_atomic_shared_ptr() {	
	
	uint32_t maxThread{ std::thread::hardware_concurrency() };

	std::cout << maxThread << " max threads in your system." << std::endl; // 4 max threads

	this_thread::sleep_for(3s); // to see the above output
	for (int i = 0; i < maxThread; ++i) {
		std::thread([] {
			//for (int j = 0; j < 20'00'000; ++j) { // Optional single quotes(') may be inserted between the digits as a separator. They are ignored by the compiler.
				for (int j = 0; j < 10; ++j) {
				ptr = std::make_shared<int>(*ptr.load() + 1);
				
				cout << *ptr.load().get() << endl; // ptr.load().get() gives you address.
			}
			}).join();
	}

	std::cout << *ptr.load() << std::endl; //40 if loop 10 is given

}

//2.
std::shared_ptr<int> ptrr{ std::make_shared<int>(0) };
void run_shared_ptr_without_atomic() {
	// without atomic also it works fine, reason given below.
	uint32_t maxThread{ std::thread::hardware_concurrency() };

	std::cout << maxThread << " max threads in your system." << std::endl; // 4 max threads

	this_thread::sleep_for(3s); // to see the above output
	for (int i = 0; i < maxThread; ++i) {
		std::thread([] {
			
			for (int j = 0; j < 10; ++j) {
				ptrr = std::make_shared<int>(*ptrr.get() + 1); //bcoz thread safe

				cout << *ptrr.get() << endl; 
			}
			}).join();
	}

	std::cout << *ptrr << std::endl; //40 if loop 10 is given
}

//int main() {
//	run_atomic_shared_ptr();
//	//run_shared_ptr_without_atomic();
//}

/*
	...
	39991
	39992
	39993
	39994
	39995
	39996
	39997
	39998
	39999
	40000
	40000
*/
