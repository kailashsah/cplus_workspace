#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <functional>

using namespace std;

namespace student_candies_inc {

	string ltrim(const string &str) {
		string s(str);

		s.erase(s.begin(),
				find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

		return s;
	}

	string rtrim(const string &str) {
		string s(str);

		s.erase(
				find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
				s.end());

		return s;
	}

	int* assign(int student_no, int candies) {

		int *student = NULL;

		// validate it
		if (student_no < 1 || candies < 1) {
			cout << endl << "candies and number of student can't be less than 1";
			return student;
		}
		if (student_no > 100) {
			cout << endl << "number of student can't be greater than 100";
			return student;
		}

		student = new int[student_no];
		memset(student, 0, sizeof(int) * student_no);

		int counter = 0;
		int iter = 0;
		while (candies > 0) {

			if (counter == student_no) {
				iter++;
				counter = 0;
			}

			int assign_candy = counter + 1 + (student_no * iter); // [if 2 students ]2 * 0, 2 * 1, 2 * 2
			if (assign_candy < candies)
				student[counter] += assign_candy;
			else
				student[counter] += candies;

			candies -= assign_candy;
			counter++;

		}

		// print
		for (int ctr = 0; ctr < student_no; ctr++)
			cout << student[ctr] << setw(4);

		return student;
	}

	int main() {
//	test
//	int *result = func(2 /*student*/, 2 /*candies*/);

		while (1) {
			string x_temp;

			do {
				cout << endl << "enter student : ";
				getline(cin, x_temp);
			} while (ltrim(rtrim(x_temp)).empty());

			int student = stoi(x_temp);

			do {
				cout << endl << "enter candies : ";
				getline(cin, x_temp);
			} while (ltrim(rtrim(x_temp)).empty());

			int candies = stoi(x_temp);

			int *result = assign(student /*student*/, candies /*candies*/);
			cout << endl;

			do {
				cout << "enter x to terminate, otherwise any key : ";
				getline(cin, x_temp);
			} while (ltrim(rtrim(x_temp)).empty());

			if (x_temp == "x")
				return 0;
		}

		return 0;
	}
}

int main()
{
	student_candies_inc ::main();
	return 0;
}
