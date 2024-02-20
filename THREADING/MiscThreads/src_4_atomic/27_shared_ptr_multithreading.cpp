#include <iostream>
using namespace std;

/*
	1. Why we need atomic functions for shared_ptr.

	1. std::shared_ptr requires special attention in a multithreading environment. They are very special. They are the only non-atomic data types in C++ for which atomic operations exist.

	2. There are specializations for the atomic operations load, store, compare and exchange for a std::shared_ptr.  By using the explicit variant, you can even specify the memory model.

	3. https://www.modernescpp.com/index.php/atomic-smart-pointers/
		https://stackoverflow.com/questions/40223599/what-is-the-difference-between-stdshared-ptr-and-stdatomicstdshared-ptr
*/
void run_atomic_shared_ptr_with_copy();
void run_atomic_shared_ptr_with_reference();
void run_atomic_shared_ptr_fix();
//
#include <thread>
#include <syncstream>
atomic_int at_val = 2014;
void run_atomic_shared_ptr_with_copy() {
	std::shared_ptr<int> ptr = std::make_shared<int>(2011);

	for (auto i = 0; i < 10; i++) {
		std::thread([ptr] {                             //(1)
			std::shared_ptr<int> localPtr(ptr);         //(2) only mutates the control block 
			localPtr = std::make_shared<int>(at_val);   //(3)
			at_val++;

			osyncstream os{ cout };
			os << *localPtr.get() << endl;
			}).detach();
	}
	/*
		At first to (2). By using copy construction for the std::shared_ptr localPtr, only the control block is used. That is thread-safe. 
		(3) is a little bit more interesting.  localPtr  (3) is set to a new  std::shared_ptr. This is from the multithreading point of view, no problem.
		
		lambda-function (1) binds ptr by copy. Therefore, the modification of localPtr takes place on a copy.
	*/

}
void run_atomic_shared_ptr_with_reference() {
	std::shared_ptr<int> ptr = std::make_shared<int>(2011);

	for (auto i = 0; i < 10; i++) {
		std::thread([&ptr] {                         //(1)
			ptr = std::make_shared<int>(at_val);     //(2) race condition
			at_val++;

			osyncstream os{ cout };
			os << *ptr.get() << endl;
			}).detach();
	}
	/*
		1. The lambda function binds the std::shared_ptr ptr by reference (1). Therefore assignment (2) is a race condition on the resource, and the program has undefined behavior.

		2. Here, we are mutating the control block (which is ok) but also the shared pointer itself, by making it point to a different values from multiple threads. This is not ok.

			A solution to that problem is to wrap the shared_ptr with a lock, but this solution is not so scalable under some contention, and in a sense, loses the automatic feeling of the standard shared pointer.

		3. This is where atomic shared pointer comes to play. You can mutate the shared pointer from multiple threads without fearing a data race and without using any locks.
	*/
}

void run_atomic_shared_ptr_fix() {

	std::shared_ptr<int> ptr = std::make_shared<int>(2011);

	for (auto i = 0; i < 10; i++) {
		std::thread([&ptr] {
			auto localPtr = std::make_shared<int>(2014);
			std::atomic_store(&ptr, localPtr);            //(1) thread safe
			}).detach();
	}
}

void run_atomic_shared_ptr_111() {
	
	//run_atomic_shared_ptr_with_copy();
	
	run_atomic_shared_ptr_with_reference();
	
	//run_atomic_shared_ptr_fix();
	
	this_thread::sleep_for(4s);

}

//int main()
//{
//	
//	run_atomic_shared_ptr_111();
//}

