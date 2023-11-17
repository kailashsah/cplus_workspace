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
	B& operator=(const B& arg) noexcept {
		cout << "assignment fn " << endl;
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

//1.
B&& func_rvalue_return() noexcept {
	//1.
	//return  move(B("rrr_func"));

	//2.
	B obj = B("obj_rrr_");
	return move(obj);
}

void run_rvalue_returned_by_func() {
	//1.
	B&& a = func_rvalue_return(); // not calling move function // 
	/*
		ctor called for rvalue argument obj_rrr_
		dtor for value : obj_rrr_
		run_rvalue_returned_by_func() ends here
	*/

	//2.
	//B& a = func_rvalue_return(); //cannot convert from 'B' to 'B &'

	//3.
	//B a = func_rvalue_return();// this crashes .. .. b is dangling object, read explaination 

	cout << "run_rvalue_returned_by_func() ends here" << endl;
	/*
		When a nameless temporary, not bound to any references, would be moved or copied into an object of the same cv-unqualified type, the copy/move is omitted. When that temporary is constructed, it is constructed directly in the storage where it would otherwise be moved or copied to. When the nameless temporary is the argument of a return statement, this variant of copy elision is known as RVO, "return value optimization".
		
		auto&& values = makeWidget().data();
			values will be dangling as binding an xvalue(expiring value) to a reference doesn't extend anythings lifetime.

		fm - https://stackoverflow.com/questions/27368236/return-value-or-rvalue-reference
	*/
}

//2.
B& func_lvalue_return() noexcept {
	//1.
	B obj = B("obj_rrr_");
	return obj;

	//2.
	//return (B&)B("obj_rrr_"); // same like (1.)

}
void run_lvalue_returned_by_func()
{
	B& a = func_lvalue_return();
	cout << "run_lvalue_returned_by_func() ends here" << endl;
	//cout << a.val_ << endl; // crashes here. // "a" obj is already destroyed, see output below.

	/*
		ctor called for rvalue argument obj_rrr_
		dtor for value : obj_rrr_
		run_lvalue_returned_by_func() ends here
	*/

	/*
		Returning a reference to an object being about to be destroyed is always wrong: the referenced object will be destroyed before it can be used in any form. Making the reference an rvalue reference doesn't change that, it just makes returning a temporary compile.

		Note that returning a temporary string by value will probably result in copy elision, i.e., the object is probably going to be constructed directly in the location where it is used. 
			see run_value_returned_by_func().
		If that doesn't happen the object will be moved if there is a move constructor for the return type (there is for std::string). Note that the same applies when returning a function local variable instead of the temporary.
		fm - https://stackoverflow.com/questions/29332516/return-rvalue-reference-vs-return-by-value-in-function-return-type
	*/
}
//3.
B func_value_return() noexcept {

	return B("obj_rrr_");
}
void run_value_returned_by_func()
{
	//B a = func_lvalue_return(); // lvalue version
	B a = func_value_return(); // if func_lvalue_return() called, it calls copy ctor
	cout << "run_lvalue_returned_by_func() ends here" << endl;

	/*
		it seems, it constructed the a obj at the place of caller.
			ctor called for rvalue argument obj_rrr_
			run_lvalue_returned_by_func() ends here
			dtor for value : obj_rrr_
	*/
}

int main()
{
	//run_copy_constructor();
	//run_move_ctor();
	// 
	//run_value_returned_by_func();
	//run_lvalue_returned_by_func();
	run_rvalue_returned_by_func();
	return 0;
}

