#include <iostream>
using namespace std;
/*
	1. trailing-type	-	-> ret, where ret specifies the return type

	2.
		If trailing-type is not provided, the return type of operator() is determinted as follows:

		If body only consists of a return statement that returns an expression, the return type is the type of that expression after lvalue-to-rvalue conversion, array-to-pointer conversion and function-to-pointer conversion.
		Otherwise, the return type is void.
		(until c++14)

	3. If trailing-type is not provided, or provided as -> auto, the return type of operator() is automatically deduced.  (since c++14)

	4. not userful for  single return statement which always returns an integer value.

		But for multiple return statements of different types, we have to explicitly define the type. For example,  see code below

	5. https://www.programiz.com/cpp-programming/lambda-expression
*/

void run_fn_trailing_type()
{

	auto operation = [](int a, int b, string op) -> double {
		if (op == "sum") {
			// returns integer value
			return a + b;
		}
		else {
			// returns double value
			return (a + b) / 2.0;
		}
	};

	/*
		here are multiple statements which return different types based on the value of op.

		So no matter what type of value is returned by the various return statements, they are all explicitly converted to double type.
	*/

}

//int main()
//{
//	return 0;
//}
