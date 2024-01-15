#include <iostream>
using namespace std;
/*
	1. Put simply, an lvalue is an object reference and an rvalue is a value.
	
	2. an rvalue is an unnamed object or a member of such an object which is not a reference.
	
	3. rvalue is an expression that could not be the left hand side of an assignment, but that could only be the right hand side.

	4. move() - 
		1. The std::move function converts the lvalue object to an rvalue.
		
		2. static_cast< remove_reference_t<_Ty> &&> (_Arg);

	5.
*/
