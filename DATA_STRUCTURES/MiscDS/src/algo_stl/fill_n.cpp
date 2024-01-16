#include <iostream>
#include <vector>
#include <array>
using namespace std;
//
void vector_filln(); 
void array_cstyle_fill();
void array_fill();
//
void vector_filln()
{
	vector<int> vec(100);
	std::fill_n(vec.begin(), vec.end() - vec.begin(), 1200);
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));

	// 1200  1200  1200 1200 1200 1200 1200 1200 1200 1200 1200 1200 .... 100 times
}

void array_cstyle_fill()
{
	const int n = 5;
	int val = 1;

	int arr1[n];

	std::fill_n(begin(arr1), n, val);
	copy(begin(arr1), end(arr1), ostream_iterator<int>(cout, " "));
	
}
#include <algorithm> // for_each()
void array_class_fill() {
	//1.
	array<int, 100> arr2;
	//fill_n(arr2, 100 , 1); // error C2675: unary '++': '_OutIt' does not define this operator or a conversion to a type acceptable to the predefined operator
	
	//2.
	array<int, 100> arr{};
	//for_each(begin(arr), end(arr), ostream_iterator<int>(cout, " ")); // error: C2064: term does not evaluate to a function taking 1 arguments	
	copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));//ok
	for_each(begin(arr), end(arr), [](int x) {cout << x; }); // ok

}
//int main()
//{
	//vector_filln();
	//array_cstyle_fill();
	//array_fill();
//	return 0;	
//}
