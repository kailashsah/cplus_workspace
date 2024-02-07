#include <iostream>
using namespace std;
/*
	1. It shows upcasting
*/

void run_multi_inheritance_v1();
void run_multi_inheritance_v2();
//
class top {
public:
	virtual void foo(void) { cout << "I am top foo\n"; }
};

class middle : public top {
public:
	virtual void foo(void) { cout << "I am middle foo\n"; }
	virtual void bar(void) { cout << "I am middle bar\n"; }
};

class lower : public middle {
public:
	virtual void foo(void) { cout << "I am lower foo()\n"; }
	void foo(int a) { cout << "I am lower int foo()\n"; }

	virtual void bar(void) { cout << "I am lower bar()\n"; }
};

void run_multi_inheritance_v1()
{
	cout << "run_multi_inheritance_v1" << endl;
	// Ques - 
	lower* l = new lower();
	top* t = dynamic_cast<top*>(l); // up cast
	
	if (t != nullptr)
		cout << "top* t = dynamic_cast<top*>(l) -  is not null " << endl;
	
	//t->bar(); // compliation error - top (parent) has no memeber as bar  (IMP)
	//t->foo(5); //  compliation error - function doesnot take 1 argu

	cout << endl;

	/*
		output - 
		run_multi_inheritance_v1
		top* t = dynamic_cast<top*> (l) -  is not null
	*/


}
void run_multi_inheritance_v2() {

	cout << "run_multi_inheritance_v2" << endl;
	// 2.1
	middle* middleObj = new middle();// to check vfptr while debugging
	
	// 2.2
	lower* l = new lower();
	middle* m = dynamic_cast<middle*> (l);
	if (m != nullptr)
		cout << "middle* m = dynamic_cast<middle*> (l) - is not null " << endl;
	m->bar(); 
	/*
		it'll call lower version 
		if virtual removed from lower & middle, then it will call middle version (IMP)
	*/ 
	m->foo(); // it'll call lower version
	
	cout << endl;
	/*
		output - 
		run_multi_inheritance_v2
		middle* m = dynamic_cast<middle*> (l) - is not null
		I am lower bar()
		I am lower foo()
	*/

}

//int main()
//{
//	run_multi_inheritance_v1();
//	run_multi_inheritance_v2();
//
//	return 0;
//}
