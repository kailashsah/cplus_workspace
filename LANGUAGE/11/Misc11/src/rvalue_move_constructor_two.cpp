#include <iostream>
using namespace std;
/*
	1. what will happend if no move functions defined.
*/

struct B2 {
	string val_{ "default_val" };
	B2()
	{
		cout << "ctor called " << endl;
	}
	B2(string& ar)
	{
		cout << "ctor called for lvalue argument" << endl;
		val_ = ar;
	}
	//1.
	B2(string&& val) : val_(std::move(val))  // 1.
	{
		// val_ = std::move(val); // 2.
		cout << "ctor called for rvalue argument " << val_ << endl;
	}
	//2.
	B2(const B2& val) {
		cout << "copy ctor " << endl;
		val_ = val.val_;
	}

	B2& operator=(const B2& arg) {
		cout << "assignment function " << endl;
		val_ = arg.val_;
		return *this;
	}
	//1.
	/*B2(B&& val) noexcept {
		val_ = val.val_;

		cout << "move copy ctor " << endl;
		// "val" will die there ( if rvalue provided  move(B("string_move_ctor_")) ) & prints dtor for value : string_move_ctor_ -- imp

	}
	*/

	//2. move functions not written, no problems, it calls normal ctors
	
	//3. move functions deleted, see output error
	//B2(B2&&) = delete;
	//B2& operator=(B2&&) = delete;

	~B2() {
		cout << "dtor for value : " << val_ << endl;
	}
};

void run_move_ctorr() {
	//1.
	B2 b_a4 = move(B2("string_value"));// copy ctor <=
	/*
		if B2(B2&&) = delete;
		error C2280: 'B2::B2(B2 &&)': attempting to reference a deleted function
	*/

	//2.
	cout << "---------------" << endl;
	B2 b_a5;
	b_a5 = move(b_a4);//  assignment fn <=
	/*
		if B2& operator=(B2&&) = delete;
		error C2280: 'B2 &B2::operator =(B2 &&)': attempting to reference a deleted function
	*/
	cout << b_a4.val_ << endl; // prints empty

	cout << "fn ends" << endl;
}
/*
	ctor called for rvalue argument string_value
	copy ctor
	dtor for value : string_value
	---------------
	ctor called
	assignment function
	string_value
	fn ends
	dtor for value : string_value
	dtor for value : string_value
*/


//int main()
//{
//	run_move_ctorr();
//	return 0;
//}

