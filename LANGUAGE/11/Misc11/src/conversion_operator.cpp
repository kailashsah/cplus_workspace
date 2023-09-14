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
		cout << "Conversion Ctor called" << endl;
	}
	Int& operator=(const Int&) {
		cout << " assignment called " << endl;
		return *this;
	}
	operator string()
	{
		cout << "Conversion Operator" << endl;
		return to_string(x);
	}
	~Int()
	{
		cout << "dtor called " << endl;
	}
};

void run_conversion_operator()
{
	Int obj(3);
	string str = obj;
	cout << " obj assignment" << endl;
	obj = 20.3;
	//string str2 = static_cast<string>(obj);
	//obj = static_cast<Int>(30);
}

//int main()
//{
//	run_conversion_operator();
//	return 0;	
//}
