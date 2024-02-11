#include <iostream>
using namespace std;

/*
	1. throw() is an alias for noexcept(true)
	2. noexcept() - By declaring a function, a method, or a lambda function as noexcept, you specify that these do not throw an exception, and if they throw, you do not care and let the program crash.


*/


void run_noexcept_and_throw()
{
	//1.
	void func1() noexcept;        // does not throw
	void func2() noexcept(true);  // does not throw
	void func3() throw();         // does not throw

	//2.
	void func4() noexcept(false); // may throw
}

//int main()
//{
//	run_noexcept_and_throw();
//	return 0;
//}
