#include <iostream>
#include <vector>
#include <queue>

using namespace std;
//.................................................

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

