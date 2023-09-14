#include <iostream>
#include <vector>
#include <array>
using namespace std;


void run_filln()
{
	vector<int> vec(100);
	std::fill_n(vec.begin(), vec.end() - vec.begin(), 1200);
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));

	// 1200  1200  1200 1200 1200 1200 1200 1200 1200 1200 1200 1200 .... 100 times
}

void check_array()
{
	const int n = 5;
	int val = 1;

	int arr1[n];

	std::fill_n(begin(arr1), n, val);
	copy(begin(arr1), end(arr1), ostream_iterator<int>(cout, " "));


	array<int, 100> arr ;
	//fill_n(arr, 100 , 1);
	//array<int, 100> arr;
	//array<int, 100> arr{};
	//for_each(begin(arr), end(arr), ostream_iterator<int>(cout, " ")); // it needs a func
	//for_each(begin(arr), end(arr), [](int x) {cout << x; }); // ok
}

//int main()
//{
//	run_filln();
//	return 0;	
//}
