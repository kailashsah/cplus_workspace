#include <iostream>
using namespace std;

struct S {
	int a = 0;
	int& get()
	{
		return a;
	}
};

void pointers_rvalue()
{
	S s;
	int& a = s.get();
	s.get()++;
	cout << a << endl;

	cout << "rvalue";
	int x{};
	cout << x << endl;
	int& ref1{ x };
	cout << ref1 << endl;
	ref1 = 1;
	cout << x << endl;
	cout << ref1 << endl;
	//int& ref2{ 5 }; // connot conver int to int&
	const int& ref3{ 5 };
	x = 3;
	cout << ref3 << endl;

	int&& ref5{ 5 };

}

