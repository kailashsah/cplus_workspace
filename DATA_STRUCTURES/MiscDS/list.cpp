#include <iostream>
#include <list>

using namespace std;

void data_str_list_erase() {

	list <int> ls;
	ls.push_back(1);
	ls.push_back(3);
	ls.push_back(6);
	for (auto a : ls) {
		cout << a << " ";
	}
	cout << endl;
	auto it = find(ls.begin(), ls.end(), 3);

	ls.erase(it); // removes 3
	erase(ls, 6); // removes 6
	for (auto a : ls) {
		cout << a << " ";
	}

}