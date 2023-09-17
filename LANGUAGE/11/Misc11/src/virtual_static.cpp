#include <iostream>
using namespace std;

class  MyClass
{
public:
	MyClass() {}
	~MyClass() {}
	virtual   void foo() { std::cout << "\n base"<< endl; }
private:

};
class My2 :public MyClass
{
public:
	// hides :  virtual  void foo() { std::cout << "\n base"; }
	static void foo() { std::cout << "derived" << endl;  }// override
	//int foo() { return 0; }

	// usage


};

void run_virtual_static()
{
	//1.
	static My2 obj;
	static My2* pDerived = new My2();
	pDerived->foo(); // prints: derived .. also prints same if pDerived is non-static

	//2.
	My2* pParent = dynamic_cast<My2*>( new MyClass());  // downcast result in error
	if (!pParent)
		cout << "dynamic_cast<My2*>( new MyClass()) -- failed" << endl; // prints
	else
		pParent->foo(); // null ptr exception

	//3.
	cout << "dynamic_cast<MyClass*>(new My2()) : " << endl;
	MyClass* pParentt = dynamic_cast<MyClass*>(new My2());  
	if (!pParentt)
		cout << "dynamic_cast<MyClass*>(new My2()) -- failed" << endl;
	else
		pParentt->foo(); // base .. it wouldnot call the static version of foo()

	//4.
	cout << "end"; // not printed if prg terminates
}

//int main()
//{
//	run_virtual_static();
//	return 0;	
//}
