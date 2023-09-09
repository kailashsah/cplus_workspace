#include <iostream>
#include<map>
#include<unordered_map>
using namespace std;

void map_impl()
{
	unordered_map <int, string> mapi;

	mapi.insert(pair<int, string>(5, "five"));
	mapi.insert(make_pair(5, "five"));
	mapi.insert(pair<int, string>(1, "one"));

	//std::qsort(mapi.begin(), mapi.end());
	//sort(mapi.begin(), mapi.end(), mapi.size(), greater<int> () );
	//sort(mapi.begin(), mapi.end());
	for (auto n : mapi)
	{
		cout << n.first << ":" << n.second << endl;
	}

	for (auto it = mapi.begin(); it != mapi.end();)
	{
		it = mapi.find(5);
		if (it != mapi.end())
			it = mapi.erase(it);

	}

	for (auto n : mapi)
	{
		cout << n.first << ":" << n.second << endl;
	}


}

void map_impl_sqbracket()
{
	unordered_map <int, int> mapi;

	mapi.insert(pair<int, int>(5, 5));
	mapi.insert(pair<int, int>(6, 6));
	mapi.insert(pair<int, int>(6, 6));
	if (mapi[5] == 5)
		cout << mapi[5]; // 5
}