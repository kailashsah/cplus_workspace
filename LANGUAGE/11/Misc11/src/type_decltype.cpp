#include <iostream>
using namespace std;

//auto test(const auto & v) // parameter cannot have a type that contains 'auto'
auto test(const int& v)
{
	auto a1 = decltype(v){2}; // what is a1's qualified TYPE?
	string ss(typeid(a1).name());
	cout << ss << endl;
	//cout<< type_name<decltype(a1)>();
	decltype(v) a2{ 2 }; // what is a2's qualified TYPE?
	cout << typeid(a2).raw_name() << endl;
	a1++; // is this legal? Why
	//a2++; // is this legal? Why
	return a1 + a2;
}

void run_decltype()
{
	int x = 6;
	auto c = test(x);
	return ;
}

//int main()
//{
//	run_virtual_static();
//	return 0;	
//}
