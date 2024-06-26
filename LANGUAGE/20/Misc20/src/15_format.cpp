#include <iostream>
using namespace std;

/*
	1. format string 
	
	2. The function returns a std::string that contains the formatted output.
	3. The std::format is a text formatting library since C++20, which offers a safe and extensible alternative to the printf family of functions.

*/

#include <format>
void run_format()
{
	//1.
	int a = 10;
	auto str = std::format(" hello {}  world!", a);
	cout << str << endl;

	//2.Positional arguments
	std::cout << std::format("I'd rather be {1} than {0}", "right", "happy");
}

