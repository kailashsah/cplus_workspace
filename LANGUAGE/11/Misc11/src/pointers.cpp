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

	cout << OurObject.p[0];
	cout << OurObject.p[0];

	//1. illegal indirection
	//*(OurObject.p[0]) = 1;
	//*(OurObject.p[1]) = 2;

	//2. illegal indirection
	//cout << *(OurObject.p[0]); 
	//cout << *(OurObject.p[0]);
	//_getch();
}


//int main()
//{
//	run_uniqueptr();
//	return 0;	
//}
