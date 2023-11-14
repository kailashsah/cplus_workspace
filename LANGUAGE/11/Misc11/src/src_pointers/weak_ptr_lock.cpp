#include <iostream>
using namespace std;
/*
	1. Returns a shared_ptr with the information preserved by the weak_ptr object if it is not expired.

		If the weak_ptr object has expired (including if it is empty), the function returns an empty shared_ptr (as if default-constructed).
*/
void run_weak_ptr_lock();
void run_weak_ptr_is_expired();
//
#include <iostream>
#include <memory>

void run_weak_ptr_lock() {
	std::shared_ptr<int> sp1, sp2;
	std::weak_ptr<int> wp;
	// sharing group:
	// --------------
	sp1 = std::make_shared<int>(20);    // sp1
	wp = sp1;                            // sp1, wp

	sp2 = wp.lock();                     // sp1, wp, sp2
	sp1.reset();                         //      wp, sp2

	sp1 = wp.lock();                     // sp1, wp, sp2

	std::cout << "*sp1: " << *sp1 << '\n';
	std::cout << "*sp2: " << *sp2 << '\n';
}

void run_weak_ptr_is_expired() {
	std::shared_ptr<int> shared(new int(10));
	std::weak_ptr<int> weak(shared);

	std::cout << "1. weak " << (weak.expired() ? "is" : "is not") << " expired\n"; // is not 

	shared.reset();

	std::cout << "2. weak " << (weak.expired() ? "is" : "is not") << " expired\n"; // is expired
	/*
		Returns whether the weak_ptr object is either empty or there are no more shared_ptr in the owner group it belongs to.
	*/
}

int main() {

	run_weak_ptr_is_expired();
	return 0;
}
//int main()
//{
//	return 0;
//}
