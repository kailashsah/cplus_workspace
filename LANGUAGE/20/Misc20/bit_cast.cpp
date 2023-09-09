#include <iostream>

using namespace std;

void run_int_float_ptr()
{
	// int ptr & float ptr
	int* pint = new int{ 5 };
	float* pFloat = new float{ 6 };
	cout << *pint << endl;
	//pint = (int*)pFloat; // garbage value
	//pint = static_cast<int*>(pFloat); // compile err // strong type checking

	pint = reinterpret_cast<int*>(pFloat); cout << *pint << endl; // garbage value
	int newint = static_cast<int>(*pFloat); cout << "newint " << newint << endl; // 6
	int& int_ref = reinterpret_cast<int&>(*pFloat); cout << "int_ref " << int_ref << endl; //  garbage value 
	cout << pFloat;// print address 00DCE570
	int int_bit = std::bit_cast<int>(pFloat); cout << "int_bit " << int_bit << endl; // bit_cast c++20

	// static cast
	int i = 8;
	float f = 5.5;
	int ii = static_cast<int>(f);
	float ff = static_cast<float>(i);
	//cout << ii; // 5
	cout << ff;

}

