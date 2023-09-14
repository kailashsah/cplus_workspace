// virtualmid.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
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
	virtual void foo(void) { cout << "I am lower foo\n"; }
	void foo(int a) { cout << "I am lower int foo\n"; }
	virtual void bar(void) { cout << "I am lower bar\n"; }
};
void run_multi_inheritance()
{
	// Ques - 
	lower* l = new lower();
	top* t = dynamic_cast<top*> (l);
	//t->bar(); // top has no memeber as bar
	//t->foo(5); // function doesnot take 1 argu

	middle* m = dynamic_cast<middle*> (l);
	m->bar(); // it'll call lower version if virtual removed from lower & middle
	m->foo(); // it'll call lower version
}
/*int main()
{

	 run_multi_inheritance();
	 return 0;
 }*/
