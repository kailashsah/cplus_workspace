#include <iostream>
using namespace std;
/*
	1. run_const_two() - you never able to change the value of the "static const int".
	2. if const int in local fn scope & we const_cast<int>, it creates the local copy of it. see 'run_const_two()'

*/
void run_const_one();
void run_const_two();
//
void run_const_one() {
	// 1. 
	static const  int a = 5;
	//1.1
	int& b = const_cast<int&>(a); // we can only do const_cast<> bcoz src is const.
	//1.2.
	//int& b = static_cast<int&>(a); // error - static_cast<> cannot cast away const & other type  qualifier (same for reinterpret_cast<int&>(a);)
	//1.3.
	//int& b = a;		// error - initializing': cannot convert from 'const int' to 'int &'

	cout << typeid(b).name(); // int
	//b = 10;			// Exception thrown : write access violation.

	// 2. 
	static int aa = 5;
	int& bb = const_cast<int&>(aa); // ok
	cout << typeid(bb).name();		//int
	bb = 10;

	// 3.
	static int aaa = 5;
	const int& bbb = aaa;	// you can create the const variable at run time from the static variable. IMP
	cout << typeid(bbb).name(); //int
	//bbb = 10;				//b': you cannot assign to a variable that is const
}

void run_const_two() {
	// 1.1
	static const  int a = 5; //like written in global scope.
	int* b = const_cast<int*>(&a);    // Exception thrown : write access violation. at line below
	cout << typeid(b).name() << endl; // int*
	//*b = 10;  //(1)
	cout << " changed value: " << *b << endl;
	cout << "org value: " << a << endl;


	// 1.1 solution...............
	cout << "solution " << endl;
	//1.
	//static const  int aa = 5; // this call makes const forever like it was written in global scope.
								//write access violation.
	//2.
	const  int aa = 5; // inside fn not outside fun(globally)

	//2.1.
	//int* ptr = &aa;		// cannot convert from 'const int *' to 'int *'
	//2.2
	const int* ptr = &aa;	//ok

	//3.
	//int* bb = const_cast<int*>(&aa); //OK
	//3.1
	int* bb = const_cast<int*>(ptr);//OK // it makes the local copy of int variable, check output 
	cout << typeid(b).name() << endl;// int*
	*bb = 10;
	cout << " changed value: " << *bb << endl;	//10
	cout << "org value: " << aa;				//5


}

//int main()
//{
//	run_const_one();
//	run_const_two();
//	return 0;
//}
