
#include <iostream>

#include <memory> // make_unique
#include <algorithm>
using namespace std;

//.................................................
#include <sstream> // istream_iterator
void run_input_stream_iterator()
{
	istringstream str{ "1 2 4" };
	auto itr = istream_iterator<int>(str);
	for (; itr != istream_iterator<int>(); ++itr)
	{
		cout << *itr;
	}
}
//.................................................
class A {
public:
    ~A() noexcept(false)
    {
        //cout << "dtor" << endl;
        //throw 1;  // terminate the program
        //
        // solution
        // 
		try {
			 throw 1;
		}
		catch (...)
		{

		}
	}
};

void run_dtor_exception()
{
    try {
        A a;
        A b;
        cout << "inside try" << endl;
        // dtor called for a, b
    }
    catch (...)
    {
        cout << "exc" << endl;
    }
    int i;
    cout << "int i " << endl;
    std::cout << "ends";
    return ;
}
//.................................................
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
void run_unique_ptr()
{
    unique_ptr<Base> baseObj = make_unique<Derived>();
    baseObj->foo();
    cout << "reassignment of unique_ptr" << endl;
    baseObj = make_unique<Derived>();
    baseObj->foo();
}
//.................................................
void shared(shared_ptr<Base> baseObj);
void run_shared_ptr(){
    shared_ptr<Base> baseObj{ new Derived() };
    baseObj->foo();
    shared(baseObj);
}
void shared(shared_ptr<Base> baseObj)
{
    
    cout << "reassignment of shared_ptr" << endl;
    baseObj = make_unique<Derived>();
    baseObj->foo();
}
//.................................................
//.................................................
//int main()
//{
//    run_shared_ptr();
//    //run_unique_ptr();
//    //run_dtor_exception();
//	//run_input_stream_iterator();
//}
