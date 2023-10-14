#include <iostream>
#include <string>
using namespace std;

/*
	1. https://www.geeksforgeeks.org/static_cast-in-cpp/
*/

void run_static_cast()
{
	int a = 7;
	const int b = static_cast <int> (a); // ok
	const int c = a; // ok
}

//int main()
//{
//	run_static_cast();
//	return 0;	
//}
