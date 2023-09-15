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
	A() { cout << "default ctor1"; };
	A(int i) {
		cout << "ctor 1 param" << endl;
	}
	A(int i, int y) : i{ i } { cout << "ctor 2 param" << endl; }
	A(const A&) { cout << "copy" << endl; }
	A(A&&) { cout << "move" << endl; }
	A& operator=(A&&) { cout << "m assign" << endl; return *this; }
	A& operator=(const A&) { cout << "assign" << endl; }
	//A(initializer_list<int>) { cout << "ini list " << endl; }

};

void run_aggregate_initialization()
{
	A a = A(1,2);// ctor 2 param
	A b = a; // copy
	b = a; // assignment


	A a1 = A( 1, 2 );// ctor 2 param
	A a2 = { 1, 2 }; // ctor 2 param, if ini list not present
	A a3 = A{ 1, 2 }; // ctor 2 param , if ini list not present
	A a4{ 1, 2 }; // ctor 2 param, if no ini list
	//A a5{ 1, 2, 3 }; // ini list // todo
	A a6 = A{ 1 }; // ctor 1 param

	A a7 { 1 }; // ctor 1 param
	A a8(1); // ok 

	A a9; // default 
	a9 = A{ 1 }; // ctor 1 param -> m assign
	a9 = A(1); // same
}

//int main()
//{
//	run_aggregate_initialization();
//	return 0;	
//}
