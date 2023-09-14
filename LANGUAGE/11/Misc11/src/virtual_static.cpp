#include <iostream>
using namespace std;

class  MyClass
{
public:
	MyClass() {}
	~MyClass() {}
	virtual   void foo() { std::cout << "\n base"; }
private:

};
class My2 :public MyClass
{
public:
	// hide :  virtual  void foo() { std::cout << "\n base"; }
	static void foo() { std::cout << "\n derived"; }// override
	//int foo() { return 0; }

	// usage


};

void run_virtual_static()
{
	static My2 obj;
	static My2* pParent = new My2();
	pParent->foo(); // prints: derived

	//My2* pParent = dynamic_cast<My2*>( new MyClass());  // downcast result in error
	//pParent->foo(); // null ptr exception
}

//int main()
//{
//	run_virtual_static();
//	return 0;	
//}
