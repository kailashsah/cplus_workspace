#include <iostream>
using namespace std;
/*
	1. demonstrate Abstract class pointer can hold and call methods of concrete classes.

	2.
*/

class Abstract
{
public:
    virtual void foo() = 0;
};

class Implementation : public Abstract
{
public:
    void foo() { std::cout << "Foo!" << std::endl; }
};

void call_foo(Abstract& obj) { obj.foo(); }
void call_foo(Abstract* obj) { obj->foo(); }

void run()
{
    // demonstrate Abstract class pointer can hold and call methods of concrete classes.
    Abstract* bar = new Implementation();
    
    call_foo(*bar); // call_foo(Abstract& obj)
    call_foo(bar);  // call_foo(Abstract* obj) 

    delete bar;
}

//int main()
//{
//	run();
//	return 0;
//}