#include <iostream>
#include<set>
#include <unordered_set>
using namespace std;



void set_impl()
{
	//unordered_multiset <int> setm;
	unordered_multiset<int> set_unorder;
	multiset <int> setm;
	set_unorder.insert(1);
	set_unorder.insert(4);
	set_unorder.insert(5);
	set_unorder.insert(5);
	set_unorder.insert(3);
	set_unorder.insert(3);
	set_unorder.insert(2);
	auto it = set_unorder.find(5);
	cout << *it << endl;
	cout << "size" << set_unorder.size() << endl;

	// remove all occurrences of item 5
	for (auto it = set_unorder.begin(); it != set_unorder.end(); ) {
		it = set_unorder.find(5);

		if (it != set_unorder.end())
		{
			//cout << "found:" << it - seti.begin() << endl;
			it = set_unorder.erase(it);
		}
	}

	//seti.erase(5);
	for (auto n : set_unorder)
	{
		cout << n << endl;
	}

}