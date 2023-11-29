#include <iostream>
#include <string>
using namespace std;

/*
	1. An object of type std::initializer_list<T> is a lightweight proxy object that provides access to an array of objects of type const T.

	2. https://en.cppreference.com/w/cpp/utility/initializer_list
*/

#include <initializer_list>
void fn(auto vec)
{
	cout << "function for initializer_list" << endl;
	cout << typeid(vec).name() << endl; // class std::initializer_list<char const *>
	cout << typeid(decltype(vec)).name(); // class std::initializer_list<char const *>
}
void run_initializer_list_two()
{
	//1.
	auto var = { "hello", "world", "test" };
	
	//2.
	// function1( {"hello", "world", "test"} );
	fn(var);
}

//int main()
//{
//	run_initializer_list_two();
//	return 0;	
//}
