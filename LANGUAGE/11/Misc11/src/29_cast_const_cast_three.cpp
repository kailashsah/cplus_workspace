#include <iostream>
using namespace std;
void run_const_4();
void run_const_3();
void run_const_2();
void run_const();
//
int fun(int* ptr)
{
	return (*ptr + 10);
}

void run_const() {
	const int val = 10;
	const int* ptr = &val;
	int* ptr1 = const_cast <int*>(ptr);		//local copy inside fn scope.
	cout << fun(ptr1) << endl;				//20
	cout << "org value: " << val << endl;	//10
}
void run_const_2() {

	const int src = 1;
	int* p = const_cast<int*>(&src);	// p becomes the local copy inside fn scope.
	cout << "src before=" << *p << endl;//1
	//1.
	*p = 10;
	cout << "src after=" << src << endl;//1
	cout << "*p after=" << *p << endl;	//10

	//2.
	*const_cast<int*>(&src) = 12;
	cout << "src after=" << src << endl; //1
	cout << "*p after=" << *p << endl;	//12 
}

//const int* ip = new int(123); //(1)	//ok
void run_const_3() {
	const int* ip = new int(123);
	const int* ptr = ip;
	//1.
	//*ptr = 321;
	//2.
	//*const_cast<int*>(ip) = 321;
	//3.
	//*const_cast<int*>(ptr) = 321; //ok
	cout << "*ip: " << *ip << endl; // 321
	/*
		for (1), it remains 123 becoz in global scope
	*/
}

void run_const_4() {
	int a1 = 40;
	const int* b1 = &a1;
	//1.
	//char* c1 = const_cast <char*> (b1); // compiler error 'const_cast': cannot convert from 'const int *' to 'char *'	

	//2.
	//*b1 = 5; //'b1': you cannot assign to a variable that is const
	return;
}

//int main()
//{
//	//run_const_4();
//	//run_const_3();
//	//run_const_2();
//	//run_const();
//	return 0;
//}
