#include <iostream>
using namespace std;

/*
	1. format string 
*/

#include <format>
void run_format()
{
	int a = 10;
	auto str = std::format(" hello {}  world!", a);
	cout << str << endl;
}

