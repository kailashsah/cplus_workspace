#include <iostream>
using namespace std;

/*
	1. If the cast fails and target-type is a pointer type, it returns a null pointer of that type.
	2. If the cast fails and target-type is a reference type, it throws an exception that matches a handler of type std::bad_cast.
	3. A dynamic_cast works only polymorphic base class because it uses this information to decide safe downcasting
	4. The primary purpose for the dynamic_cast operator is to perform type-safe downcasts
*/

class Parent {

public:
	virtual void foo() {
		cout << "Parent version" << endl;
	}
};

class Child : public Parent {
public:
	void foo() override {
		cout << "Child version" << endl;
	}
};

void run_virtual_inheritance_three()
{
	//2.
	// child -> parent == upcasting (safe)
	Parent* pPar = nullptr;
	Child* pChild = new Child;
	pPar = pChild; // implicit cast allowed
	pPar = (Parent*) pChild;
	pPar = dynamic_cast<Parent*> (pChild); // no harm in down_cast
	pPar->foo(); // child version

	//3.
	// parent -> child == downcasting (unsafe)
	
	Parent* pParr = new Parent;
	Child* pChildd = nullptr;
	//3.1
	//pChild = pPar; // cnnot convert, compile err // error C2440: '=': cannot convert from 'Parent *' to 'Child *'
	
	//3.2
	cout << endl << "(Child*)pParr; foo() :" << endl;
	pChildd = (Child*)pParr; // c-style cast like reinterpret_cast<> //not safe
	pChildd->foo();//parent version

	//3.3
	cout << endl << "dynamic_cast<Child*>(pParr); foo() :" << endl;
	pChildd = dynamic_cast<Child*>(pParr); //  safe
	if(pChildd)
		pChildd->foo();//parent version
	else
	{
		cout << "dynamic_cast<Child*>(pParr); failed" << endl;
	}

	//4.
	//use of the dynamic_cast operator
	//https://www.ibm.com/docs/en/zos/2.4.0?topic=expressions-dynamic-cast-operator-c-only

}

//int main()
//{
//	run_virtual_inheritance_three();
//	return 0;	
//}
