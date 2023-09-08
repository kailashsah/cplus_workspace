#include <iostream>

#include <memory> // make_unique
#include <algorithm>
using namespace std;
#include <vector>
void run_array_in_ptr()
{
	auto endll = [] { cout << endl << endl; };

	unique_ptr<int> pInt = make_unique<int>(4);
	cout <<"Value in the unique ptr : " << * pInt << endl;   // 4
	cout <<" *(pInt.get()) : " << * (pInt.get()); // 4 
	endll();
	//	
	unique_ptr<int[]> arr_one{ new int[10] }; //ok
	//
	unique_ptr<int[]> arr = make_unique<int[]>(10);			//ok
	cout << "Garbage value held by 10 as unique ptr array : ";
	for (int i{}; i < 10; ++i) 
		cout << arr[i]; 
	endll(); // 0000000000-33686019 (garbage for 11th) 
	
	//unique_ptr<int[10]> arr = make_unique<int [10]>(10);	// error
	//copy(begin(*arr.get()), end(arr.get()), ostream_iterator<int>(cout)); // error
	//
	int arr_two[10];
	cout << "output from int arr_two[10] ";
	copy(begin(arr_two), end(arr_two), ostream_iterator<int>(cout)); 
	endll();
	//
	vector<int> vec = { 1,2,3 };
	cout << "output from vector<int> vec = { 1,2,3 } : ";
	copy(begin(vec), end(vec), ostream_iterator<int>(cout)); 
	endll(); // 123
}



int main()
{
	
	run_array_in_ptr();
}
