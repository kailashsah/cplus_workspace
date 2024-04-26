#include <iostream>
using namespace std;
/*
	1. func() is called by derived class but it is not present in derived class, instead it exists in base class.
		what will happen it will be called or not?

	2.
*/

class base {
public:
	virtual void fun1() = 0;
	void func2() {
		cout << "base func2" << endl;
		fun1();
	}
};

class derived :public base
{
public:
	//1.
	void fun1() 
	{
		cout << "derived fun1()" << endl;
	}

	//2. void fun2(int) //if this is defined insted of above -	Error	C2259	'derived': cannot instantiate abstract class	

};

void run_derived_class() {

	derived* der_obj = new derived;
	der_obj->func2(); // func2() not present present in child class
	/*
		base func2
		derived fun1()
	*/
}

//int main()
//{
//	run_derived_class();
//	return 0;
//}