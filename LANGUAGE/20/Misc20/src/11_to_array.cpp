#include <iostream>
using namespace std;
#include <array> // to_array
#include <algorithm> // for_each
/*
	1. array<> template class
*/

void run_to_array() // to_array 
{
	//1.
	int a[] = { 1,3,2 };
	std::array b = std::to_array(a); // in c++20 array<int,3> not required, it deduced itself
	for_each(begin(b), end(b), [=](auto a) {cout << a << " "; });

	//2.
	cout << endl;
	array c = to_array<double>({ 4,5,6 });
	cout << typeid(c).name() << endl;		//class std::array<double, 3>  .. auto deduced to this type
	for_each(begin(c), end(c), [=](auto a) {cout << a << " "; });

	//3.
	cout << endl;
	array d = to_array("abc");
	cout << typeid(d).name();			// class std::array<char,4>
	for_each(begin(d), end(d), [=](auto a) {cout << a << " "; });
}

