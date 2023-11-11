#include <iostream>
using namespace std;

#include<vector>
#include<algorithm> // generate()
void fill_random_numbers()
{
	vector<int> vec(100);
	vector<int> vec_c(100);
	//1.
	//srand(100);
	//srand((unsigned)time(nullptr));
	//2.
	// fill 1 to 100 
	generate(vec.begin(), vec.end(), []() {return 1 + rand() % 99; });
	generate(vec_c.begin(), vec_c.end(), []() {return 1 + rand() % 99; });
	sort(vec.begin(), vec.end());
	sort(vec_c.begin(), vec_c.end());
	for (auto i : vec) {
		cout << i << " ";
	}
	cout << endl;
	for (auto i : vec_c) {
		cout << i << " ";
	}
}


//int main()
//{
//	fill_random_numbers();
//	return 0;
//}
