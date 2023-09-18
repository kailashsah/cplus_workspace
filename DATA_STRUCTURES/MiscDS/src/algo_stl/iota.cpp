#include <iostream>
#include <numeric> // iota
using namespace std;

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
