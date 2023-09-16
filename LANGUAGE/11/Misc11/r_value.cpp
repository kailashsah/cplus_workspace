#include <iostream>
using namespace std;
/*
	Put simply, an lvalue is an object reference and an rvalue is a value.
	In C++, an rvalue is an unnamed object or a member of such an object which is not a reference.
	rvalue - an expression that could not be the left hand side of an assignment, but that could only be the right hand side.
*/
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
	cout << "int& a : " << a << endl;

	cout << "rvalue" << endl;
	int x{};
	cout << "int x{} : " << x << endl;

	int& ref1{ x };
	cout << "int& ref1{ x } : " << ref1 << endl;
	ref1 = 1;
	cout << "after ref1 = 1;: " << endl;
	cout << "value of x: " << x << endl;
	cout << "value of ref1: " << ref1 << endl;
	//int& ref2{ 5 }; // connot conver int to int&
	const int& ref3{ 5 };
	x = 3;
	cout << "const int& ref3{ 5 } : " << ref3 << endl;

	int&& ref5{ 5 };
	cout << "int&& ref5{ 5 }: " << ref3 << endl;

}

//int main()
//{
//	pointers_rvalue();
//	return 0;
//}

/*
	output-
		int& a : 1
		rvalue
		int x{} : 0
		int& ref1{ x } : 0
		after ref1 = 1;:
		value of x: 1
		value of ref1: 1
		const int& ref3{ 5 } : 5
		int&& ref5{ 5 }: 5
*/