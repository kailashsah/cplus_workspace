// C++ program to implement the
// deep copy
#include <iostream>
using namespace std;

/*
	1. perfromance analysis
	2. whose performance is better
		- range base for with switch .. case
		- range base for with if()
		- range base for with any_of() using initlialize_list<>
		- for_each()
		- Concurrency::parallel_for_each()

	3.  below give little better result than others
		- for_each()
		- Concurrency::parallel_for_each()
*/

#include <vector>
#include <thread>
#include <algorithm>
#include <numeric> // iota()
initializer_list<int> ilist = { 10, 9,8 };
vector<int> vec(10);

#include <ppl.h> // parallel_for_each()
void run_per1() {


	//fill(vec.begin(), vec.end(), 10);
	iota(vec.begin(), vec.end(), 0);
	auto start = chrono::high_resolution_clock::now();

	//this_thread::sleep_for(chrono::milliseconds(100));

	for (int i : vec)
	{
		switch (i)
		{
		case 10:
		case 9:
		case 8:
			cout << "match" << endl;
			break;
		default:
			break;
		}
		/*if (i == 10 || i == 9 || i == 8)
		{
			cout << "match" << endl;
		}*/

		/*if(any_of(vec.begin(), vec.end(), [](int t) {
			if (t == 10)
				return true;;
			}))
			cout << "match" << endl;*/
	}
	auto end = chrono::high_resolution_clock::now();
	auto aa = chrono::duration_cast<chrono::microseconds> (end - start);
	cout << aa.count() << endl;
}
#include <execution>
void run_per2() {
	iota(vec.begin(), vec.end(), 0);

	auto start = chrono::high_resolution_clock::now();
	//this_thread::sleep_for(chrono::milliseconds(100));
	//for (int i : vec)
	//{

	//	if (i == 10 || i == 9 || i == 8)
	//	{
	//		cout << "match" << endl;
	//	}
	//}

	/*Concurrency::parallel_for_each(vec.begin(), vec.end(), [](int i) {
		if (i == 10 || i == 9 || i == 8)
		{
			cout << "match" << endl;
		}
		});*/
	for (int i : vec) {
		for_each(execution::par, ilist.begin(), ilist.end(), [&](int el) {
			if (i == el)
			{
				cout << "match" << endl;
			}
			});
	}
	auto end = chrono::high_resolution_clock::now();
	auto aa = chrono::duration_cast<chrono::microseconds> (end - start);
	cout << aa.count() << endl;
}
void run_per3() {
	iota(vec.begin(), vec.end(), 0);

	auto start = chrono::high_resolution_clock::now();
	//this_thread::sleep_for(chrono::milliseconds(100));
	for (int i : vec)
	{
		if (any_of(ilist.begin(), ilist.end(), [&](int t) {
			if (t == i)
				return true;;
			}))
			cout << "match" << endl;
	}

	auto end = chrono::high_resolution_clock::now();
	auto aa = chrono::duration_cast<chrono::microseconds> (end - start);
	cout << aa.count() << endl;
}

void run_performance_any_of() {
	run_per1();
	run_per2();
	run_per3();

}


//int main()
//{
//	run_performance_any_of();
//	return 0;
//}