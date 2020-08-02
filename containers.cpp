#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <bitset>
#include <boost/functional/hash.hpp>
#include <deque>
#include <iomanip> // setw()
#include <set>
#include <forward_list>
#include <algorithm> // for_each()
#include <exception>

using namespace std;

namespace containers {

	void linked_list() {
		// create linked list and count the memebers of it
		struct Node {
		public:
			int d;
			Node *next;
		};

		class Count {
		public:
			int operator ()(Node *head) {
				if (head == NULL) {
					return 0;
				}
				int count = 1; // for head
				while (head->next != NULL) {
					count++;
					head = head->next;
				}
				return count;
			}
		} obj_count;

		Node *head = new Node();
		head->d = 10;

		Node *newNode = new Node();
		newNode->d = 2;
		head->next = newNode;

		newNode = new Node();
		newNode->d = 5;
		head->next->next = newNode;

		cout << obj_count(head);

	}

	void forward_list_demo() {
		forward_list<int> fl;

		auto print = [&fl](int item) {
			cout << setw(4) << item;
			//for_each(fl.begin(), fl.end(), [](int a) {cout << setw(4) << a; });
		};

		forward_list<int> fl_1 = { 2, 4, 3 };
		forward_list<int> fl_2 = { 7, 6, 5 };
		for_each(fl_1.begin(), fl_1.end(), [](int a) {
			cout << setw(4) << a;
		});

		cout << endl;
		for_each(fl_2.begin(), fl_2.end(), print);

		{
			forward_list<int> fl_1 = { 2, 4, 3 };
			forward_list<int> fl_2 = { 7, 6, 5 };
			cout << endl;
			cout << "after merge fl_1.merge(fl_2)" << endl;
			fl_1.sort();
			fl_2.sort();
			fl_1.merge(fl_2); // it will break if list is not sorted.
			for_each(fl_1.begin(), fl_1.end(), print);
		}

		cout << endl;
		cout << "after splice_after fl_1" << endl;
		fl_1.splice_after(fl_1.begin(), fl_2); // insert f2 after the position given
		for_each(fl_1.begin(), fl_1.end(), print);

	}

	void set_demo() {
		auto print = [&](set<int> sett) {

			for (auto item : sett) {
				cout << setw(4) << item;
			}
		};

		{
			// case - 1
			set<int> sett = { 2, 6, 1, 0 };
			print(sett);
			cout << endl;

			cout << typeid(sett).name(); // print class name
		}

		{
			// case - 2
			set<int> sett = { 2, 6, 1, 0 };
			//set <int, greater<>> sett = { 2,6,1,0 };
			//print(sett);   // not possible due to predicate

			//for_each (sett.begin(), )
			cout << endl;
		}

		{
			// case - 3
			set<int, less<int>> sett = { 2, 6, 1, 0 };
			print(sett);

			sett.erase(2);
			cout << endl;
			print(sett);
			cout << endl;

		}
	}

	void deque_demo() {
		deque<int> dq = { 2, 3, 4 };
		dq.push_front(1);
		dq.push_back(5);

		for (auto item : dq) {
			cout << item << setw(4);
		}
		cout << endl;
	}

	void hash_demo() {
		hash<string> hashString;
		cout << hashString("Kailash") << endl;
		cout << hashString("geekofgeeks") << endl;
	}

	void find_elements_unordered_map() {
		std::unordered_multimap<std::string, std::string> myumm = { { "apple",
				"red" }, { "apple", "green" }, { "orange", "orange" }, {
				"strawberry", "red" } };

		auto p = myumm.equal_range("apple");
		/*for (auto it = p.first; it != p.second; it++)
		 cout << it->first << "- " << it->second << endl;*/

		auto it = p.first;
		while (it != p.second) {
			cout << it->second << endl;  // this will print red and green
			it++;
		}

		auto pt = myumm.find("apple");
		for (auto it = pt->second.begin(); it != pt->second.end(); ++it) {
			//std::cout << *it;
		}

	}

	void bit_set() {
		const int m = 5;
		bitset<m> b1, b2;

		b1.set(1, 1);
		b2.set(2, 1);

		//b1.reset();
		//b1.set();

		cout << b1 << endl << b2 << endl;

		cout << "after bitwise OR operation" << endl;
		cout << (b1 ^ b2) << endl; // bitwise xor operation 0,0 = 1,1 -> 0  ||  1,0 = 0,1 -> 1

		cout << "after bitwise OR operation storing in bitwise object" << endl;
		b1 = b1 ^ b2;  // same output as above
		cout << b1 << endl;

		int a[] = { 1, 2, 3, 4 };
		for (int i = 0; i < 4; i++) {
			// this method is used to count common integer elements in two arrays.
			// we do b1 & b2 AND operation for that

			b1.set(a[i]);
		}
		cout << b1 << endl;

	}

	struct tup_hash {
		template<class T1, class T2>
		size_t operator ()(const tuple<T1, T2> &t) const {
			//auto h1 = hash<T1>{} get<0>(t);
			//auto h2 = hash<T2>{} get<1>(t);
			//return h1 ^ h2;
			//return boost::hash_combine(h1,h2);
			return 1;
		}
	};

	void tuple_demo() {
		tuple<int, string> tup = make_tuple(1, "aaa");
		cout << get<0>(tup) << "-";
		cout << get<1>(tup).c_str() << endl;

		int index;
		string name;
		tie(index, name) = make_tuple(2, "bbb");
		cout << index << "-" << name << endl;

		map<tuple<int, string>, string> mapp;
		mapp[make_tuple(1, "bbb")] = "mountains";

		//using tup1 = tuple<int, string>;
		//hash <tup1> hashFn;

		unordered_map<tuple<int, string>, string, tup_hash> hash_table;
		//unordered_map <tuple<int, string>, string, boost::hash<tuple<int, string>>> hash_table;
		hash_table[make_tuple(1, "bbb")] = "mountains";

		auto it = hash_table.begin();
		cout << "-" << it->second << endl;

	}

	void map_basic() {
		pair<int, int> insert = make_pair(10, 20);
		cout << "pair to insert in map is " << insert.first << "-"
				<< insert.second << endl;

		map<int, int> map_num;
		map_num.insert(insert);
		insert = make_pair(20, 20);
		map_num.insert(insert);
		map_num[3] = 4;
		map_num.insert(make_pair(4, 3));
		map_num.insert(make_pair(4, 3));// this will not work, already inserted
		map_num[4] = 30; // updation

		for (auto item : map_num) {
			cout << item.first << "-" << item.second << endl;
		}

		cout << "using map iterator" << endl;
		for (map<int, int>::iterator it = map_num.begin(); it != map_num.end();
				it++) {
			cout << it->first << "-" << it->second << endl;
		}
	}

	std::string& ltrim(std::string &s) {
		size_t first = s.find_first_not_of(' ');

		if (string::npos == first) {
			return s;
		}

		s = s.substr(first, s.length() - 1);
		return s;
	}

	std::string& rtrim(std::string &s) {
		size_t last = s.find_last_not_of(' ');

		if (string::npos == last) {
			return s;
		}

		s = s.substr(0, last + 1);
		return s;
	}

	int main() {

		//linked_list();
//		forward_list_demo();
		//set_demo();
		//deque_demo();
		//find_elements_unordered_map();

		//hash_demo();
//		bit_set();
		//tuple_demo();
		//map_basic();

		getchar();
		return 0;
	}

}

/*
int main() {
	containers::main();
	return 0;
}
*/
