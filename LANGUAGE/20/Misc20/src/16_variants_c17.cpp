#include <iostream>
#include <vector>
using namespace std;
/*
	1. variant<> - template class
*/

// 
#include <variant>
/*
 The class template std::variant represents a type-safe union. An instance of std::variant at any given time either holds a value of one of its alternative types, or in the case of error - no value
 https://iq.opengenus.org/std-variant-in-cpp/
*/
void run_variant() {
	//1.
	std::variant<int, double> var{ 11 };
	cout << get<int>(var) << endl;
	cout << get<0>(var) << endl;

	//2.
	var = 12.0;
	cout << get<double>(var) << endl;
	cout << get<1>(var) << endl;

	//3.
	//cout << get<0>(var) << endl; // exception: std::bad_variant_access at memory location 0x00B3F8D0
	//cout << get<int>(var) << endl; // std::bar_variant_access exception
}

//int main()
//{
//	run_variant();
//	return 0;
//}
