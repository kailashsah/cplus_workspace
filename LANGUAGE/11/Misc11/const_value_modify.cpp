
#include <iostream>

using namespace std;

int fun(int* ptr)
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
	cout << fun(ptr1);
	cout << endl;
	return 0;
}
//.................................................
int volatile_func(void)
{
	int a1 = 40;
	const volatile int* b1 = &a1;
	cout << "typeid of b1 " << typeid(b1).name() << '\n';
	int* c1 = const_cast <int*> (b1); // const_cast  also removes the volatile from variable
	cout << "typeid of c1 " << typeid(c1).name() << '\n';
	return 0;
}

void run_const_cast() {
	volatile_func();
	const_modify();
}