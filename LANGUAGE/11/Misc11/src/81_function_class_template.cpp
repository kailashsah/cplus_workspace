#include <iostream>
using namespace std;
/*
	1. The function<> template is referred to as a polymorphic function wrapper because an instance of the template can wrap a variety of function. objects with a given parameter list and return type.

	2. Class template std::function is a general-purpose polymorphic function wrapper. Instances of std::function can store, copy, and invoke any CopyConstructible Callable target -- functions (via pointers thereto), lambda expressions, bind expressions, or other function objects, as well as pointers to member functions and pointers to data members.

*/
void print_num(int i)
{
	std::cout << i << '\n';
}
#include <functional>
struct Foo
{
	Foo(int num) : num_(num) {}
	void print_add(int i) const { std::cout << num_ + i << '\n'; }
	int num_;
};

void run_function_template()
{
	//1.
	// store a free function
	std::function<void(int)> f_display = print_num;
	f_display(-9);

	//2.
	{
		const Foo foo(314159);
		// store a call to a data member accessor
		std::function<int(Foo const&)> f_num = &Foo::num_;
		std::cout << "num_: " << f_num(foo) << '\n';

		// store a call to a member function and object
		//1.
		//using std::placeholders::_1;
		//2.
		using namespace std::placeholders;
		std::function<void(int)> f_add_display2 = std::bind(&Foo::print_add, foo, _1);
		f_add_display2(2);
	}

}

//int main()
//{
//	run_function_template();
//	return 0;
//}
