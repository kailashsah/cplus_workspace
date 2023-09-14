#include <iostream>
//import <iostream>;
using namespace std;
 

class Person
{
	std::string m_name;
	std::shared_ptr<Person> m_partner; // initially created empty

public:
	Person() {}
	Person(const std::string& name) : m_name(name)
	{
		std::cout << m_name << " created\n";
	}
	~Person()
	{
		std::cout << m_name << " destroyed\n";
	}

	friend bool partnerUp(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2)
	{
		if (!p1 || !p2)
			return false;

		cout << p1.use_count() << endl;
		//p1->m_partner = p2;


		//auto ricky{ std::make_shared<Person>("Ricky1") };
		//p1->m_partner = ricky ;
		//p2->m_partner = p1;

		std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

		return true;
	}
	ostream& print(ostream& os) const
	{
		os << "printing person" << endl;
		return os;
	}
};
ostream& operator<<(ostream& os, const Person& per) {
	return per.print(os);

}
inline Person& GetPerson()
{
	// check single instance
	static Person per;
	return per;
}

void run_shared_cyclic_dep()
{
	auto lucy{ std::make_shared<Person>("Lucy") }; // create a Person named "Lucy"

	auto ricky{ std::make_shared<Person>("Ricky") }; // create a Person named "Ricky"

	partnerUp(lucy, ricky); // Make "Lucy" point to "Ricky" and vice-versa

	cout << Person("aa");
	Person&& s = std::move(GetPerson());
	cout << &s << endl;
	Person&& s1 = std::move(GetPerson());
	cout << &s1 << endl;

}


//int main()
//{
//	run_shared_cyclic_dep();
//	return 0;
//}



