#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void fill_array() {
	vector<int> vec(100, 0);
	//for_each(vec.begin(), vec.end(), [](auto a) { cout << a << " "; });
	//for_each(vec.begin(), vec.end(), [i = 0](auto& a) mutable { i++; a = i; return a; });
	//for_each(vec.begin(), vec.end(), [](auto a) { cout << a << " "; });

	// random numbers
	vec.resize(300);
	//fill 1 to 100;
	srand(time(nullptr));
	for_each(vec.begin(), vec.end(), [](auto& a) {a = 1 + rand() % 99; ; return a; });
	sort(vec.begin(), vec.end());
	/*auto last = unique(vec.begin(), vec.end(), [](auto l, auto r) {
		if (l == r)
			return true;
		else false;
		});
	*/
	auto last = unique(vec.begin(), vec.end());
	vec.erase(last, vec.end());
	auto l = [](auto a) mutable {return rand() % a; };;
	_Random_shuffle1(vec.begin(), vec.end(), l);
	for_each(vec.begin(), vec.end(), [](auto a) { cout << a << " "; });
	cout << "count is " << vec.size();
	//iota();
}
//.................................................

void vector_2D_array() {
	vector<vector<int>> vec(2);
	vec[0].push_back(1);
	vec[0].push_back(2);
	vec[1].push_back(3);
	vec[1].push_back(4);
	cout << "row" << vec.size();
	cout << " col" << vec[0].size();
	cout << endl;
	for (auto row : vec)
	{
		cout << row[0] << " " << row[1];
		cout << endl;
	}



}