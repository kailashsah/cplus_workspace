#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <set>
#include <numeric>
#include <algorithm>
#include <list>


using namespace std;

namespace tuple {

	void find_contact()
	{
		vector <string> contacts;
		contacts.push_back("Ramesh007");
		contacts.push_back("Kavita");
		contacts.push_back("Sapna");
		contacts.push_back("Anmol");

		cout << "Contacts in record - ";
		for (auto item : contacts)
		{
			cout << setw(10) << item;
		}
		cout << endl;

		string input;
		cout << "enter search string :";
		getline(cin, input); // ltrim and rtrim is required

		if (input.empty())
		{
			cout << "Terminated!!!";
			return;
		}

		// complexity is O(1)
		for (auto item : contacts)
		{
			if (string::npos == item.find(input))
				continue;
			cout << setw(10) << item;
		}


		cout << endl << endl;
		cout << "Search finshed !";
		getchar();
	}


	void remove_first(vector<int>& vec, int num)
	{

		auto it = std::find(vec.begin(), vec.end(), num);
		vec.erase(it);
		return;

	}
	void sum_plus_minus()
	{

		vector<int> input;

		input.push_back(2);
		input.push_back(2);
		input.push_back(2);
		input.push_back(1);
		input.push_back(1);
		input.push_back(1);
		input.push_back(1);
		input.push_back(7);
		//input.push_back(1);
		input.push_back(5);

		int sum, half_sum = 0;
		sum = std::accumulate(input.begin(), input.end(), 0);
		sort(input.begin(), input.end());
		if (sum % 2 != 0)
			cout << "not possible" << endl;
		else
		{
			half_sum = sum / 2;
			cout << sum << endl;
		}

		int temp_sum = 0;

		int max = *max_element(input.begin(), input.end());
		remove_first(input, max);
		cout << "+" << max << setw(10); // first element
		temp_sum = max;


		int subtractor = abs(temp_sum - half_sum);
		while (temp_sum != half_sum) // half_sum is constant,  and we have to achieve
		{
			// subtractor is the differnce integer we need to complete half sum
			auto it = std::find(input.begin(), input.end(), subtractor);
			if (it != input.end()) {
				cout << "+" << *it << setw(10);
				temp_sum += *it;
				input.erase(it);
			}
			else
			{
				if (subtractor > 1)
				{
					// if half sum is not achieved than reduce it by one
					// and find it again
					subtractor -= 1;
				}
					

			}
		}

		for (auto item : input)
		{
			cout << "-" << item << setw(10);

		}

		cout << endl;

		getchar();

	}

	class Emp
	{
	private:
		string name;
		string code;
		int row_number;
		string emp_code;
		int k;
	public:
		Emp(string arg_name, string arg_code, int arg_row_number, string arg_emp_code) :
			name(arg_name), code(arg_code), row_number(arg_row_number), emp_code(arg_emp_code) {}

		string getName() { return name; }
		string getCode() { return code; }
		int getRowNumber() { return row_number; }
		string getEmpCode() { return emp_code; }

	};

	void row_number() ;
	void row_number()
	{
		/* scenario
		it should print in the specific format
		name - code - row number - emp code
		aamir - a1 - 1 - a11
		gaurav - g2 - 1 - g21
		gaurav - g3 - 2 - g32
		*/
		vector <string> names;
		names.push_back("gaurav");
		names.push_back("aamir");
		names.push_back("gaurav");


		sort(names.begin(), names.end());

		char first = '0';
		int count = 1, repeat = 1;
		list<Emp*> allEmp;

		for (auto item : names)
		{
			if (first != item.front())
			{
				first = item.front();
				repeat = 1;
			}
			else
				repeat++;

			Emp* emp = new Emp(item,
				first + to_string(count),
				repeat,
				first + to_string(count) + to_string(repeat));

			allEmp.push_back(emp);
			count++;
		}

		cout << endl;
		for (auto item : allEmp)
		{
			Emp* emp = item;
			cout << emp->getName() << setw(10) << emp->getCode() << setw(10)
				<< emp->getRowNumber() << setw(10) << emp->getEmpCode() << endl;
		}
		getchar();
	}

	int main()
	{
		// question (2)
		 find_contact();

		// question (3)
		// sum_plus_minus();

		// question (4)
		// row_number();


		return 0;
	}

	/*int main()
	{
	tuple::main();

	}*/
}
