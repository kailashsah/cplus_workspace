
#include <iostream>
using namespace std;
/*
	1. const_cast<> 
	2. 

*/

int fun_const_change(int* ptr)
{
	*ptr = *ptr + 10;
	return (*ptr);
}

/*
int fun(int* ptr)
{
	return (*ptr + 10);
}
*/


//1.
int const_modify(void)
{
	/*
		-- const_cast can be used to pass const data to a function that doesn’t receive const. For example, in the following program fun() receives a normal pointer, but a pointer to a const can be passed with the help of const_cast.
	*/
	const int val = 10;
	const int* ptr = &val;
	int* ptr1 = const_cast <int*>(ptr);
	cout << "fun(ptr1) : " << fun_const_change(ptr1) << endl; // 20
	//1.1
	cout << "* ptr1 :" << *ptr1 << endl; // 20

	//1.2
	cout << val; // undefined behavior, it is const int at declaration .. if it would be "int val =10", then it is fine, gives value 20.
	
	
	cout << endl;
	return 0;

	/*
		output -
		20
	*/
}

//2.................................................
int volatile_func(void)
{
	int a1 = 40;
	const volatile int* b1 = &a1;
	cout << "typeid of b1 (const volatile int* b1 = &a1;) :  " << typeid(b1).name() << '\n' << endl;

	// 1.
	int* c1 = const_cast <int*> (b1); // const_cast  also removes the volatile from variable
	cout << "typeid of c1 (int* c1 = const_cast <int*> (b1)) :  " << typeid(c1).name() << '\n';
	
	// 2. 
	//int* c1 = static_cast <int*> (b1);
	/*
		Error	C2440	'static_cast': cannot convert from 'volatile const int *' to 'int *'
	*/	
	return 0;

	/*
		output -
		typeid of b1 (const volatile int* b1 = &a1;) :  int const volatile *

		typeid of c1 (int* c1 = const_cast <int*> (b1)) :  int *
	*/
}

//3.
int strong_typecasting(void)
{
	/*
		-- const_cast is considered safer than simple type casting.It’safer in the sense that the casting won’t happen if the type of cast is not same as original object.For example, the following program fails in compilation because ‘int* ’ is being typecasted to ‘char* ’
	*/
	int a1 = 40;
	const int* b1 = &a1;
	//char* c1 = const_cast <char*> (b1); // compiler error 
	//*c1 = 'A';
	return 0;
}

void run_const_cast() {
	volatile_func();  
	const_modify(); 
	strong_typecasting();
}

//int main()
//{
//	run_const_cast();
//	return 0;
//}