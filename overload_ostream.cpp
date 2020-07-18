#include <iostream>
#include <string>

using namespace std;

namespace overload_ostream {

	class Person {
	public:
		Person(const string& first_name, const string& last_name) : first_name_(first_name), last_name_(last_name) {}
		const string& get_first_name() const {
			return first_name_;
		}
		const string& get_last_name() const {
			return last_name_;
		}

	private:
		string first_name_;
		string last_name_;
		friend ostream & operator <<(ostream& os, Person& person);
	};
	// Enter your code here.
	ostream & operator <<(ostream& os, Person& person)
	{
		os << person.get_first_name();
		os << person.get_last_name();
		return os;
	}


	int main() {
		std::string first_name, last_name, event;
		getline(cin, first_name);
		getline(cin, last_name);
		getline(cin, event);
		//std::cin >> first_name >> last_name >> event;
		Person p = Person(first_name, last_name);
		cout << p << " " << event << endl;

		return 0;
	}

	/*int main()
	{
	overload_ostream::main();

	}*/
}