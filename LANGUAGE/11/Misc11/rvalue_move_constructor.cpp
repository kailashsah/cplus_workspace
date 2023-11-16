#include <iostream>

using namespace std;

struct B {
	string val_{ "default_val" };
	B()
	{
		cout << "ctor called " << endl;
	}
	B(string& ar)
	{
		cout << "ctor called for lvalue argument" << endl;
	}
	//1.
	B(string&& val) : val_(std::move(val))  // 1.
	{
		// val_ = std::move(val); // 2.
		cout << "ctor called for rvalue argument " << val_ << endl;
	}
	//2.
	B(const B& val) { cout << "copy ctor " << endl; }

	//1.
	/*B(B&& val) noexcept {
		val_ = val.val_;

		cout << "move copy ctor " << endl;
		// "val" will die there ( if rvalue provided  move(B("string_move_ctor_")) ) & prints dtor for value : string_move_ctor_ -- imp

	}
	*/

	//2.  for improved performance 

	B(B&& val) noexcept {
		cout << "move copy ctor " << endl;
		*this = move(val); // calling move assignment //Use move semantics to improve performance


		// "val" will die there ( if rvalue provided  move(B("string_move_ctor_")) ) & prints dtor for value : string_move_ctor_ -- imp

	}
	/*
			If you provide both a move constructor and a move assignment operator for your class, you can eliminate redundant code by writing the move constructor to call the move assignment operator. The following example shows a revised version of the move constructor that calls the move assignment operator:
		*/
	B& operator=(B&& arg) noexcept {
		cout << "move assignment fn " << endl;
		if (this != &arg) {
			//1. free existing resource.
			val_ = {}; // or delete Val_

			//2. copy data pointer
			val_ = arg.val_;

			//3. release data pointer from source object.
			arg.val_ = {};  // arg.Val_ = nullptr			

		}

		return *this;
	}


	//2.
	~B() {
		cout << "dtor for value : " << val_ << endl;
	}
};

void run_copy_constructor() {

	string a;
	B b_a(string("a")); // these all call - ctor called for rvalue argument
	auto b2 = B("b1");
	auto* b1 = new B("b2");

	cout << endl << "B b_a2(B(\"a\")) : " << endl;
	B b_a2(B("a"));
	B b_a3 = B("a");

	cout << "prg ends" << endl;
}
/*
	ctor called for rvalue argument a
	ctor called for rvalue argument b1
	ctor called for rvalue argument b2

	B b_a2(B("a")) :
	ctor called for rvalue argument a
	ctor called for rvalue argument a
	prg ends
	dtor for value : a
	dtor for value : a
	dtor for value : b1
	dtor for value : a
*/
void run_move_ctor() {
	//1.
	B b_a4 = move(B("string_move_ctor_"));// move copy ctor // see ouput, it calls dtor also 

	//2.
	cout << "---------------" << endl;
	B b_a5;
	b_a5 = move(b_a4);// move assignment ctor
	cout << b_a4.val_ << endl; // prints empty

	cout << "fn ends" << endl;
}
/*
	ctor called for rvalue argument string_move_ctor_
	move copy ctor
	move assignment fn
	dtor for value : 
	---------------
	ctor called
	move assignment fn

	fn ends
	dtor for value : string_move_ctor_
	dtor for value :
*/


//int main()
//{
//	run_copy_constructor();
//	//run_move_ctor();
//	return 0;
//}

