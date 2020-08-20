#include <iostream>
#include <iomanip>
#include  <cstring>
using namespace std;

namespace student_candies {
	int* dist(int *arr, int n, int &k, int nextItr) {

		if (nextItr == 0) {
			for (int i = 0; i < n; i++) {

				if (k > i + 1) {
					arr[i] += i + 1;
					k -= i + 1;
				} else {
					if (k == i) {
						arr[i] += k;
						k -= i;
					} else {
						arr[i] += k;
						k = 0;

					}
				}
			}
		}

		else {

			for (int i = 0; i < n; i++) {

				if (k > n * nextItr + i + 1) {
					arr[i] += n * nextItr + i + 1;
					k -= (n * nextItr + i + 1);
				} else {
					if (k > 0) {
						arr[i] += k;
						k = 0;
					}
				}
			}

		}

		return arr;
	}
	int* func(int n, int k) {

		cout << endl;
		cout << "student no is " << n << endl;
		cout << "candies no is " << k << endl;

		int *arr = new int[k];
		memset(arr, 0, sizeof(int) * k);
		if (k < 1) {
			cout << "candies shuld not be zero " << endl;
			return arr;
		}

		if (n > 100)
			return arr;

		arr = dist(arr, n, k, 0);

		int nextItr = 1;
		while (k > 0) {
			arr = dist(arr, n, k, nextItr);
			nextItr++;
		}

		cout << endl;
		for (int i = 0; i < n; i++) {
			cout << arr[i] << setw(4);
		}
		return arr;
	}

	int main() {
//	test
//	int *result = func(2 /*student*/, 2 /*candies*/);

		while (1) {
			string x_temp;
			cout << "enter student" << endl;
			getline(cin, x_temp);

			int student = stoi(x_temp);

			cout << "enter candies" << endl;
			getline(cin, x_temp);
			int candies = stoi(x_temp);

			int *result = func(student /*student*/, candies /*candies*/);
			cout << endl;
		}

		return 0;
	}
}
