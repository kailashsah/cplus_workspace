#include <iostream>
using namespace std;

namespace circular_queue {

//(front )4 - 3 - 2 -  (back) -> (front)

//  1 - 2 - 3 - 4 - 5
//  E - E - 3 - 4 - 5
//  6 - E - 3 - 4 - 5
//  6 - 7 - 3 - 4 - 5

	struct queue_zscaler {
		int back, front;
		int *arr;
		int size;

		void addBack(int val);
		void removeFront();
		void print ();
	};

	void queue_zscaler::removeFront() {

		if (front == -1) {
			cout << "empty" << endl;
			return;
		}
		if (front == back)
		front = back = - 1;
		else if (front == size - 1)
		front = 0;
		else
		front++;
	}
	void queue_zscaler::addBack(int val) {

		// queue is full
		if (front == 0 && back == size - 1 && (back == front - 1)) {
			cout << "queue is full" << endl;
			return;
		}

		// empty queue
		if (front == -1) {
			back = front = 0;
			arr[back] = val;
		}
		// circular rotation (last element)
		else if (back == size - 1 && front != 0) {
			back = 0;
			arr[back] = val;

		}

		else {
			back++;
			arr[back] = val;
		}
	}

	int main() {
		return 0;
	}

}
