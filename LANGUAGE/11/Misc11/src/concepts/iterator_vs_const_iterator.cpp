#include <iostream>
using namespace std;

/*
	1.  For each container class, there are two STL-style iterator types: one that provides read-only access and one that provides read-write access. Read-only iterators should be used wherever possible because they are faster than read-write iterators.

	2.  by noting that the const-iterator can never change the value, then perhaps it would enable some optimizations.


*/

#include <set>
void run_const_iterator()
{
    int arr[] = { 14, 12, 15, 11, 10 };

    // initializes the set from an array
    set<int> s(arr, arr + 5);

    // prints all elements in set
    for (auto it = s.cbegin(); it != s.cend(); it++)
        cout << *it << " ";
}

//int main()
//{
//	run_const_iterator();
//	return 0;
//}
