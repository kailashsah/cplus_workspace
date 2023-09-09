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
