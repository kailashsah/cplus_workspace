#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

/*
	1. list.sort() - O(nlogn)
	2. search/find - O(n), linear
*/
void data_str_list_erase() {

	list <int> ls;
	ls.push_back(1);
	ls.push_back(3);
	ls.push_back(6);
	//ls.push_front(); // also available
	for (auto a : ls) {
		cout << a << " ";
	}
	cout << endl;
	auto it = find(ls.begin(), ls.end(), 3);

	ls.erase(it); // removes 3
	//erase(ls, 6); // removes 6 // std::erase() available for string type 
	for (auto a : ls) {
		cout << a << " ";
	}

	//
	ls.pop_back();
	ls.pop_front();

}
