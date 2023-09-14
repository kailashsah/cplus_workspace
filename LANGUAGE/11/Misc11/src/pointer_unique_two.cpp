#include <iostream>

#include <memory> // make_unique
#include <algorithm>
using namespace std;
#include <vector>


// assignment to smart pointer, free the memory on assignment(unique_ptr), also on out of scope for shared_ptr

class Base {
public:
    virtual void foo() = 0;
    virtual ~Base() { cout << "base dtor" << endl; }
};

class Derived :public Base {
public:
    void foo() { cout << "derived foo" << endl; }
    ~Derived() { cout << "derived dtor" << endl; }
};

void run_unique_ptr_two()
{
    unique_ptr<Base> baseObj = make_unique<Derived>();
    baseObj->foo();
    
    cout << "reassignment of unique_ptr" << endl;
    baseObj = make_unique<Derived>();
    baseObj->foo();
}


//int main()
//{
//	run_unique_ptr_two();
//	return 0;	
//}
