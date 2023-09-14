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


void list_impl()
{
	list<int> li;
	li.push_back(5);
	li.push_back(2);
	for (auto n : li)
		cout << n << endl;

	auto it = find(li.begin(), li.end(), 5);
	li.erase(it);

	for (auto n : li)
		cout << n << endl;
}