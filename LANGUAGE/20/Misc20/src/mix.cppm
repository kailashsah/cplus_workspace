#include <iostream>
using namespace std;

#include <map>
#include <list>
#include <array>
///////////////////////////////////// // output stream ensuring synchronization
#include <syncstream>
void run_sys_ostream()
{
	osyncstream(cout) << " I am osyncstream " << endl;
}

///////////////////////////////////// // mid point
import <numeric>; 
void run_midpoint()
{
	//1.
	cout << std::midpoint(1, 4); // 5/2 -> 2
	
	//2.
	//cout << std::midpoint(1, 6.5); // 7/2 -> 3 //error C2784: '_Ty *std::midpoint(_Ty *const ,_Ty *const ) noexcept': could not deduce template argument for '_Ty *const ' from 'int'
}

void run_mix_main()
{
	// run_midpoint();

	//run_sys_ostream();
	//
}

//int main()
//{
//	run_mix_main();
//	return 1;
//}

