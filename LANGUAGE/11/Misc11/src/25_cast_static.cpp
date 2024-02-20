#include <iostream>
#include <string>
using namespace std;

/*
	1. https://www.geeksforgeeks.org/static_cast-in-cpp/
	2. static_cast can provide both upcasting and downcasting in case of inheritance.
	3. static_cast to Cast ‘to and from’ Void Pointer
	4. simplest type of cast that can be used. It is a compile-time cast. It does things like implicit conversions between types (such as int to float, or pointer to void*), and it can also call explicit conversion functions.

*/

void run_static_cast()
{
	int a = 7;
	//1.
	const int b = static_cast <int> (a); // ok
	//b = 50; // compilation error - expression must not be modifiable

	//2.
	const int c = a; // ok
}

void run_static_cast_int_char() {
	char c = 'a';

	// Pass at compile time, may fail at run time
	int* q = (int*)&c;

	//1.
	//int* p = static_cast<int*>(&c); // error C2440: 'static_cast': cannot convert from 'char *' to 'int *' .. types pointed to are unrelated requires reinterprest_cast<>

	//2.
	//int i = 50; // int & char both are compiling fine .. but static_cast<> fail to identify char type in (3), thus no error
	char i = 'a';
	//void* p = const_cast<void*>(&i); // error - const_cast can only adjust type qualifiers, it cannot change the underlying type
	void* p = static_cast<void*>(&i);
	int* intptr = static_cast<int*> (p); //(3)
	cout << *intptr << endl;

}

//int main()
//{
//	//run_static_cast();
//	run_static_cast_int_char();
//	return 0;
//}
