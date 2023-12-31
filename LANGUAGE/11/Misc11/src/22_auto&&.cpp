#include <iostream>
using namespace std;
/*
	1. auto&& - universal reference.
		By using auto&& var = <initializer> -- it will accept any initializer regardless of whether it is an lvalue or rvalue expression and I will preserve its constness.

		This is typically used for forwarding (usually with T&&). The reason this works is because a forwarding reference, auto&& or T&&, will bind to anything.

	2. const auto& - hat will also bind to anything? -- you won't be able to later bind it to any non-const references or invoke any member functions that are not marked const.

	3.	auto         => will copy the vector, but we wanted a reference
		auto&        => will only bind to modifiable lvalues
		const auto&  => will bind to anything but make it const, giving us const_iterator
		const auto&& => will bind only to rvalues
*/
void run_ex_v1();
void run_ex_v2();
void run_lifetime_extension();
//
void run_ex_v1() {

	/*
		auto&& vec = some_expression_that_may_be_rvalue_or_lvalue;
		auto i = std::begin(vec);
		(*i)++;
	*/
}

void run_ex_v2() {

	/*
		// If you then use std::forward on your auto&& reference to preserve the fact that it was originally either an lvalue or an rvalue 

		auto&& var = some_expression_that_may_be_rvalue_or_lvalue;
		// var was initialized with either an lvalue or rvalue, but var itself
		// is an lvalue because named rvalues are lvalues
		use_it_elsewhere(std::forward<decltype(var)>(var));
	*/
}
/*
	1. lifetime extension via auto&&
		We can see that the temporary object was not destroyed (1) on the statement it was created, but at the end of the scope of rx. The rvalue reference extended its lifetime.
	2. When can that be useful?
			1. A case I see is when the returned object is not moveable (for example an std::array)
			2. when we’d like to modify this value (so we wouldn’t use const&).
	3. https://www.fluentcpp.com/2021/04/02/what-auto-means/
*/
struct X
{
	~X() { std::cout << "destruct X\n"; }

};
X getX()
{
	return {};
}
void run_lifetime_extension() {
	std::cout << "before getX()\n";
	auto&& rx = getX(); // (1)
	std::cout << "after getX()\n";

	/*
		before getX()
		after getX()
		destruct X

	*/
}

//int main()
//{
//	run_lifetime_extension();
//	return 0;
//}

