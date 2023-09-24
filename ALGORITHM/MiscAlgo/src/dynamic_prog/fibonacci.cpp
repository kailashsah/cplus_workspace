#include <iostream>
using namespace std;

constexpr int fib(int n)
{
	return (n <= 1) ? n : fib(n - 2) + fib(n - 1);

	// driver code
	//cout << fib(5);
}