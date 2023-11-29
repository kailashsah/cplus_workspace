#include <iostream>
using namespace std;

// 1.
/*
	struct my_struct
	{
	}
	sizeof(obj) - 1 byte
*/

// 2.
struct my_struct
{
	//int a;
	//char b;
};

void run_struct()
{
	my_struct obj;
	my_struct* pObj = &obj;
	
	//1.
	int sz = sizeof(*pObj);
	cout << "sizeof(*pObj)" << sz << endl; // size of struct, char padded becomes 4, so 4 + 4 = 8 
	
	//2.
	int sz1 = sizeof(pObj);
	cout << "sizeof(pObj)" << sz1 << endl; // it prints the pointer size, always 4 
	/*
		sizeof(*pObj)8
		sizeof(pObj)4
		Given-
			sizeof(int) - 4
	*/
}

//int main()
//{
//	run_struct();
//	return 0;
//}
