#include <iostream>
using namespace std;

class A
{
	int i;
	int y;
public:
	A() { cout << "default ctor"; };
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


	//A a = A( 1, 2 );// ctor 2 param
	//A a = { 1, 2 }; // ctor 2 param, if ini list not present
	//A a = A{ 1, 2 }; // ctor 2 param , if ini list not present
	//A a{ 1, 2 }; // ctor 2 param, if no ini list
	//A a{ 1, 2, 3 }; // ini list
	//A a = A{ 1 }; // ctor 1 param

	//A a { 1 }; // ctor 1 param
	//A a(1); // ok 

	//A a; // default 
	//a = A{ 1 }; // ctor 1 param -> m assign
	//a = A(1); // same
}

//int main()
//{
//	run_virtual_static();
//	return 0;	
//}
