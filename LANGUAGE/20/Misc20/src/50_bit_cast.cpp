#include <iostream>
using namespace std;

/*
	1. reinterpret_cast<> https://www.geeksforgeeks.org/reinterpret_cast-in-c-type-casting-operators/ 
	2. When it is needed to interpret the bytes of an object as a value of a different type, std::memcpy or std::bit_cast (since C++20) can be used
	3. It is generating a new object as if by copying its value representation from an existing one. It's a low-level tool, but it's not a tool that messes with the type system. So it would be strange to spell a "safe" operation the same way you spell a "dangerous" one.

	4. 
		bit_cast(const From& src) noexcept
		{
			static_assert(std::is_trivially_constructible_v<To>,
				"This implementation additionally requires "
				"destination type to be trivially constructible");
 
			To dst;
			std::memcpy(&dst, &src, sizeof(To)); // <--
			return dst;
		}
*/
#include <bit> // std::bit_cast
void run_bit_cast()
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
	int ii = static_cast<int>(f);	// 5
	float ff = static_cast<float>(i);
	//cout << ii; // 5
	cout << ff;

}

