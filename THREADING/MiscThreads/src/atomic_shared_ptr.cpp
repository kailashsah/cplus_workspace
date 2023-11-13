#include <iostream>
using namespace std;

/*
	1. std::shared_ptr requires special attention in a multithreading environment. They are very special. They are the only non-atomic data types in C++ for which atomic operations exist.


*/
#include <thread>
#include <syncstream>
atomic_int at_val = 2014;
void run_atomic_shared_ptr_111() {
	std::shared_ptr<int> ptr = std::make_shared<int>(2011);

	for (auto i = 0; i < 10; i++) {
		std::thread([ptr] {                             //(1)
			std::shared_ptr<int> localPtr(ptr);         //(2)
			localPtr = std::make_shared<int>(at_val);     //(3)
			at_val++;

			osyncstream os{ cout };
			os << *localPtr.get() << endl;
			}).detach();
	}

}
void run_atomic_shared_ptr_222() {
	std::shared_ptr<int> ptr = std::make_shared<int>(2011);

	for (auto i = 0; i < 10; i++) {
		std::thread([&ptr] {                         //(1)
			ptr = std::make_shared<int>(at_val);     //  (2)
			at_val++;

			osyncstream os{ cout };
			os << *ptr.get() << endl;
			}).detach();
	}

}

void run_atomic_shared_ptr() {
	//run_atomic_shared_ptr_111();
	run_atomic_shared_ptr_222();
	this_thread::sleep_for(4s);

}

int main()
{
	run_atomic_shared_ptr();
}

