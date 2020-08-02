//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <fstream>

#define _CRT_SECURE_NO_WARNINGS
using namespace std;

namespace ideal_num_3_5 {

	string ltrim(const string&);
	string rtrim(const string&);

	/*
	 * Complete the 'getIdealNums' function below.
	 *
	 * The function is expected to return a LONG_INTEGER.
	 * The function accepts following parameters:
	 *  1. LONG_INTEGER low
	 *  2. LONG_INTEGER high
	 */

	long getIdealNums(long low, long high) {
		int count = 0; // counter 

		for (long i = low; i <= high; i++) {
			long num = i;
			long num_dup = i;
			// While num is divisible by 3, divide it by 3
			while (num % 3 == 0)
				num /= 3;

			// While num is divisible by 5, divide it by 5
			while (num % 5 == 0)
				num /= 5;

			// If num got reduced to 1 then it has
			// only 3 and 5 as prime factors
			if (num == 1) {
				cout << num_dup << endl; // print all such numbers
				count++;
			}
		}

		return count;
	}

	int main() {

		cout << "ideal_num_3_5::main()" << endl;
		char *path;
		size_t len;
		//getenv(path, &len, "OUTPUT_PATH");
		path = getenv("OUTPUT_PATH");
		//ofstream fout(getenv("OUTPUT_PATH"));
		/*ofstream fout(path);

		 string low_temp;
		 getline(cin, low_temp);

		 long low = stol(ltrim(rtrim(low_temp)));

		 string high_temp;
		 getline(cin, high_temp);

		 long high = stol(ltrim(rtrim(high_temp)));*/

		long low = 1;
		long high = 20;
		long result = getIdealNums(low, high);

		cout << "total count is : " << result << endl;
		/*fout << result << "\n";

		 fout.close();
		 */
		return 0;
	}

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

}

/*int main() {
	ideal_num_3_5::main();

}*/

