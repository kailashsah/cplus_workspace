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
void run_class_members()
{
}

//int main()
//{
//	run_virtual_static();
//	return 0;	
//}
