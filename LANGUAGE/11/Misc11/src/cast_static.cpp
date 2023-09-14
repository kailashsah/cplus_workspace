#include <iostream>
#include <string>
using namespace std;



void run_static_cast()
{
	int a = 7;
	const int b = static_cast <int> (a);
}

//int main()
//{
//	run_static_cast();
//	return 0;	
//}
