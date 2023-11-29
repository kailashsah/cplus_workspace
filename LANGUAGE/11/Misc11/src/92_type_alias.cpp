#include <iostream>
#include <vector>
using namespace std;

//1.
template<typename T>
using Vec = vector<T>;

//2.
using ss = string;

void run_type_alias()
{
	Vec<int> v{ 2,1,4,5 };
	ss s = "hi";
	cout << s;

}

//int main()
//{
//	run_type_alias();
//	return 0;	
//}
