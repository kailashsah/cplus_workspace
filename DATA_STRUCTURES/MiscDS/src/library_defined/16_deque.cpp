#include <iostream>
using namespace std;
/*
	1. Double-ended queues are sequence containers with the feature of expansion and contraction on both ends. They are similar to vectors, but are more efficient in case of insertion and deletion of elements. Unlike vectors, contiguous storage allocation may not be guaranteed.
		Double Ended Queues are basically an implementation of the data structure double-ended queue. A queue data structure allows insertion only at the end and deletion from the front. This is like a queue in real life, wherein people are removed from the front and added at the back. Double-ended queues are a special case of queues where insertion and deletion operations are possible at both the ends.
		The functions for deque are same as vector, with an addition of push and pop operations for both front and back.

		The time complexities for doing various operations on deques are-

		Accessing Elements- O(1)  -  NOTE - "random access" only possible in vector & deque
		Insertion or removal of elements- O(N)
		Insertion or removal of elements at start or end- O(1)

	2. Storing contents in multiple smaller arrays, allocating additional arrays at the beginning or end as needed. Indexing is implemented by keeping a dynamic array containing pointers to each of the smaller arrays.
*/

#include <deque>
void showdq(deque<int> g)
{
	deque<int>::iterator it;
	for (it = g.begin(); it != g.end(); ++it)
		cout << '\t' << *it;
	cout << '\n';
}

int run_deque()
{
	deque<int> gquiz;
	gquiz.push_back(10);
	gquiz.push_front(20);
	gquiz.push_back(30);
	gquiz.push_front(15);
	cout << "The deque gquiz is : ";
	showdq(gquiz);

	cout << "\ngquiz.size() : " << gquiz.size();
	cout << "\ngquiz.max_size() : " << gquiz.max_size();

	cout << "\ngquiz.at(2) : " << gquiz.at(2);		// O(1)
	cout << "\ngquiz.front() : " << gquiz.front();
	cout << "\ngquiz.back() : " << gquiz.back();

	cout << "\ngquiz.pop_front() : ";
	gquiz.pop_front();
	showdq(gquiz);

	cout << "\ngquiz.pop_back() : ";
	gquiz.pop_back();
	showdq(gquiz);

	return 0;
	/*
		The deque gquiz is :     15    20    10    30

		gquiz.size() : 4
		gquiz.max_size() : 4611686018427387903
		gquiz.at(2) : 10
		gquiz.front() : 15
		gquiz.back() : 30
		gquiz.pop_front() :     20    10    30

		gquiz.pop_back() :     20    10
	*/
}
