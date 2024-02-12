#include <iostream>
using namespace std;

/*
	1.  if (atomicA.is_lock_free()) - to make sure that your atomic has a real atomic behavior you can use atomicA.is_lock_free().

	2. There are a lot of severe restrictions on a user-defined type to get an atomic type std::atomic<MyType>

		a)The copy assignment operator for MyType must be trivial for all base classes of MyType and all non-static members of MyType. Only an automatic by the compiler-generated copy assignment operator is trivial.
			To say it the other way around. User-defined copy assignment operators are not trivial.
			if we Delete functions it gives error for trivial constraints, see code.

		b) MyType must not have virtual methods or base classes.
		c) MyType must be bitwise comparable so that the C functions memcpy or memcmp can be applied.

		class X has no virtual functions (13.3) and no virtual base classes


*/

#include <iostream>
#include <atomic>

class test_atomic
{
public:
	int a;
	void Show()
	{
		std::cout << a << "\n";
		/*
			if virtual show()
				error C2338: atomic<T> requires T to be trivially copyable, copy constructible, move constructible, copy assignable, and move assignable.
		*/
	}
	//A(const A&) = delete; 
	//A(A&&) = delete; 
};

void run_atomic_user_defined_type() {
	test_atomic a1{ 1 };
	test_atomic a2{ 2 };
	std::atomic<test_atomic> atomicA{ a1 };
	//1.
	atomicA.load().Show();//the original atomicA //1
	atomicA.compare_exchange_strong(a2, test_atomic{ 2 });// this makes no change
	atomicA.load().Show(); //1

	atomicA.compare_exchange_strong(a1, test_atomic{ 2 });//this changes atomicA
	atomicA.load().Show(); //2

	//2.
	if (atomicA.is_lock_free())
		cout << "atomicA is lock free " << endl;

}

//int main() {
//	run_atomic_user_defined_type();
//}

