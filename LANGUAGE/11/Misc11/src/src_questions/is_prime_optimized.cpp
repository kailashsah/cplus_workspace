#include <iostream>
using namespace std;
/*
	1. 
	2. 
*/
void run_isPrime();
//
bool isPrime(int n) {
	if (n <= 1)
		return false;
	if (n <= 3)
		return false;
	if (n % 2 == 0 || n % 3 == 0)
		return false;

	for (int i = 5; i * i <= n; i = i + 6) {
		if (n % i == 0 || n % (i + 2) == 0)
			return false;

	}

	return true;


}
bool is_prime_optimized(int n) {

	int m = n / 2;
	int flag = 0;
	for (int i = 2; i <= m; ++i) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;

}
void run_isPrime() {
	int K = 10;
	int i = 2; int k = 0;
	while (k < K) {
		if (is_prime_optimized(i))	 // 5 7 11 13 17 19 23 29 31
		//if (is_prime(i)) // 2 3 5 7 11 13 17 19 23 29
		{
			cout << i << " ";
			k++;
		}
		i++;
	}
}

//int main()
//{
//	run_isPrime();
//	return 0;
//}
