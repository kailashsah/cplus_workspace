#include <iostream>
using namespace std;

/*
	'auto' lets you declare a variable with a particular type whereas decltype lets you extract the type from the variable so decltype is sort of an operator that evaluates the type of passed expression
*/
//auto test(const auto & v) // parameter cannot have a type that contains 'auto'
auto test(const int& v)
{
	auto a1 = decltype(v){2}; // what is a1's qualified TYPE?
	/*
		Note: const is ignored in auto keyword, but const is not ignored in decltype.
	*/
	string ss(typeid(a1).name());
	cout << ss << endl; //int
	a1++; // is this legal? Why -> becoz const is ignored in "auto"


	decltype(v) a2{ 2 }; // what is a2's qualified TYPE?
	cout << typeid(a2).raw_name() << endl; //.h //typeid(a2).name() retuns i
	/*
	 a2++; // is this legal? Why
	'a2': you cannot assign to a variable that is const	Misc11

	*/

	return a1 + a2;


	//
	//Note: reference(&) is ignored in auto keyword, but reference(&) is not ignored in decltype.
	//auto - const, reference & is ignored
}

void run_decltype()
{
	int x = 6;
	auto c = test(x);
	cout << "auto c = test(x); : " << c << endl; // 5
	return;
}



//int main()
//{
//	run_decltype();
//	return 0;
//}
