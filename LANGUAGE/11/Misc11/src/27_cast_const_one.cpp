
#include <iostream>

using namespace std;

int fun_const_change(int* ptr)
{
	*ptr = *ptr + 10;
	return (*ptr);
}
/*
int fun(int* ptr)
{
	return (*ptr + 10);
}*/



int const_modify(void)
{
	const int val = 10;
	const int* ptr = &val;
	int* ptr1 = const_cast <int*>(ptr);
	cout << "fun(ptr1) : " << fun_const_change(ptr1) << endl; // 20
	cout << "* ptr1 :" << *ptr1 << endl; // 20
	cout << endl;
	return 0;

	/*
		output -
		20
	*/
}
//.................................................
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

void run_const_cast() {
	volatile_func();
	const_modify();
}

//int main()
//{
//	run_const_cast();
//	return 0;
//}