#include <iostream>
using namespace std;



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
	//Parent* pPar = nullptr;
	Parent* pPar = new Parent;
	Child* pChild = new Child;

	// child -> parent
	//pPar = pChild;
	//pPar = (Parent*) pChild;
	//pPar = dynamic_cast<Parent*> (pChild);
	//pPar->foo();

	// parent -> child
	//pChild = pPar; // cnnot convert, compile err 
	pChild = (Child*)pPar;
	pChild->foo();
}

//int main()
//{
//	run_virtual_inheritance_three();
//	return 0;	
//}
