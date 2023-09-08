#include <iostream>
#include <numeric> // iota
#include <vector>

#include <thread>
#include <string> // to_string
#include <map>
#include <set>
using namespace std;
void printt(string str);

//.....................................................
/*
void run_print_tuple(set<tuple<int, int, int> >& setOfTuples);
void run_tie();
void run_tuple();
void run_range_based_loop();
run_chrono();
void run_member_init();
run_ref();
run_reference_vector();
run_begin_end();
*/
//------------------------------------------------------

void run_print_tuple(set<tuple<int, int, int> >& setOfTuples)
{
	for (auto x : setOfTuples)
	{
		tuple<int, int, int> tp = x;
		cout << get<0>(x); // alternative of above

		cout << get<0>(tp) <<
			' ' << get<1>(tp) <<
			' ' << get<2>(tp) << '\n';
	}
}
void run_print_tuple_caller()
{
	set<tuple<int, int, int>> stup;
	tuple<int, int, int> tuple1 = make_tuple(1, 2, 3);
	stup.insert(tuple1);
	run_print_tuple(stup);
}

void run_tie()
{
	//useful for unpacking std::pair and std::tuple objects
	// With tuples...
	std::string playerName;
	std::tie(std::ignore,	 playerName, std::ignore) = std::make_tuple(91, "John Tavares", "NYI");

	// With pairs...
	std::string yes, no;
	std::tie(yes, no) = std::make_pair("yes", "no");
}
void run_tuple()
{
	// cout << tuple_size<decltype(geek)>::value << endl;
	auto playerProfile = std::make_tuple(51, "Frans Nielsen", "NYI");
	std::get<0>(playerProfile); // 51
	std::get<1>(playerProfile); // "Frans Nielsen"
	std::get<2>(playerProfile); // "NYI"
}

//-------------------------------------------------------

void run_range_based_loop()
{
	// Printing keys and values of a map
	std::map <int, int> MAP{ {1, 1}, {2, 2}, {3, 3} };
	for (auto i : MAP)
		std::cout << '{' << i.first << ", "
		<< i.second << "}\n";
}

//-------------------------------------------------------

void run_member_init()
{
	class AA{ 
		int a{0};
		string str{};

	public:
		AA() : a{0}{}
	};
}

//-------------------------------------------------------

void run_chrono()
{
	auto start = chrono::high_resolution_clock::now();
	
	this_thread::sleep_for(chrono::milliseconds(2500));
	auto end = chrono::high_resolution_clock::now();
	auto aa = chrono::duration_cast<chrono::milliseconds> (end - start);
	printt(to_string(aa.count()));
}

//.................................................
void update(int& data)  //expects a reference to int
{
	data = 15;
}
int run_ref()
{
	int data = 10;

	// This doesn't compile as the data value is copied when its reference is expected.
	//std::thread t2(update, data);   
	//std::thread t1(update, move(data));

	std::thread t1(update, std::ref(data));  // works, if reference provided in this way

	t1.join();
	printt(to_string(data)); //  15
	return 0;
}

//.................................................

class B { public: int i; };
void run_vector()
{
	vector <B*> vec;
	B* c = nullptr;
	vec.push_back(c);
	
	auto a = vec[0];	
	if (vec[0])
		cout << vec[0]->i; // crash if no if validation, use reference_wrapper instead
	else
		printt("null ptr");
}

void run_reference_vector()
{
	vector <reference_wrapper<B>> vec;
	
	B b;
	b.i = 20;	
	
	vec.push_back(b);
	
	b.i = 40;
	auto a = vec[0];
	printt( to_string( a.get().i));
}
//-------------------------------------------------------

void printt(string str)
{
	cout << str << endl;
}

//-------------------------------------------------------

void run_begin_end()
{
	//int arr[100];
	// iota(begin(arr), end(arr), 0);
	//
	//int arr[100] = {}; // initialize all to zero
	//
	int arr[100] ;
	fill(begin(arr), end(arr), 3);
	//
	copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
	cout << endl;
}
//-------------------------------------------------------
void run_tute()
{
	//run_print_tuple_caller();
	//run_range_based_loop();
	//run_chrono();
	//run_ref();
	//run_reference_vector();
	//run_begin_end();
	cout << "main ends here" << endl;
}

//int main()
//{
//	run_tute();
//	return 0;
//}

