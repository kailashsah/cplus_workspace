#include <iostream>
#include "cplus20.h" //#define cplus20


using namespace std;
#ifdef cplus20

#include <map>
#include <list>
#include <array>

// map contains
// string view
// format string 
// is standard layout
// output stream ensuring synchronization
// explicit(bool), ctor made explicit at compile time
// run_explicit_bool();
// mid point
constexpr int addOne(int n)
{
	return [n] { return n + 1; }();
}

////////////////////////  // map contains
void run_map()
{
	
	/*list<int> ll = {2,5,6};
	if(ll.contains(2))			// list don't has contains, it has elements not key
		cout << " list contains " << endl;*/

	map<int, char> map = { {1,'a'}, {1, 'b'}};
	if (map.contains(1))
		cout << " found " << map.at(1) << endl; // found a

	multimap<int, char> mmap = { {1,'a'}, {1, 'b'} };
	//(*(mmap.find(1)))->second; // type 'std::pair<const int,char>' does not have an overloaded member 'operator ->'
	if (mmap.contains(1))
		cout << " multimap found "   << (*(mmap.find(1))).second << endl;  // multimap found a

	//array arr{ 1,2,3 };
	//arr.contains(1); // 'contains': is not a member of 'std::array<_First,3>'


}
///////////////////////////////////// // string view

void func_sv(std::string_view sv)
{
	cout << sv << endl;
}

void func_str(std::string str)
{
	cout << str << endl;
}
void run_stringview()  // string view
{
	string_view sv = "str literal";
	string str_reg{ sv };
	cout << str_reg << endl; // str literal
	//func_str(sv);			//No user-defined-conversion operator available that can perform this conversion, or the operator cannot be called
	func_str(static_cast<string>(sv)); // str literal -> fun with regular string
				  //
	std::string s = "abc";
	func_sv(s);				// abc
	// 
	string str = "foobar";
	cout << str.starts_with("foo");

}
///////////////////////////////////// // format string 

#include <format>
void run_format()
{
	int a = 10;
	auto str = std::format(" hello {}  world!", a);
	cout << str << endl;
}

///////////////////////////////////// // is standard layout
#include <type_traits>
class st {
	st() = delete;
	st(st&&) = delete;
};
void run_is_pod()
{
	//cout << is_pod<st>; // deprecated in c++20
	cout << is_standard_layout<st>::value; // returns false if any private member, in case of public return is ture;
}


///////////////////////////////////// // output stream ensuring synchronization
#include <syncstream>
void run_sys_ostream()
{
	osyncstream(cout) << " I am osyncstream " << endl;
}

///////////////////////////////////// // mid point
import <numeric>; 
void run_midpoint()
{
	cout << std::midpoint(1, 4); // 5/2 -> 2
	//cout << std::midpoint(1, 6.5); // 7/2 -> 3 //error C2784: '_Ty *std::midpoint(_Ty *const ,_Ty *const ) noexcept': could not deduce template argument for '_Ty *const ' from 'int'
}

////////////////////////  // explicit(bool), ctor made explicit at compile time
struct foo {

	template<typename T>
	//explicit(true)	foo(T) {}
	explicit(!is_integral_v<T>)	foo(T) {
		cout << "ctor called";
	}
};
void run_explicit_bool()
{
	foo a{ 123 };
	//foo b = "123"; // explicit specifier evaluates to true //error C2440: 'initializing': cannot convert from 'const char [4]' to 'foo'
	foo c{ "123" }; // implicit call
	foo d = 'a';    // explicit success
	foo e{ 5.5 }; // direct call // implicit call
}

#include <initializer_list>

void function1(auto vec)
{
	cout << "function1" << endl;
	cout << typeid(vec).name() << endl;
	cout << typeid(decltype(vec)).name();;
}

void run_mix_main()
{
	auto var = { "hello", "world", "test" };
	// function1( {"hello", "world", "test"} );
	function1(var);


	//run_explicit_bool();

	// run_midpoint();

	//run_sys_ostream();
	//
	//run_stringview();
	//
	//run_map();
}

//int main()
//{
//	run_mix_main();
//	return 1;
//}

#endif
