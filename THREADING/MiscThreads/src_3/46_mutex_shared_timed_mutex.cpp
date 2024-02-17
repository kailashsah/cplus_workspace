#include <iostream>
using namespace std;

/*
	1. The supported suffixes are:

		h → std::chrono::hours
		min → std::chrono::minutes
		s → std::chrono::seconds
		ms → std::chrono::milliseconds
		us → std::chrono::microseconds
		ns → std::chrono::nanoseconds

	2. classifications timed/non-timed - https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n3891.htm
*/

#include <shared_mutex> // shared_timed_mutex, shared_lock<>
void foo() {
	shared_timed_mutex m;
	using namespace std::literals::chrono_literals;
	std::shared_lock<std::shared_timed_mutex> lk(m, 50ms);
	//1.
	//lk.release(); // this will release the lock & without lock condition will be executed.

	//2.
	if (lk.owns_lock()) {

		//do_something_with_lock_held();
		cout << "do_something_with_lock_held()" << endl; // this will take execution
	}
	else {
		//do_something_without_lock_held();
		cout << "do_something_without_lock_held()" << endl;
	}
}
void run_shared_timed_mutex() {
	foo();
}

//void main() {
//    run_shared_timed_mutex();
//}