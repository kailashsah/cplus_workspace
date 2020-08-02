#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

namespace max_space {
	/*
	intput x for total segment
	intput number of array elements [4,5,6,7]
	divide the elements in segment like [4,5], [5,6], [6,7]
	get the min of all sements
	get he maximum of all minimumns
	*/

	string ltrim(const string &);
	string rtrim(const string &);



	/*
	* Complete the 'segment' function below.
	*
	* The function is expected to return an INTEGER.
	* The function accepts following parameters:
	*  1. INTEGER x
	*  2. INTEGER_ARRAY space
	*/

	int getMin(vector<int> space)
	{
		vector<int>::iterator ptr;
		int min = space[0];
		for (ptr = space.begin(); ptr < space.end(); ptr++)
			if (*ptr < min)
				min = *ptr;
		return min;
	}
	int segment(int x, vector<int> space) {
		// obsolete funciton
		// this funciton is not possible because < or > is not possible with iterators
		if (x == 1)
		{
			//	*min_element(space.begin(), space.end(), 0);
			return getMin(space);
		}
		vector<int>::iterator ptr, ptrNext;
		int min = 0;
		int max = space[0];
		for (ptr = space.begin(); ptr < space.end(); ptr = ptr + (x - 1))
		{
			min = *ptr;
			ptrNext = ptr;
			if (ptrNext == space.end())
				return max;
			for (; ptrNext < space.end() && ptrNext < (ptr + x);)
			{
				if (*ptrNext < min)
					min = *ptrNext;

				ptrNext++;
			}
			if (max < min)
				max = min;
		}

		return max;
	}

	int segment_1(int x, vector<int> space) {


		if (x == 1)
		{
			//	*min_element(space.begin(), space.end(), 0);
			return getMin(space);
		}
		//vector<int>::iterator ptr, ptrNext;
		unsigned int index = 0;
		unsigned int index_next = 0;
		int min = 0;
		int max = space[0];
		for (index = 0; index < space.size(); index = index + (x - 1))
		{
			min = space[index];
			index_next = index;
			if (index_next >= space.size() - 1)
				return max;
			for (; index_next < space.size() && index_next < (index + x);)
			{
				if (space[index_next] < min)
					min = space[index_next];

				index_next++;
			}
			if (max < min)
				max = min;
		}

		return max;
	}
	int main()
	{
		//ofstream fout(getenv("OUTPUT_PATH"));

		string x_temp;
		getline(cin, x_temp);

		int x = stoi(ltrim(rtrim(x_temp)));

		string space_count_temp;
		getline(cin, space_count_temp);

		int space_count = stoi(ltrim(rtrim(space_count_temp)));

		vector<int> space(space_count);

		for (int i = 0; i < space_count; i++) {
			string space_item_temp;
			getline(cin, space_item_temp);

			int space_item = stoi(ltrim(rtrim(space_item_temp)));

			space[i] = space_item;
		}

		int result = segment_1(x, space);
		cout << "maximum of minimum is " << result;
		//fout << result << "\n";

		//fout.close();
		getchar();
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
		::max_space::main();
	}*/
}
