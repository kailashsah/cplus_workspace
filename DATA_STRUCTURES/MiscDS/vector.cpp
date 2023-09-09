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
//.................................................

void vec_impl()
{

	std::string cs = "hello";
	vector<int> veci = { 1,2,5,2,4,5 };
	//veci.push_back(5);
	//veci.pop_back();
	veci.insert(veci.begin(), { 55, 66, 77 });
	veci.at(3);
	veci.emplace_back(88);

	// iterate &  erase
	for (auto it = veci.begin(); it != veci.end(); ) {
		it = find(it, veci.end(), 5);

		if (it != veci.end())
		{
			cout << "found:" << it - veci.begin() << endl;
			it = veci.erase(it);
			//it++;
		}
	}

	// erase if 2 is found
	/*for (auto it = veci.begin(); it < veci.end();)
	{

		if (*it == 2)
		{
			it = veci.erase(it);

		}
		else
			it++;


	}*/

	// print
	for (auto n : veci) {
		cout << n << "\n";
	}

	cout << cs << endl;


}
void print(int a)
{
	// used in vector_for_each()
	cout << " " << a;
}
void vector_for_each()
{
	vector<int> v_int = { 1,2,3,6,5 };
	for_each(v_int.begin(), v_int.end(), print);
	for_each(v_int.begin(), v_int.end(), [](int& a) { cout << " " << a; });
}
