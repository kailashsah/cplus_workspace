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

//int main()
//{
//	run_static_cast();
//	return 0;	
//}
