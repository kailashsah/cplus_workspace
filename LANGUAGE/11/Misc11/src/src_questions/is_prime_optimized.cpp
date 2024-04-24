#include <iostream>
using namespace std;
/*
	1. prime numbers - 
		a whole number greater than 1 that cannot be exactly divided by any whole number other than itself and 1 (e.g. 2, 3, 5, 7, 11).
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
	int till_this_count = 10;
	int incrementor = 2;
	int countof_found_elements = 0; 

	while (countof_found_elements < till_this_count) {
		
		if (is_prime_optimized(incrementor))	 //2 3 5 7 11 13 17 19 23 29 31
		//if (is_prime(incrementor))			// 2 3 5 7 11 13 17 19 23 29
		{
			cout << incrementor << " ";
			countof_found_elements++;
		}
		incrementor++;
	}
}

int main()
{
	run_isPrime();
	return 0;
}
