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
	cout << "int& a : " << a << endl; //1

	cout << "rvalue" << endl;
	int x{};
	cout << "int x{} : " << x << endl; // 0

	int& ref1{ x };
	cout << "int& ref1{ x } : " << ref1 << endl;
	ref1 = 1;
	cout << "after ref1 = 1;: " << endl;
	cout << "value of x: " << x << endl;// 1
	cout << "value of ref1: " << ref1 << endl; //1

	//int& ref2{ 5 }; // connot conver int to int&

	const int& ref3{ 5 };
	cout << "const int& ref3{ 5 } : " << ref3 << endl;//5

	int&& ref5{ 5 };
	cout << "int&& ref5{ 5 }: " << ref3 << endl; //5

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