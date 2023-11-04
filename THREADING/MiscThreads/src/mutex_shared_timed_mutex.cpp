#include <iostream>
using namespace std;

/*

*/
#include <shared_mutex>
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