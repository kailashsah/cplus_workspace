#include <iostream>

using namespace std;

struct B {
	string val_;
	B()
	{
		cout << "ctor called " << endl;
	}
	B(const B& val) { cout << "copy ctor called one parameter" << endl; }
	B(string&& val) : val_(std::move(val))  // 1.
	{
		// val_ = std::move(val); // 2.
		cout << "move ctor called for " << val_ << endl;
	}
	~B() {
		cout << "dtor for value : " << val_ << endl;
	}
};

void run_move_constructor() {

	string a;
	B b_a(string("a")); // these all call move constructor
	auto b2 = B("b1");
	auto* b1 = new B("b2");

	cout << endl << "B b_a2(B(\"a\")) : " << endl;
	B b_a2(B("a")); //move ctor called for a
	B b_a3 = B("a");

	cout << "prg ends" << endl;
}

int main()
{
	run_move_constructor();
	return 0;
}
/*
 output-
	move ctor called for a
	move ctor called for b1
	move ctor called for b0
	move ctor called for b2
	dtor for value : b0
	dtor for value : b1
	dtor for value : a

*/
