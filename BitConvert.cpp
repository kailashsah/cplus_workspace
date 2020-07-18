#include <iostream>
#include <algorithm>
#include <vector>
#include "conio.h"

void BitConvert(int num, std::vector<int> &array)
{
	while(num > 0) {
		array.push_back(num % 2);
		num = num / 2;
	}
}

void CheckEven(int num)
{
	std::vector<int> array;
	BitConvert(num, array);
	if(array[ 0 ] == 0)
		std::cout << "Number is even";
	else
		std::cout << "Number is odd";
}
//
//int main()
//{
//	int num;
//	std::cout << "Enter a number:";
//	std::cin >> num;
//
//	CheckEven(num);
//	std::cout << std::endl;
//
//	_getch();
//	return 0;
//}
