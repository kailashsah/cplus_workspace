#include <iostream>
#include<array> 
#include <algorithm>
using namespace std;


void TwoD()
{
	
	using roww = array<int, 2 >; // <datatype, size>
	array<roww, 2> arr;
	arr[0] = { 1,2 };
	arr[1] = { 3, 4 };
	cout << endl;
	for (auto r : arr) {
		cout << r[0] << r[1];
		cout << endl;
	}

}
//.................................................

void array_fill() {
	array<int, 10> arr = {0};
	array<int, 50> arro;
	for_each(arr.begin(), arr.end()-1, [i = 0](auto& a) mutable {a = ++i; return a; });
	const int * p = arr.data();
	
	cout << arr.size() << arr.max_size();
	for (auto a : arr)
		cout << a << " ";
}


void array_impl()
{
	// regular array
	int arr[] = { 9,8,3,4,5,6 };
	int size = sizeof(arr) / sizeof(arr[0]);
	sort(arr, arr + size, less<int>()); // ascending order
	for (auto n : arr)
		cout << n << endl;

	cout << "stl array " << endl;
	array <int, 5> sta = { 7,6,5,4,5 };
	for (auto n : sta)
		cout << n << endl;
	cout << sta.at(3) << endl;

	cout << "data() " << sta.data()[0] << endl; // item at first position
	auto pos = find(sta.begin(), sta.end(), 4); // find item
	remove(sta.begin(), sta.end(), 5); // remove first occurrence of item  5
	//cout << *pos;
	for (auto n : sta)
		cout << n << endl;
}