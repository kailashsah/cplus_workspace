#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <set>
#include <numeric>
#include <algorithm>
#include <list>

using namespace std;

namespace tuple_questions {

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

	void get_contacts(vector<string> &contacts) {

		cout << "Enter the number of contacts you would like to add :";
		int contact_size;
		cin >> contact_size;
		cout << "Enter contacts" << endl;
		string temp;
		for (int i = 0; i < contact_size; i++) {

			getline(cin, temp);

			contacts.push_back(rtrim(ltrim(temp)));
		}

	}

	void search_contact() {

		const int PRINT_DISTANCE = 10;
		vector<string> contacts; // deque could be used if the space required is high
		get_contacts(contacts); // get contacts from user

		cout << "Contacts in record - ";
		for (auto item : contacts) {
			cout << setw(PRINT_DISTANCE) << item;
		}
		cout << endl;

		string input;
		cout << "enter search string :";
		getline(cin, input);

		input = rtrim(ltrim(input));
		if (input.empty()) {
			cout << "Input is empty, program terminated!!!";
			return;
		}

		// complexity is O(1)
		for (auto item : contacts) {
			if (string::npos == item.find(input))
				continue;
			cout << setw(PRINT_DISTANCE) << item;
		}

		cout << endl;
		cout << "Enter to exit ";
		getchar();
	}

	void remove_first(vector<int> &vec, int num) {

		auto it = std::find(vec.begin(), vec.end(), num);
		vec.erase(it);
		return;

	}

	void get_plus_minus_input(vector<int> &input) {

		cout << "Enter the number of integers you would like to add :";
		int input_size;
		cin >> input_size;
		cout << "Enter integers : ";
		string temp;

		for (int i = 0; i < input_size; i++) {

			getline(cin, temp);

			temp = ltrim(rtrim(temp));
			if (!temp.empty()) {
				int iTemp = stoi(temp);
				input.push_back(iTemp);

			} else
				i--;
		}

	}

	void sum_plus_minus() {

		const int ELEMENT_DISTANCE = 4;
		vector<int> input;
		get_plus_minus_input(input); // get input from user

		cout << "Elements entered are :";
		for (auto item : input) {
			cout << item << setw(ELEMENT_DISTANCE);

		}
		cout << endl;

		int sum, half_sum = 0;
		sum = std::accumulate(input.begin(), input.end(), 0);
		sort(input.begin(), input.end());
		if (sum % 2 != 0)
			cout << "not possible" << endl;
		else {
			half_sum = sum / 2;
			cout << "half of the total sum is :" << sum << endl;
		}

		int temp_sum = 0;

		int max = *max_element(input.begin(), input.end());
		remove_first(input, max);

		cout << "Output of the program is :";
		cout << "+" << max << setw(ELEMENT_DISTANCE); // first element
		temp_sum = max;

		int subtractor = abs(temp_sum - half_sum);
		while (temp_sum != half_sum) // half_sum is constant,  and we have to achieve
		{
			// subtracter is the difference integer we need to complete half sum
			auto it = std::find(input.begin(), input.end(), subtractor);
			if (it != input.end()) {
				cout << "+" << *it << setw(10);
				temp_sum += *it;
				input.erase(it);
			} else {
				if (subtractor > 1) {
					// if half sum is not achieved than reduce it by one
					// and find it again
					subtractor -= 1;
				}

			}
		}

		for (auto item : input) {
			cout << item << "-" << setw(ELEMENT_DISTANCE);

		}

		cout << endl;
		cout << "Enter to exit ";
		getchar();

	}

	class Emp {
	private:
		string name;
		string code;
		int row_number;
		string emp_code;
		int k = 0;
	public:
		Emp(string arg_name, string arg_code, int arg_row_number,
				string arg_emp_code) :
				name(arg_name), code(arg_code), row_number(arg_row_number), emp_code(
						arg_emp_code) {
		}

		string getName() {
			return name;
		}
		string getCode() {
			return code;
		}
		int getRowNumber() {
			return row_number;
		}
		string getEmpCode() {
			return emp_code;
		}

	};

	void get_row_number_input(vector<string> &input) {

		cout << "Enter the number of candidate you would like to add :";
		int input_size;
		cin >> input_size;
		cout << "Enter candidate's name : ";
		string temp;

		for (int i = 0; i < input_size; i++) {

			getline(cin, temp);

			temp = ltrim(rtrim(temp));
			if (!temp.empty())
				input.push_back(temp);
			else
				i--;
		}

	}

	void row_number() {
		/* scenario
		 it should print in the specific format
		 name - code - row number - emp code
		 aamir - a1 - 1 - a11
		 gaurav - g2 - 1 - g21
		 gaurav - g3 - 2 - g32
		 */

		const int ELEMENT_DISTANCE = 4;
		vector<string> names;
		get_row_number_input(names);

		sort(names.begin(), names.end());

		char first = '0';
		int count = 1, repeat = 1;
		list<Emp*> allEmp;

		for (auto item : names) {
			if (first != item.front()) {
				first = item.front();
				repeat = 1;
			} else
				repeat++;

			Emp *emp = new Emp(item, first + to_string(count), repeat,
					first + to_string(count) + to_string(repeat));

			allEmp.push_back(emp);
			count++;
		}

		cout << endl;
		cout << "program output :" << endl;
		for (auto item : allEmp) {
			Emp *emp = item;
			cout << emp->getName() << setw(ELEMENT_DISTANCE) << emp->getCode()
					<< setw(ELEMENT_DISTANCE) << emp->getRowNumber()
					<< setw(ELEMENT_DISTANCE) << emp->getEmpCode() << endl;
		}

		cout << "Enter to exit ";
		getchar();
	}

	int main() {

		// search_contact();  // question (2)

		//sum_plus_minus();  // question (3)

		// row_number();  // question (4)

		return 0;
	}

}

int main() {
	tuple_questions::main();

}
