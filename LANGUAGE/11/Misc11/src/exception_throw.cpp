#include <iostream>
using namespace std;

/*
	1. You can specify the type being thrown so that if it throws anything but that type (e.g. int), then the function calls std::unexpected instead of looking for a handler or calling std::terminate.

	2. If this throw specifier is left empty with no type, this means that std::unexpected is called for any exception. Functions with no throw specifier (regular functions) never call std::unexpected, but follow the normal path of looking for their exception handler.
*/

void handler() {
	printf_s("in handler\n");
}

//1.
void f1(void) throw(int) {
	printf_s("About to throw 1\n");
	if (1)
		throw 1;
}

//2. throw() -> means no exception thrown
void f5(void) throw() {
	try {
		f1();
	}
	catch (...) {
		handler();

	}
}
void run_throw()
{


}

//int main()
//{
//	run_throw();
//	return 0;
//}
