#include <iostream>
using namespace std;

/*
	1. you can't really compare std::function with std::mem_fn.
		std::function - is a class template whose type you specify,
		std::mem_fn -  is a function template with unspecified return type. There really isn't a situation in which you'd actually consider one versus the other.

	2. A better comparison might be between mem_fn and std::bind.
		std::bind - function template
		std::mem_fn - function template
		There, for the specific use-case of a pointer-to-member, mem_fn is going to a lot less verbose if all you want to do is pass-through all the arguments. Given this simple type:

*/
void run_mem_fn_vs_bind();
void run_with_additional_argument();
void run_memfn_with_unique_ptr();
//
struct A {
	int x;
	int getX() { return x; }
	int add(int y) { return x + y; }
};

A a{ 2 };
#include <functional> // mem_fn

void run_mem_fn_vs_bind()
{
	using namespace std::placeholders;
	A a{ 2 };
	auto get1 = std::mem_fn(&A::getX);
	auto get2 = std::bind(&A::getX, _1);

	cout << get1(a) << endl; // yields 2
	cout << get2(a) << endl; // same


}

void run_with_additional_argument() {
	//  mem_fn is more concise in this case. 

	//1.
	A a{ 2 };
	using namespace std::placeholders;
	auto add1 = std::mem_fn(&A::add);
	auto add2 = std::bind(&A::add, _1, _2);
	cout << add1(a, 5) << endl;	// 7
	cout << add2(a, 5) << endl; // 7

	//2.
	{
		//if we wanted to bind a specific argument, say call add(5) on a given A, you can only do that with bind :

		auto add_5 = std::bind(&A::add, _1, 5);
		add_5(a); // yields 7 

		// Ultimately, no comparison between function and mem_fn, but there are times to prefer mem_fn to bind.
	}
}

void run_memfn_with_unique_ptr() {
	//mem_fn - Function template std::mem_fn generates wrapper objects for pointers to members, which can store, copy, and invoke a pointer to member. Both references and pointers (including smart pointers) to an object can be used when invoking a std::mem_fn.

	cout << "run_bind_with_unique_ptr" << endl;
	A a{ 2 };
	auto access_data = std::mem_fn(&A::x);
	//1.
	auto ptr = make_unique<A>(); // prints '0'

	//2.
	//auto ptr = make_unique<A>(a); // call copy ctor // prints 2.

	cout << access_data(a) << endl; // 2 .. bcoz A a{ 2 };

	cout << access_data(ptr) << endl; // 0
}

//int main()
//{
//	//run_mem_fn_vs_bind();
//	//run_with_additional_argument();
//	run_memfn_with_unique_ptr();
//	return 0;
//}
