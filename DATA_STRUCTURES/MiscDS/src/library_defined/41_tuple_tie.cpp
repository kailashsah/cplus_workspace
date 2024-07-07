#include <iostream>
#include <set>
#include <tuple>
using namespace std;
/*
	1. tuple<int, string, double>
	2. make_tuple();
	3. tie

*/

void print_tuple(set<tuple<int, int, int> >& setOfTuples)
{
	for (auto x : setOfTuples)
	{
		//1.
		cout << get<0>(x);

		//2. alternative of above, but both are same
		tuple<int, int, int> tp = x;
		cout << get<0>(tp) <<
			' ' << get<1>(tp) <<
			' ' << get<2>(tp) << '\n';
	}
}
void run_print_tuple_caller()
{
	cout << endl << "run_print_tuple_caller() : " << endl;
	set<tuple<int, int, int>> setoftup;
	tuple<int, int, int> tuple1 = make_tuple(1, 2, 3);
	setoftup.insert(tuple1);
	print_tuple(setoftup);
}

void run_tie()
{
	cout << endl << "run_tie() : " << endl;
	//useful for unpacking std::pair and std::tuple objects
	
	//........................................... 1. With tuples...
	std::string playerName;
	std::tie(std::ignore, playerName, std::ignore) = std::make_tuple(91, "John Tavares", "NYI");

	//........................................... 2. With pairs...
	std::string yes, no;
	std::tie(yes, no) = std::make_pair("yes", "no");
}

void run_tuple()
{
	cout << endl << "run_tuple() : " << endl;
	auto playerProfile = std::make_tuple(51, "Frans Nielsen", "NYI");
	
	//1.
	cout << tuple_size<decltype(playerProfile)>::value << endl; //3
	
	//2.
	cout << std::get<0>(playerProfile) << " "; // 51
	cout << std::get<1>(playerProfile) << " "; // "Frans Nielsen"
	cout<< std::get<2>(playerProfile); // "NYI"

	//3.
	//cout << get<const char*>(playerProfile); // error C2338: duplicate type T in get<T>(tuple)
	cout << get<int>(playerProfile); // ok
	/*
		auto t = std::make_tuple(1, 's', 2);
		std::get<int>(t);
		here, we have a t of a type std::tuple<int, char, int>. std::get can also work with types (alongside indexes, like get<int>), unless you have a duplicate type. 
		std::get<char> will work since there is only one char in the t, but std::get<int> will not work, since it does not know which int to fetch - the 1 or the 2?
	*/
	
	cout << endl;
}


//int main()
//{
//	run_print_tuple_caller();
//	run_tie();
//	run_tuple();
//	return 0;
//}
