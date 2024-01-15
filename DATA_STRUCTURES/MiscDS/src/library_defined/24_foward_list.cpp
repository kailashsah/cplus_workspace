#include <iostream>
#include <forward_list>
using namespace std;

/*
Forward List is preferred over the list when only forward traversal is required (same as the singly linked list is preferred over doubly linked list) as we can save space. Some example cases are, chaining in hashing, adjacency list representation of the graph, etc.
*/
void run_forward_list()
{
	forward_list<int> flist1;

	// Declaring another forward list
	forward_list<int> flist2;

	//Declaring another forward list
	forward_list<int> flist3;

	// Assigning values using assign()
	flist1.assign({ 1, 2, 3 });

	// Assigning repeating values using assign()
	// 5 elements with value 10
	flist2.assign(5, 10); // 10 10 10 10 10


	//Assigning values of list 1 to list 3
	flist3.assign(flist1.begin(), flist1.end());

	// Displaying forward lists
	cout << "The elements of first forward list are : ";
	for (int& a : flist1)
		cout << a << " ";
	cout << endl;

	cout << "The elements of second forward list are : ";
	for (int& b : flist2)
		cout << b << " ";
	cout << endl;


	cout << "The elements of third forward list are : ";
	for (int& c : flist3)
		cout << c << " ";
	cout << endl;

	puts("aaaa"); // output in console
	puts("bbb");

	/*
		output
			The elements of first forward list are : 1 2 3
			The elements of second forward list are : 10 10 10 10 10
			The elements of third forward list are : 1 2 3
	*/
}
#include<algorithm> // for_each
void run_forward_list_second() {
	forward_list<int> flist(5);
	puts("");

	for_each(flist.begin(), flist.end(), [i = 0](auto& a)mutable{++i; a = i; }); // 12345
	// flist.emplace_after();

	flist.emplace_after(flist.begin(), 9); // only two functions push_front(), insert_after();
	flist.emplace_front(8);
	for (auto a : flist)
		cout << a; // 8192345
}

//int main()
//{
//	run_forward_list();
//	return 0;	
//}
