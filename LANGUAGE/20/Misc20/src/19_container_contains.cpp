#include <iostream>
using namespace std;

/*
	1. container.contains()
	2. 
*/
#include <map>
#include <array>
void run_map()
{
	//1.
	/*
		list<int> ll = {2,5,6};
		if(ll.contains(2))			// list don't has contains, it has elements not key
			cout << " list contains " << endl;
	*/

	//2.
	map<int, char> map = { {1,'a'}, {1, 'b'} };
	if (map.contains(1))
		cout << " found " << map.at(1) << endl; // found a

	//3.
	multimap<int, char> mmap = { {1,'a'}, {1, 'b'} };
	//(*(mmap.find(1)))->second; // type 'std::pair<const int,char>' does not have an overloaded member 'operator ->'
	if (mmap.contains(1))
		cout << " multimap found " << (*(mmap.find(1))).second << endl;  // multimap found a

	//4.
	//array arr{ 1,2,3 };
	//arr.contains(1); // error - 'contains': is not a member of 'std::array<_First,3>'


}

