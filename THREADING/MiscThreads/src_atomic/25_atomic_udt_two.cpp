#include <iostream>
using namespace std;

/*
	1. Free functions - atomic_load(), atomic_store()

	2. atomic free functions support the same types as the class template std::atomic but in addition to that the smart pointer std::shared_ptr.

		That is special because std::shared_ptr is not an atomic data type


*/
void run_atomit_udt_two_crashing();
void run_atomit_udt_two_222();
//
#define _SILENCE_CXX20_OLD_SHARED_PTR_ATOMIC_SUPPORT_DEPRECATION_WARNING // takes impact if defined in project preprocessor section
#define _SILENCE_ALL_CXX20_DEPRECATION_WARNINGS
//

class test_atomic_my_data {
public:
	int x;
	test_atomic_my_data(int arg) :x{ arg } {

	}
	virtual void print() { // IMP - we defined virtual here.
		cout << "class memeber value is " << x << endl;
	}
};

void run_atomit_udt_two_crashing() {
	//1.
	std::shared_ptr<test_atomic_my_data> p;
	std::shared_ptr<test_atomic_my_data> p2 = std::atomic_load(&p);
	p2->print();// gives a crash
}

void run_atomit_udt_two_222()
{
	//1.1
	std::shared_ptr<test_atomic_my_data> p = make_shared<test_atomic_my_data>(20);
	/*
		std::shared_ptr<test_atomic_my_data> p{20}
		initializing': cannot convert from 'initializer list' to 'std::shared_ptr<test_atomic_my_data>'
	*/
	//1.2
	//std::shared_ptr<test_atomic_my_data> p (new test_atomic_my_data(20));

	std::shared_ptr<test_atomic_my_data> p2 = std::atomic_load(&p);
	p2->print();// 20

	//2.
	std::shared_ptr<test_atomic_my_data> p3(new test_atomic_my_data{ 10 });
	std::atomic_store(&p, p3);
	p->print(); // 10

}

//int main()
//{
//	//run_atomit_udt_two_crashing();
//	run_atomit_udt_two_222();
//
//}

