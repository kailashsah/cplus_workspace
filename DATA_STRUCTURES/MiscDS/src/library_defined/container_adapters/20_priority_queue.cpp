#include <iostream>
#include <vector>
#include <queue>

using namespace std;
/*
	1. A priority queue in c++ is a type of container adapter, which processes only the highest priority element, i.e. the first element will be the maximum of all elements in the queue, and elements are in decreasing order. 
		Here priority means {fixed_order}

	2. STL Priority Queue is the implementation of Heap Data Structure.

	3. Priority queues are built on the top of the max heap and use an array or vector as an internal structure.
*/


void heap_min() {
	priority_queue <int, vector<int>, greater<int> > minheap; // < type, container, class Compare >
	minheap.push(3);
	minheap.push(6);
	minheap.push(9);
	while (minheap.empty() == false) {
		cout << minheap.top() << " ";
		minheap.pop();
	}
	cout << endl;
	//...........................

	cout << "max heap :" << endl;
	priority_queue <int, deque<int>, less<int> > maxheap;
	maxheap.push(3);
	maxheap.push(6);
	maxheap.push(9);
	while (maxheap.empty() == false) {
		cout << maxheap.top() << " ";
		maxheap.pop();
	}
}


//int main()
//{
//	heap_min();
//	return 0;
//}

