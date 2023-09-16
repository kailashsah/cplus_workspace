#include <iostream>
#include <string>
using namespace std;


class Int {
	int x;

public:
	Int()
	{
		cout << "ctor default " << endl;
	}
	Int(int x_in = 0)
		//: x{ x_in }
		: x(x_in)
	{
		cout << "Parameterized Ctor called" << endl;
	}
	Int& operator=(const Int& arg) {
		cout << "assignment called " << endl;
		x = arg.x;
		return *this;
	}
	operator string()
	{
		cout << "Conversion Operator" << endl;
		return to_string(x);
	}
	~Int()
	{
		cout << "dtor called for x: " << x << endl;
	}
	void print() {
		cout << "value of obj.x : " << x << endl;
	}

};

void run_conversion_operator()
{
	Int obj(3);

	//1.
	cout << endl << "//1. operator string(): " << endl;
	string str = obj; // conversion op
	cout << str << endl;

	//2.
	cout << endl << "//2. obj assignment" << endl;
	obj = 20.3;
	/*
		20.3 calls the parametrized ctor & then assignment operator
		obj.operator=(Int(static_cast<int>(20.300000000000001)));

	*/
	obj.print();

	//3.
	cout << endl << "//3. move()" << endl;
	obj = move(30.3); //  obj.operator=(Int(static_cast<int>(std::move(20.300000000000001)))); 20.3 calls the parametrized ctor & then assignment operator

	//4.
	/*
		conversion translated in this way.
		int n = static_cast<int>(obj.operator int());  (IMP)

		for operator like this
		operator int()
		{
			cout << "Conversion Operator" << endl;
			return x;
		}
	*/

	cout << endl << "//5. string str2 = static_cast<string>(obj); - ";
	string str2 = static_cast<string>(obj); cout << str2 << endl;
	/*
		translated into -- string str2 = static_cast<string>(	static_cast<string>(obj.operator string())	);
	*/

	cout << endl << "//6. obj = static_cast<Int>(40);; - ";
	obj = static_cast<Int>(40); // obj.operator=(static_cast<Int>(Int(40))); // it create temp obj first
	obj.print();
}

int main()
{
	run_conversion_operator();
	return 0;
}

/*
	Parameterized Ctor called

	//1. operator string():
	Conversion Operator
	3

	//2. obj assignment
	Parameterized Ctor called
	assignment called
	dtor called for x: 20
	value of obj.x : 20

	//3. move()
	Parameterized Ctor called
	assignment called
	dtor called for x: 30

	//5. string str2 = static_cast<string>(obj); - Conversion Operator
	30

	//6. obj = static_cast<Int>(40);; - Parameterized Ctor called
	assignment called
	dtor called for x: 40
	value of obj.x : 40
	dtor called for x: 40
*/