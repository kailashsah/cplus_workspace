//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <fstream>

#define _CRT_SECURE_NO_WARNINGS
using namespace std;

namespace ideal_num_3_5 {

//#define _CRT_SECURE_NO_WARNINGS

	string ltrim(const string &);
	string rtrim(const string &);



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

			// While num is divisible by 3, divide it by 3
			while (num % 3 == 0)
				num /= 3;

			// While num is divisible by 5, divide it by 5
			while (num % 5 == 0)
				num /= 5;

			// If num got reduced to 1 then it has
			// only 3 and 5 as prime factors
			if (num == 1)
				count++;
		}

		//1>e:\data\projects\drive\drive\ideal_numbers_3_5.cpp(52) : error C4996 : 'getenv' : This function or variable may be unsafe.Consider using _dupenv_s instead.To disable deprecation, use _CRT_SECURE_NO_WARNINGS.See online help for details.
			return count;
	}


	int main()
	{
		char* path;
		size_t len;
		//getenv(path, &len, "OUTPUT_PATH");
		path = getenv( "OUTPUT_PATH");
		//ofstream fout(getenv("OUTPUT_PATH"));
		ofstream fout(path);

		string low_temp;
		getline(cin, low_temp);

		long low = stol(ltrim(rtrim(low_temp)));

		string high_temp;
		getline(cin, high_temp);

		long high = stol(ltrim(rtrim(high_temp)));

		long result = getIdealNums(low, high);

		fout << result << "\n";

		fout.close();

		return 0;
	}

	string ltrim(const string &str) {
		string s(str);

		s.erase(
			s.begin(),
			find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
		);

		return s;
	}

	string rtrim(const string &str) {
		string s(str);

		s.erase(
			find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
			s.end()
		);

		return s;
	}

	/*int main()
	{
	ideal_num_3_5::main();

	}*/
}
