#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

namespace lambda {

	void abssort(vector<int>& elements);
	void use_of_constexpr();

	void abssort(vector<int>& elements)
	{
		std::sort(elements.begin(), elements.end(),
			[](int a, int b) mutable throw()-> int {
			return abs(a) < abs(b);
		});

	}

	void use_of_constexpr()
	{
		 auto Increment = [&](int n) throw() ->int {
			return n + 1;
		};

		//constexpr int (*inc)(int) 
		 int answer = Increment(10);
		cout << answer;


	}

	int main()
	{
		/*
		call of functions -
		1- use_of_constexpr
		2- abssort
		*/

		//use_of_constexpr();

		string count;
		getline(cin, count);
		int vect_count = stoi(count);
		vector<int> elements(vect_count);

		int vect_element = 0;
		for (vector<int>::iterator it = elements.begin(); it != elements.end(); it++)
		{
			string item;
			getline(cin, item);
			vect_element = stoi(item);
			*it = vect_element;
			//elements.push_back(vect_element);
		}

		//abssort(elements);


		for (vector<int>::iterator it = elements.begin(); it != elements.end(); it++)
		{
			cout << *it << " ";
		}
		getchar();
		return 0;
	}

	/*int main()
	{
		lambda::main();

	}*/
}
