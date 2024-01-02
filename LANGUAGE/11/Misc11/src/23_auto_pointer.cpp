#include <iostream>
using namespace std;
/*
	1. auto*
	2. auto - The auto keyword in C++ automatically detects and assigns a data type to the variable with which it is used. The compiler analyses the variable's data type by looking at its initialization.

	3. https://www.scaler.com/topics/cpp/auto-in-cpp/

*/
void run_auto_ptr_v1();
void run_auto_references_v2();
//
void run_auto_ptr_v1() {
	// Declare variables.
	int num1 = 10, num2 = 9;

	// Declare pointer using auto.
	auto p1 = &num1;

	// We can also use * for readability.
	auto* p2 = &num2;

	cout << "The values are " << *p1 << " and " << *p2 << endl;

}

void run_auto_references_v2() {

	// Declare a variable.
	int num1 = 10;

	// Declare reference using auto.
	auto& x = num1;

	// Change the value of num1 to see if the reference works.
	num1 = 19;

	cout << "The value is " << x << endl;
}
void run_auto_ptr_usage() {
	/*
		1.
			int i;
			const auto* p = &i;
			is equivalent to

			int i;
			const int* p = &i;  // read as 'pointer to const int'

		2.
			int i;
			const auto p = &i;
			is equivalent to

			int i;
			int* const p = &i; // read as "constant pointer to int"
		
		3. const int* const // constant pointer to const int 

	*/
	int a;
	//1
	const auto* p1 = &a;
	//*p1 = 7;               // Error //'p1': you cannot assign to a variable that is const.
	p1 = nullptr;          // OK

	//2.
	const auto p2 = &a;
	*p2 = 7;               // OK
	//p2 = nullptr;          // Error
}
//int main()
//{
//	run_auto_ptr_v1();
//	run_auto_references_v2();
//	return 0;
//}

