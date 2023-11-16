#include <iostream>
using namespace std;

/*
	https://www.learncpp.com/cpp-tutorial/struct-aggregate-initialization/
*/
class A
{
	int i;
	int y;
public:
	A() { cout << "default ctor1" << endl; };
	A(int i) {
		cout << "ctor 1 param" << endl;
	}
	A(int i, int y) : i{ i } { cout << "ctor 2 param" << endl; }
	A(const A&) { cout << "copy" << endl; }
	A(A&& obj) { cout << "move" << endl; }
	A& operator=(A&&) { cout << "move assignment" << endl; return *this; }
	A& operator=(const A&) {
		cout << "assignent" << endl;
		return *this;
	}
	//A(initializer_list<int>) { cout << "ini list " << endl; }

};

void run_aggregate_initialization()
{
	cout << endl << "A a = A(1,2);" << endl;
	A a = A(1, 2);// ctor 2 param

	cout << endl << "A b = a;" << endl;
	A b = a; // copy

	cout << endl << "b = a;" << endl;
	b = a; // assignment


	A a1 = A(1, 2);// ctor 2 param
	cout << endl << "A a2 = { 1, 2 };" << endl;
	A a2 = { 1, 2 }; // ctor 2 param, if ini list not present

	cout << endl << "A a3 = A{ 1, 2 };" << endl;
	A a3 = A{ 1, 2 }; // ctor 2 param , if ini list not present

	cout << endl << "A a4{ 1, 2 };" << endl;
	A a4{ 1, 2 }; // ctor 2 param, if no ini list

	cout << endl << "A a5{ 1, 2, 3 };" << endl;
	//A a5{ 1, 2, 3 }; // ini list // todo 
	/*
		'initializing': cannot convert from 'initializer list' to 'A'
		// if A(initializer_list<int>) -- not present in class
	*/

	cout << endl << "A a6 = A{ 1 };" << endl;
	A a6 = A{ 1 }; // ctor 1 param

	cout << endl << "A a7 { 1 };" << endl;
	A a7{ 1 }; // ctor 1 param

	cout << endl << "A a8(1);" << endl;
	A a8(1); // ok 

	cout << endl << "A a9; " << endl;
	A a9; // default 

	cout << endl << "a9 = A{ 1 };" << endl;
	a9 = A{ 1 }; // ctor 1 param -> m assign

	cout << endl << "a9 = A(1);  " << endl;
	a9 = A(1); // same

	cout << endl << "A a10(A(1));  " << endl;
	A a10(A{}); // <= IMP
	/*
		A a10(A())
			will not create obj by A() .. so no output comes out of it
			A a10(A()); translated into  -  A a10( A(*)() ); // compiles ok, but do nothing
			in general A(*)() - function pointer

		 replace parentheses with braces to declare a variable -- A{}
		 A a10(A{}); translated into  -  A a10 = A{}; // OK

	*/
}

//int main()
//{
//	run_aggregate_initialization();
//	return 0;
//}

/*
	if A(initializer_list<int>) is present
	A a = A(1,2);
	ctor 2 param

	A b = a;
	copy

	b = a;
	assignent
	ctor 2 param

	A a2 = { 1, 2 };
	ini list

	A a3 = A{ 1, 2 };
	ini list

	A a4{ 1, 2 };
	ini list

	A a5{ 1, 2, 3 };
	ini list

	A a6 = A{ 1 };
	ini list

	A a7 { 1 };
	ini list

	A a8(1);
	ctor 1 param

	A a9;
	default ctor1

	a9 = A{ 1 };
	ini list
	move assignment

	a9 = A(1);
	ctor 1 param
	move assignment
*/
/*
	A(initializer_list<int>) not present
		A a = A(1,2);
		ctor 2 param

		A b = a;
		copy

		b = a;
		assignent
		ctor 2 param

		A a2 = { 1, 2 };
		ctor 2 param

		A a3 = A{ 1, 2 };
		ctor 2 param

		A a4{ 1, 2 };
		ctor 2 param

		A a5{ 1, 2, 3 };

		A a6 = A{ 1 };
		ctor 1 param

		A a7 { 1 };
		ctor 1 param

		A a8(1);
		ctor 1 param

		A a9;
		default ctor1

		a9 = A{ 1 };
		ctor 1 param
		move assignment

		a9 = A(1);
		ctor 1 param
		move assignment
*/