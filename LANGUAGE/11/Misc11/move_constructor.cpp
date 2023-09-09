#include <iostream>

using namespace std;

void move_constructor()
{
	struct B {
		string val_;
		B(string&& val) : val_(std::move(val))  // 1.
		{
			// val_ = std::move(val); // 2.
			cout << "move ctor called " << val_ << endl;
		}
		~B() {
			cout << val_ << endl;
		}
	};
	string a;
	B b_a(string("a")); // these all call move constructor
	auto b2 = B("b1");
	auto b0 = B("b0");
	auto* b1 = new B("b2");
}

