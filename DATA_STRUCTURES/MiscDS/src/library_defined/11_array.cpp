#include <iostream>
#include<array> 
#include <algorithm>
using namespace std;


void TwoD()
{
	cout << endl << "TwoD() : ";
	using roww = array<int, 2 >; // <datatype, size>
	array<roww, 2> arr;
	arr[0] = { 1, 2 };
	arr[1] = { 3, 4 };
	cout << endl;
	for (auto r : arr) {
		cout << r[0] << "  " << r[1];
		cout << endl;
	}
}
//.................................................

void array_fill() {
	cout << endl << "array_fill() : " << endl;

	array<int, 10> arr = { 0 };
	array<int, 50> arro;
	for_each(arr.begin(), arr.end() - 1, [i = 0](auto& a) mutable {a = ++i; return a; });
	const int* p = arr.data();

	cout << "arr.size() : " << arr.size() << endl; // 10
	cout << "arr.max_size() " << arr.max_size() << endl; //10
	for (auto a : arr)
		cout << a << " "; // 1 2 ... 0
}

void array_impl()
{
	cout << endl << "array_impl() : ";

	//1. regular array
	int arr[] = { 9,8,3,4,5,6 };
	int size = sizeof(arr) / sizeof(arr[0]);
	sort(arr, arr + size, less<int>()); // ascending order
	for (auto n : arr)
		cout << n << endl; // 4 5 6 ...

	//2.
	cout << "stl array " << endl;
	array <int, 5> sta = { 7,6,5,4,5 };
	for (auto n : sta)
		cout << n << endl; // 7 6 5 ...
	cout << sta.at(3) << endl; // 4

	//3.
	cout << "data() " << sta.data()[0] << endl; // item at first position // 7

	//4.
	auto pos = find(sta.begin(), sta.end(), 4); // find item
	auto itrEnd = remove(sta.begin(), sta.end(), 5); // remove all occurrence of item  5 in the given range
	// erase() not available for std::array class
	/*
		These algorithms will not actually remove any elements, but instead only move them to the end of the sequence, so that all "removed" elements fall behind a certain boundary in your range. This boundary is returned as an iterator.
	*/
	cout << "after removing (5) fm { 7,6,5,4,5 } : " << endl;
	for (auto itr = sta.begin(); itr < itrEnd; itr++) {
		cout << *itr << " "; // 7 6 4
	}
	cout << endl;
	cout << "after removing (5) fm { 7,6,5,4,5 } array becomes : " << endl;
	for (auto n : sta)
		cout << n << endl; // 7 6 4 4 5

	//6.
}
class A {
public:
	~A() {
		cout << "dest " << endl;
	}
};
void array_with_userdefined() {
	array<A*, 2>* arra = new array<A*, 2>;
	arra->fill(nullptr);
	arra->_Elems[0] = new A();

	//1.
	//A* obj = arra->at(0);
	//delete obj;
	//2.
	for (auto* item : *arra) {
		delete item;
		item = nullptr; // this will not make element position to zero .. no use of doing this
	}
	arra->fill(nullptr); // good if we make all positions nullptr

	//3.
	for (auto i = arra->begin(); i != arra->end(); i++) {
		if (*i)
			delete* i;
	}
	//4.
	delete arra; // delete the final parent container array
}
void run_array()
{
	TwoD();
	array_fill();
	array_impl();
}

//int main()
//{
//	run_array();
//	return 0;
//}