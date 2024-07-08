#include <iostream>
#include <numeric> // iota
using namespace std;
/*
	1. iota() - Store increasing sequence 
		Assigns to every element in the range [first, last] successive values of val, as if incremented with ++val after each element is written.
	2.
*/
void run_iota()
{

	int arr1[100];
	iota(begin(arr1), end(arr1), 0); // prints - 0 1 2 3 ....99
	copy(begin(arr1), end(arr1), ostream_iterator<int>(cout, " "));
	cout << endl;
}

//int main()
//{
//	run_iota();
//	return 0;	
//}
