//#include <bits/stdc++.h>


#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;
namespace min_sum {
	string ltrim(const string &);
	string rtrim(const string &);



	/*
	* Complete the 'minSum' function below.
	*
	* The function is expected to return an INTEGER.
	* The function accepts following parameters:
	*  1. INTEGER_ARRAY num
	*  2. INTEGER k
	*/

	int minSum(vector<int> num, int k) {

		/*
		go with k iterations
		in each iterations divide the element by 2 and check for sum
		after the last iteration the sum has to be minimum
		*/
		for (int i = 0; i < k; i++)
		{

			int max = *max_element(num.begin(), num.end());
			int replace_element = (int)ceil((double)max / 2);
			cout << ceil((double)max / 2);;
			replace(num.begin(), num.end(), max, replace_element);


		}
		int sum_of_elems = std::accumulate(num.begin(), num.end(), 0);
		return sum_of_elems;
	}


	int main()
	{
		//std::ofstream fout(getenv("OUTPUT_PATH"));

		string num_count_temp;
		getline(cin, num_count_temp);

		int num_count = stoi(ltrim(rtrim(num_count_temp)));

		vector<int> num(num_count);

		for (int i = 0; i < num_count; i++) {
			string num_item_temp;
			getline(cin, num_item_temp);

			int num_item = stoi(ltrim(rtrim(num_item_temp)));

			num[i] = num_item;
		}

		string k_temp;
		getline(cin, k_temp);

		int k = stoi(ltrim(rtrim(k_temp)));

		int result = minSum(num, k);


		cout << result << "\n";
		//fout << result << "\n";

		//fout.close();

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
	min_sum::main();

	}*/
}
