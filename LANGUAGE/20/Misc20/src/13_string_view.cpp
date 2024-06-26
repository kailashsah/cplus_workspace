#include <iostream>
using namespace std;

/*
	1. use string_view when it is required to pass "const string&" in an argument.
	2. std::string_view provides read-only access to an existing string (a C-style string, a std::string, or another std::string_view) without making a copy. 
	
		Read-only means that we can access and use the value being viewed, but we can not modify it.
*/

void func_sv(std::string_view sv)
{
	cout << sv << endl;
}

void func_str(std::string str)
{
	cout << str << endl;
}
void run_stringview()  // string view
{
	string_view sv = "str literal";
	
	//1. string_view - to - string object
	string str_reg{ sv };
	cout << str_reg << endl; // str literal
	
	//2. passing string_view to string
	//func_str(sv);			//No user-defined-conversion operator available that can perform this conversion, or the operator cannot be called, fix below
	func_str(static_cast<string>(sv)); // str literal -> fun with regular string

	//3. passing string to string_view
	std::string s = "abc";
	func_sv(s);				// abc


}

void run_starts_with() {
	string str = "foobar";
	cout << str.starts_with("foo");

}

