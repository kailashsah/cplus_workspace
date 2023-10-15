#include <iostream>
using namespace std;

/*
	1. consteval - specifies that a function is an immediate function, that is, every call to the function must produce a compile-time constant

	2. Same as constexpr, a consteval specifier implies inline.

	3.
*/

//1. This function might be evaluated at compile-time, if the input
// is known at compile-time. Otherwise, it is executed at run-time.
constexpr unsigned factorial(unsigned n)
{
	return n < 2 ? 1 : n * factorial(n - 1);
}

//2. With consteval we enforce that the function will be evaluated at compile-time.
consteval unsigned combination(unsigned m, unsigned n)
{
	return factorial(n) / factorial(m) / factorial(n - m);
}

//3.
consteval int sqr(int n) // immediate function
{
	return n * n;
}

//4.
//constexpr int dblsqr(int n)
//{
//	return 2 * sqr(n);      // Error: Enclosing function is not consteval // Error: Call does not produce a constant
//							// and value of n cannot be used as constant
//}
void run_consteval() {
	
	//3.1
	constexpr int r = sqr(100); // OK
	
	//3.2
	//int x = 100;					// fix is -> const int x=100;
	//int r2 = sqr(x);				// Error: Call does not produce a constant

	

}
