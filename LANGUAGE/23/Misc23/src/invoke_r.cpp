#include <iostream>
using namespace std;
/*
	1. This paper proposes invoke_r, a variant of std::invoke that allows specifying the return type

	2. When R is not cv void, you can specify a compatible return type that is different from the callable entity. For example, you can request a function that returns T&& to return a prvalue of type T by calling invoke_r<T>.

	3. If the callable entity has overloaded call operators that may return different types, they may agree on a return type that allows you to specify. For example, you can perform an upcast for covariant return types.

*/
#include <functional>

void print_num_(int i) {
	cout << i << endl;
}

void run_invoke_r() {

	invoke_r<void>(print_num_, 10);
} 

void run_invoke_r_v2()
{
	
	auto add = [](int x, int y) { return x + y; };
	cout << typeid(add).name() << endl; // class `void __cdecl run_invoke_r_v2(void)'::`2'::<lambda_1>
	
	auto ret = std::invoke_r<float>(add, 11, 22);
	static_assert(std::is_same<decltype(ret), float>()); // performs compile-time assertion checking. // <type_traits>
	/*
		1. is_same - If T and U name the same type (taking into account const/volatile qualifications), provides the member constant value equal to true. Otherwise value is false.
	*/
	static_assert(std::is_same<decltype(ret), float>::value); // ::value member function
	
	std::cout << ret << '\n';
}

//int main()
//{
//	run_invoke_r();
//	run_invoke_r_v2();
//	return 0;
//}