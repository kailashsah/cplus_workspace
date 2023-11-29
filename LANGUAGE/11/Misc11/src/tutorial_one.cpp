#include <iostream>
#include <numeric> // iota
#include <vector>

#include <thread>
#include <string> // to_string
#include <map>
#include <set>
using namespace std;
void printt(string str);

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
	class AA {
		int a{ 0 };
		string str{};

	public:
		AA() : a{ 0 } {}
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


//-------------------------------------------------------

void printt(string str)
{
	cout << str << endl;
}

//-------------------------------------------------------

void run_initializer_list()
{
	int arr2[100] = {}; // initialize all to zero
	
}
//-------------------------------------------------------
void run_tute()
{
	//run_range_based_loop();
	//run_chrono();
	//run_ref();
	run_initializer_list();
	cout << "main ends here" << endl;
}

//int main()
//{
//	run_tute();
//	return 0;
//}

