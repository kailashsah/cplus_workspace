#include <iostream>
using namespace std;

int bin_search(int key, int* a, int l, int h) {
	if (l < h) {


		int mid = (l + h) / 2;
		if (a[mid] == key)
			return mid;
		if (key < a[mid])
			bin_search(key, a, l, mid - 1);
		else if (key > a[mid]) {
			bin_search(key, a, mid + 1, h);

		}
	}
	else
	{
		int i = 0;
		return 999;
	}
	return 999;
}


void run_binary_search() {
	int a[10] = { 1,2,3,4,5,16,17,18,19,20 };
	//cout << bin_search(19, a, 0, 9) << endl;
	cout << bin_search(100, a, 0, 9);
	cout << a[bin_search(100, a, 0, 9)];
}


//int main()
//{
//	run_binary_search();
//	return 0;
//}
