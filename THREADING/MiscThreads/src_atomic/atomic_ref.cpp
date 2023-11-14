#include <iostream>
using namespace std;

/*
	1. Constructs a new atomic_ref object.

			 Constructs an atomic_ref object referencing the object obj
	
	2. The program increments the values in a container using several threads. Then the final sum is printed. Non-atomic access may "loss" the results of some operations due to data-races.


*/
void run_atomic_ref();
//
#include <atomic>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

void run_atomic_ref() {
	using Data = std::vector<int>;

	auto inc_atomically = [](Data& data)
	{
		for (auto& x : data)
		//for (Data::value_type &x : data) //error C2451: a conditional expression of type 'std::vector<int,std::allocator<int>>' is not valid
		{
			auto xx = std::atomic_ref<Data::value_type>(x);
			++xx; // atomic read-modify-write
		}
	};

	auto inc_directly = [](Data& data)
	{
		for ( auto& x : data)
		//for (Data::value_type& x : data)
			++x;
	};

	auto test_run = [](const auto Fun)
	{
		Data data(10'000'000);
		{
			std::jthread j1{ Fun, std::ref(data) };
			std::jthread j2{ Fun, std::ref(data) };
			std::jthread j3{ Fun, std::ref(data) };
			std::jthread j4{ Fun, std::ref(data) };
		}
		std::cout << "sum = " << std::accumulate(cbegin(data), cend(data), 0) << '\n';
	};

	test_run(inc_atomically);
	test_run(inc_directly);
}
/*
	sum = 40000000
	sum = 39999996
*/

//int main()
//{
//  run_atomic_ref();
//
//}

