#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <list>
#include <queue>
#include <stack>
using namespace std;

//.................................................
void buff_unique_ptr() {

	uint32_t size = 20;
	unique_ptr<char> char_buff(new char[size]);
	strcpy(char_buff.get(), "I am unique ptr ");
	cout << char_buff;
	cout << endl;
	//
	unique_ptr<char[]> c_ptr;			// I did mistake for '[]'
	c_ptr = make_unique<char[]>( size); // I did mistake for '[]'
	//unique_ptr<char[]> c_ptr = make_unique<char[]>(size+100); // I did mistake for '[]'
	strcpy_s(c_ptr.get(),size, "I am make_un");
	cout << c_ptr;
}
//.................................................

void heap_min() {
	priority_queue <int, vector<int> , greater<int> > minheap;
	minheap.push(3);
	minheap.push(6);
	minheap.push(9);
	while (minheap.empty() == false) {
		cout << minheap.top() << " ";
		minheap.pop();
	}
	cout << endl;
	//...........................

	cout << "max heap :" << endl;
	priority_queue <int, deque<int>, less<int> > maxheap;
	maxheap.push(3);
	maxheap.push(6);
	maxheap.push(9);
	while (maxheap.empty() == false) {
		cout << maxheap.top() << " ";
		maxheap.pop();
	}
}
//.................................................

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
//.................................................

void data_str_array() {
	array<int, 10> arr = {0};
	array<int, 50> arro;
	for_each(arr.begin(), arr.end()-1, [i = 0](auto& a) mutable {a = ++i; return a; });
	const int * p = arr.data();
	
	cout << arr.size() << arr.max_size();
	for (auto a : arr)
		cout << a << " ";
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

	// second method ... 
	using roww = array<int, 2 >;
	array<roww, 2> arr;
	arr[0] = { 1,2 };
	arr[1] = {3, 4};
	cout << endl;
	for (auto r : arr) {
		cout << r[0] << r[1];
		cout << endl;
	}

	
}
//.................................................

void find_str_str() {
	string str = "first 21 second 21 third ";
	uint32_t pos = 0;
	uint32_t  lpos = 0;
	string tofind = "21";
	while ( (pos = str.find(tofind, pos)) != string::npos) {
		string ss = str.substr(lpos, pos - lpos);
		cout << ss << " ";
		pos += tofind.length();
		lpos = pos;
	}
	if (lpos < str.length())
		cout << str.substr(lpos, str.length() - lpos);

}
#include <sstream>
void string_split() {
	string str = "first 21 second 21 third ";
	stringstream ss(str);
	string strr;
	while (getline(ss, strr, '2')) {
		cout << strr << " ";
	}

	cout << endl;
	char* token = strtok(str.data(), "21");
	while (token != nullptr) {
		cout << token << " ";
		token = strtok(0, "21");

	}
}

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
	_Random_shuffle1(vec.begin(), vec.end(), l );
	for_each(vec.begin(), vec.end(), [](auto a) { cout << a << " "; });
	cout << "count is " << vec.size();
	//iota();
}
void findin_string() {
	string str = "I 2 m 2 r";
	string tofind = "2";
	uint32_t pos = 0;// = str.find(tofind);
	uint32_t cpos = 0;
	string sstr;
	while ((pos = str.find(tofind, pos)) != string::npos) {
		sstr = str.substr(cpos, pos - cpos);
		cout << sstr << " ";
		pos += tofind.length();
		cpos =  pos;
	}

	//erase
	erase(str, ' ');
	cout << endl ;
}

void run_jan_seven() {
	
	// main();
	// 
	buff_unique_ptr();
	//heap_min();
	//
	//data_str_list_erase ();
	//
	//vector_2D_array();
	// 
	//data_str_array();
	// 
	//string_split();
	// 
	//find_str_str();
	// 
	//findin_string();
	// 
	//fill_array();
}

//int main()
//{
//	run_jan_seven();
//	//return 0;
//}
//
