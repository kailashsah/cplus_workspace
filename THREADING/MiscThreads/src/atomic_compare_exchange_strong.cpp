#include <iostream>
using namespace std;

/*
	1. c++20 - bool compare_exchange_strong( T& expected, T desired);
		a) Atomically compares the value representation of the referenced object with that of expected, and if those are bitwise-equal, replaces the former with desired (performs a read-modify-write operation).

		b) Otherwise, loads the actual value stored in the referenced object into expected (performs a load operation).

	2. The comparison and copying are bitwise (similar to std::memcmp and std::memcpy); no constructor, assignment operator, or comparison operator are used.
	
	3. CAS - compare-and-swap operations
	4.

*/
#include <iostream>
#include <atomic>
#include <random>
using namespace std;
std::atomic<int> atomVal;

void store_if_not_equal(int desired)
{
	while (true)    // or maxloop....
	{
		int expected = desired;

		if (atomVal.compare_exchange_strong(expected, desired)) // if false, atomval copied into expected. 
		{
			// values matched - do nothing
			std::cout << expected << endl;
			
		}
		else
		{
			//expected now contains the "current value"
			// another thread could have sneaked in and changed it,
			// so only replace it if it still matches
			if (atomVal.compare_exchange_strong(expected, desired))
			{
				// success
				std::cout << expected << "  " << endl; //1804289383 
				std::cout << desired << "  " << endl; //2
				std::cout << atomVal.load() << "  " << endl; //2
			}
		}

		// if we arrive here, retry
	}
}

void run_compare_exchange_strong() {
	atomVal.store(rand());
	store_if_not_equal(2);
}

//int main()
//{
//	run_compare_exchange_strong();
//}

