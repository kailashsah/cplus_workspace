#include <iostream>
#include <vector>
using namespace std;
/*
	1. variant<> - template class
	2. The class template std::variant represents a type-safe union. An instance of std::variant at any given time either holds a value of one of its alternative types, or in the case of error - no value
		https://iq.opengenus.org/std-variant-in-cpp/
	3. holds_alternative() - Check if the given type of data is stored inside the variant at the given moment in time.
	4. emplace() constructs the value in-place using the provided arguments.
*/


#include <variant>

void run_variant_one() {

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

void run_variant_two() {
	variant<int, double, string> myVariant; // <-- here used string also

	myVariant = 42; // Assign an int 
	// Access the int 
	if (holds_alternative<int>(myVariant)) {
		cout << get<int>(myVariant) << endl;
	}

	myVariant = 3.14; // Assign a double 
	// Access the double 
	if (holds_alternative<double>(myVariant)) {
		cout << get<double>(myVariant) << endl;
	}

	myVariant = "Hello, Variant!"; // Assign a string 
	// Access the string 
	if (holds_alternative<string>(myVariant)) {
		cout << get<string>(myVariant) << endl;
	}

	//2. emplace()

	std::variant<int, std::string> myVar;
	myVar.emplace<std::string>("Hello");
}

#include <algorithm>
void run_variant_three()
{
	std::vector<std::variant<int, double, std::string>> data;
	// Can use standard algorithms with std::variant
	std::for_each(data.begin(), data.end(), [](auto& item) {
		std::visit([](auto&& arg) { std::cout << arg << std::endl; }, item);
		});

}
//int main()
//{
//	run_variant();
//	return 0;
//}
