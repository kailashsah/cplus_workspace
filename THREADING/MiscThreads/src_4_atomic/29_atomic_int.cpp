#include <iostream>
using namespace std;

/*
	1. atomic_int

	2.
		a) increments or decrements the atomic value by one
		operator++
		operator++(int)
		operator--
		operator--(int)
 
		b) adds, subtracts, or performs bitwise AND, OR, XOR with the atomic value

		operator+=
		operator-=
		operator&=
		operator|=
		operator^=
 

*/
void run_atomic_int();
//
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic_int acnt;
int cnt;

void thread_func_2323()
{
	for (int n = 0; n < 10000; ++n)
	{
		++acnt;
		++cnt;
		// Note: for this example, relaxed memory order
		// is sufficient, e.g. acnt.fetch_add(1, std::memory_order_relaxed);
	}
}
void run_atomic_int() {
	{
		std::vector<std::jthread> pool;
		for (int n = 0; n < 10; ++n)
			pool.emplace_back(thread_func_2323);
	}

	std::cout << "The atomic counter is " << acnt << '\n';
	std::cout << "The non-atomic counter is " << cnt << '\n';
}
/*
	The atomic counter is 100000
	The non-atomic counter is 69696
*/

//int main()
//{
//	run_atomic_int();
//}

