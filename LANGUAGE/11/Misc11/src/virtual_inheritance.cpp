#include <iostream>
using namespace std;

/*
	https://www.freecodecamp.org/news/what-is-virtual-inheritance/
*/

class InheritBase
{
public:
	virtual ~InheritBase() {}
	virtual void foo() { cout << "InheritBase::foo()" << endl;; }
	virtual void bar() { cout << "InheritBase::bar()" << endl;; }
};

class B : virtual public InheritBase
{

public:
	void test() { cout << "B::test" << endl; }

	//void bar() {
	//	printf("\n c::bar"); cout << endl;
	//	//'DHybrid': ambiguous inheritance of 'void InheritBase::bar(void)'	
	//}

};
class C : virtual public InheritBase
{
public:
	void bar() {
		printf("\n c::bar"); cout << endl;
	}
};

class DHybrid : public B, public C
{
};

void run_virtual_inheritance() {
	DHybrid obj;

	//1.
	cout << endl << "DHybrid bar() : " << endl;
	obj.B::bar(); // class B copy of bar()

	//2.
	cout << endl << "DHybrid test() : " << endl;
	obj.test(); // why test is called here, given its not a virtual  (IMP)
	/*
		translated into
		 static_cast<B&>(obj).test();

		 reason - for non-virutual methods, it links statically not dynamically
	*/

	//3.
	cout << endl << "DHybrid foo() : " << endl;
	obj.foo(); // static_cast<InheritBase&>(obj).foo();

	//4.
	cout << endl << "dynamic_cast <B*> (ptrBase) test() : " << endl;
	InheritBase* ptrBase = new InheritBase();
	B* ptrB = dynamic_cast <B*> (ptrBase); //// downcasting always fails if different polymorphic type
	ptrB->test(); // though ptr is null but it successfully called test() & prints "B::test"   (IMP)  
	/*
		1. When a non-virtual function is called the implementation must use the static type of the object on which the function is being called to determine the correct function to call. A function stored in a vtable accessed by a vptr will be dependent on the dynamic type of the object, not any static type of a reference or pointer through which it is being accessed.
		https://stackoverflow.com/questions/12661292/c-does-a-vtable-contains-pointers-to-non-virtual-functions

		2. As calls to non-virtual methods can be resolved during compilation (since compiler knows the addresses of non virtual functions), the compiler generates instructions to call them 'directly' (i.e. statically).

		There is no reason to go through vtable indirection mechanism for methods which are known during compiling.
	*/
	//ptrB->foo();//nullptr exception .. terminates

	//5.
	cout << endl << "InheritBase* obj_A = new DHybrid(); foo() : " << endl;
	InheritBase* obj_A = new DHybrid();
	obj_A->foo(); // prints "InheritBase::foo()"

	//6.
	cout << endl << "B* ptrBObj = nullptr; test() : " << endl;
	B* ptrBObj = nullptr;
	ptrBObj->test(); // prg doesn't break, calling fn from nullptr //since compiler knows the addresses of non virtual functions
}

//int main()
//{
//	run_virtual_inheritance();
//	return 0;	
//}
