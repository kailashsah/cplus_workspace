#include <iostream>

#include <memory> // make_unique
#include <algorithm>
using namespace std;
#include <vector>

// assignment to smart pointer, free the memory on assignment(unique_ptr), also on out of scope for shared_ptr

class Base {
protected:
	string m_name;
public:
	Base(string name) :m_name{ name } {}
	virtual void foo() = 0;
	virtual ~Base() { cout << m_name << " base dtor" << endl; }
};

class Derived :public Base {

public:
	Derived(string name) : Base{ name } {}
	void foo() { cout << m_name << " derived foo" << endl; }
	~Derived() { cout << m_name << " derived dtor" << endl; }
};

void shared(shared_ptr<Base> baseObj); // fwd declaration

void shared(shared_ptr<Base> baseObj)
{
	cout << "reassignment of shared_ptr" << endl;
	//1.
	//baseObj = make_unique<Derived>();// if Derived(string name), default ctor would be removed thus compilation error 
	//2.
	baseObj = make_unique<Derived>("bb"); // assignment unique -> shared, makes old shared ref to zero  (IMP)
	baseObj->foo();

	//3.
	shared_ptr<Base> baseObj2(baseObj);// shows assigning of ptr return by make_unique() to shared_ptr objs
	shared_ptr<Base> baseObj3 = baseObj;
	cout << "baseObj3.use_count() : " << baseObj3.use_count() << endl; //3 bcoz of baseObj2, baseObj3
}

void run_shared_ptr_two() {
	shared_ptr<Base> baseObj{ new Derived("aa") };
	baseObj->foo(); //  derived foo
	shared(baseObj);
}

//int main()
//{
//	run_shared_ptr_two();
//	return 0;
//}

/*
	   aa derived foo
		reassignment of shared_ptr
		bb derived foo
		bb derived dtor
		bb base dtor
		aa derived dtor
		aa base dtor
	*/