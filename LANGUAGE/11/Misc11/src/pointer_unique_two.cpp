#include <iostream>

#include <memory> // make_unique
#include <algorithm>
using namespace std;
#include <vector>


// assignment to smart pointer, free the memory on assignment(unique_ptr), also on out of scope for shared_ptr

class BaseUq {
public:
	virtual void foo() = 0;
	virtual ~BaseUq() { cout << "base dtor" << endl; }
};

class DerivedUq :public BaseUq {
public:
	void foo() { cout << "derived foo" << endl; }
	~DerivedUq() { cout << "derived dtor" << endl; }
};

void case_one_unique() {
	cout << endl << "case_one_unique() : " << endl;

	unique_ptr<BaseUq> baseObj = make_unique<DerivedUq>();
	baseObj->foo();

	cout << "reassignment of unique_ptr" << endl;
	baseObj = make_unique<DerivedUq>();
	baseObj->foo();
}

void case_two_unique(unique_ptr<BaseUq>& arg_ptr) {
	
	arg_ptr->foo();
}

void run_unique_ptr_two()
{
	//1.
	case_one_unique();

	//2. unique_ptr in argument
	cout << endl << "case_two_unique() unique_ptr in argument : " << endl;
	unique_ptr<BaseUq> baseObj = make_unique<DerivedUq>();
	case_two_unique(baseObj);
}

int main()
{
	run_unique_ptr_two();
	return 0;
}
