#include <iostream>
#include <vector>
using namespace std;
/*
	1. std::visit(), under utility library. It reduces the amount of boilerplate code
	2. constexpr R visit( Visitor&& vis, Variants&&... vars ); 
		Applies the visitor vis (a Callable that can be called with any combination of types from variants) to the variants vars
	3. std::visit can be useful in scenarios where we need to handle variant objects with multiple possible types, such as in parser, where we may need to handle different types of input data differently.

*/
void run_visit();
void run_without_visit();
//
#include <variant>
void func(int i) {
	std::cout << "Called func(int): " << i << std::endl;
}

void func(double d) {
	std::cout << "Called func(double): " << d << std::endl;
}

void func(const std::string& s) {
	std::cout << "Called func(string): " << s << std::endl;
}

void run_visit() {
	std::vector<std::variant<int, double, std::string>> myVector = { 1, 3.14, "Hello" };

	for (auto& element : myVector) {
		std::visit([](auto&& arg) {
			func(arg);
			}, element);
	}// for
	
	 /*
		Called func(int): 1
		Called func(double): 3.14
		Called func(string): Hello
	
	*/
}

void run_without_visit() {
	std::vector<std::variant<int, double, std::string>> vec = { 1, 3.14, "hello" };

	for (const auto& variant : vec) {
		if (std::holds_alternative<int>(variant)) {
			int value = std::get<int>(variant);
			func(value);
		}
		else if (std::holds_alternative<double>(variant)) {
			double value = std::get<double>(variant);
			func(value);
		}
		else if (std::holds_alternative<std::string>(variant)) {
			std::string value = std::get<std::string>(variant);
			func(value);
		}
	}
}

//int main()
//{
//	run_visit();
//	return 0;
//}
