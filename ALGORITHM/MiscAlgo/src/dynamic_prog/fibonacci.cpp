#include <iostream>
using namespace std;
/*
	1.  0 1 1 2 3 4 8 13 
	2.	F(n) = F(n-1) + F(n-2), 
		F(0) = 0, F(1) = 1

*/
constexpr int fib(int n)
{
	cout << n << " "; // if we write this it gives constexpr error .. constexpr function 'fib' cannot result in a constant expression
	return (n <= 1) ? n : fib(n - 2) + fib(n - 1);

}

//void main()
//{
//	int result = fib(3); // 3
//	cout << result;
//}
