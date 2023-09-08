#include<iostream>
#include <list>
using namespace std;

// hash map
// https://www.geeksforgeeks.org/c-program-hashing-chaining/
using uint = unsigned int;
class hashmap {
	const uint m_cbucket;
	list<uint>* llist;
public:
	hashmap(int bucket): m_cbucket(bucket){
		llist = new list<uint>[m_cbucket];
	}
	
	void insertKey(int key)  // -> entry point
	{
		uint bucket = hashFunction(key);
		llist[bucket].push_back(key);
	}
	void displayMap() {
		for (uint i{}; i < m_cbucket; ++i) {
			cout << endl;
			cout << i << "-->";
			for (auto itr = llist[i].begin(); itr != llist[i].end();  ++ itr) {
				cout << *itr << ",";

			}
		}
	}
	void deleteKey(int key) {
		list<uint>::iterator itr;
		uint bucket = hashFunction(key);
		// 1.
		/*for (itr =  llist[bucket].begin(); itr != llist[bucket].end(); ++itr) {
			if (*itr == key)
				break;
		}
		if (itr != llist[bucket].end())
			llist[bucket].erase(itr);*/

		// 2.
		erase(llist[bucket], key);
	}
private:	
	uint hashFunction(int key) {
		return (key % m_cbucket);
	}
	
};
//
void run_hash_map() {
	int ele[] = { 15, 11, 27, 8, 12 };
	uint n = sizeof(ele) / sizeof(uint);
	cout << "count : " << n << endl;
	//
	hashmap map(7); // assume we have 7 total buckets
	for (uint i{}; i < n; ++i) {
		map.insertKey(ele[i]);
	}
	//map.deleteKey(15);
	map.displayMap();
	//
}
//.................................................
//int main()
//{
//	run_hash_map();
//
//	return 0;
//}

