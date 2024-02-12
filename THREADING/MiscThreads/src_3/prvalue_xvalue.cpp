#include <iostream>
using namespace std;

/*
	1. xvalue - An xvalue (an “eXpiring” value) also refers to an object, usually near the end of its lifetime (so that its resources may be moved, for example). An xvalue is the result of certain kinds of expressions involving rvalue references. 
		[Example: The result of calling a function whose return type is an rvalue reference is an xvalue.]

	2. prvalue (literal values) - A prvalue (“pure” rvalue) is an rvalue that is not an xvalue. 
		[Example: The result of calling a function whose return type is not a reference is a prvalue].

		 2.1 Example: The result of calling a function whose return type is not a reference is a prvalue. The value of a literal such as 12, 7.3e5, or true is also a prvalue

	3. prvalues are the implicit moves, and xvalues are the explicit moves (std::move returns an xvalue).

	https://stackoverflow.com/questions/3601602/what-are-rvalues-lvalues-xvalues-glvalues-and-prvalues
*/