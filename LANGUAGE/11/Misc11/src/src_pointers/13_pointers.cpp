#include <iostream>

using namespace std;

class abc
{
public:
	int* p;
	abc()
	{
		p = new int[2]; // Assume that memory allocation succeeds here.

	}
	~abc()
	{
		delete[]p;
	}
};
void run_pointers() {
	abc OurObject;
	OurObject.p[0] = 1;
	OurObject.p[1] = 2;

	cout << OurObject.p[0]; // 1
	cout << OurObject.p[1]; // 2

	//1. illegal indirection
	//*(OurObject.p[0]) = 1;
	//*(OurObject.p[1]) = 2;

	//2. illegal indirection
	//cout << *(OurObject.p[0]); 
	//cout << *(OurObject.p[0]);

	//3. 
	cout << *OurObject.p; // valid // 1
	*OurObject.p = 20;
	*(OurObject.p + 1) = 10;
	cout << *(OurObject.p); // ok // 20
	cout << *(OurObject.p + 1); // ok // 10


	//_getch();
}

//int main()
//{
//	run_pointers();
//	return 0;
//}
