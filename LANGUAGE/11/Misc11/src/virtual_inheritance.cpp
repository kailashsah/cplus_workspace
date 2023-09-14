#include <iostream>
using namespace std;

class A
{
public:
	virtual ~A() {}
	virtual void foo() { cout << endl; cout << "A::foo()"; }
	virtual void bar() {}
};

class B : public virtual A
{

public:
	void test() { cout << endl;  cout << "B::test"; }


};
class C : public virtual A
{
public:
	void bar() { cout << endl; printf("\n c::bar"); }
};

class D : public B, public C
{
};

void run_virtual_inheritance() {
	D obj;
	obj.bar();cout << endl;
	
	obj.test(); // why test is called here, given its not a virtual
	obj.foo();

	//
	A* ptr = new A();
	B* ptrD = dynamic_cast <B*> (ptr);
	ptrD->test();

	//
	A* obj_A = new D();
	obj_A->foo();
}

//int main()
//{
//	run_virtual_inheritance();
//	return 0;	
//}
