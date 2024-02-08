#include <iostream>
using namespace std;

/*
	1. 'auto' lets you declare a variable with a particular type 
	2. whereas decltype lets you extract the type from the variable so decltype is sort of an operator that evaluates the type of passed expression.
*/

//1.
//auto test(const auto & v) // parameter cannot have a type that contains 'auto'
auto test(const int& v)
{
	//1.
	auto a1 = decltype(v){2}; // what is a1's qualified TYPE?
	/*
		Note: const is ignored in auto keyword, but const is not ignored in decltype.
	*/
	string ss(typeid(a1).name());
	cout << ss << endl; //int
	a1++; // is this legal? Why -> becoz const is ignored in "auto"

	//2.
	decltype(v) a2{ 2 }; // what is a2's qualified TYPE?
	cout << typeid(a2).raw_name() << endl; //.h //typeid(a2).name() retuns i
	/*
	 a2++; // is this legal? Why  -> no its not legal
	'a2': you cannot assign to a variable that is const	Misc11

	*/

	return a1 + a2;


	//
	//Note: 
	// auto - reference(&) is ignored in auto keyword, but reference(&) is not ignored in decltype.
	// auto - const, 'reference &' is ignored  (Remember)
}

void run_decltype()
{
	int x = 6;
	auto c = test(x);
	cout << "auto c = test(x); : " << c << endl; // 5 .. expected is 5.
	return;
}



//int main()
//{
//	run_decltype();
//	return 0;
//}
