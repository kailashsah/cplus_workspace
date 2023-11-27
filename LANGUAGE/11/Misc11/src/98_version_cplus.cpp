#include <iostream>
using namespace std;


void run_version()
{
	if (__cplusplus == 201703L) std::cout << "C++17\n";
	else if (__cplusplus == 201402L) std::cout << "C++14\n";
	else if (__cplusplus == 201103L) std::cout << "C++11\n";
	else if (__cplusplus == 199711L) std::cout << "C++98\n";
	else std::cout << "pre-standard C++\n";

}

//int main()
//{
//	run_version(); // c++98, always prints c++98 when changes to c++14 or c++17 
//	return 0;	
//}
