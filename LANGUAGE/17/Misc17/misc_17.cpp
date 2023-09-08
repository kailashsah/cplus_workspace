#include <iostream>
#include <vector>
using namespace std;


// variant
#include <variant>
void run_variant() {
	std::variant<int, double> var{12};
	cout << get<int>(var) << endl;
	cout << get<0>(var) << endl;
	var = 12.0;
	cout << get<double>(var) << endl;
	cout << get<1>(var) << endl;
	//cout << get<int>(var) << endl; // std::bar_variant_access exception
}

//int main()
//{
//	run_variant();
//	return 0;
//}
