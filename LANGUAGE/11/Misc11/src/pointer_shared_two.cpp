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

void shared(shared_ptr<Base> baseObj); // fwd declaration

void shared(shared_ptr<Base> baseObj)
{
    cout << "reassignment of shared_ptr" << endl;
    baseObj = make_unique<Derived>();
    baseObj->foo();
}

void run_shared_ptr_two() {
    shared_ptr<Base> baseObj{ new Derived() };
    baseObj->foo();
    shared(baseObj);
}

//int main()
//{
//	run_shared_ptr();
//	return 0;	
//}
