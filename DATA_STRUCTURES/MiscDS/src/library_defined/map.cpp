#include <iostream>
#include<map>
#include<unordered_map>
using namespace std;
/*
	1. map is used to store elements as key,value pairs in order sorted by key. unordered_map is used to store elements as key,value pairs in non-sorted order.
	2. In the average case, the unordered_map is faster than a map since it uses a hash table, while a map is implemented using a self-balancing binary tree like a Red-Black tree.

*/
void map_impl()
{
	cout << endl << "map_impl() : " << endl;

	unordered_map <int, string> mapi;
	//1.
	mapi.insert(pair<int, string>(5, "five"));
	mapi.insert(make_pair(5, "five"));
	mapi.insert(pair<int, string>(1, "one"));

	//2.
	//std::qsort(mapi.begin(), mapi.end());
	//sort(mapi.begin(), mapi.end(), mapi.size(), greater<int> () );
	//sort(mapi.begin(), mapi.end());
	for (auto n : mapi)
	{
		cout << n.first << ":" << n.second << endl;
	}
	
	//3. remove element (5)
	for (auto it = mapi.begin(); it != mapi.end();)
	{
		it = mapi.find(5); // if not found, return mapi.end()
		if (it != mapi.end())
			it = mapi.erase(it);// retrn valid itr to next element.

	}
	cout <<"after removal (5) : " << endl;
	for (auto n : mapi)
	{
		cout << n.first << ":" << n.second << endl;
	}
	cout << endl;
}

class TestMap {
public:
	int n;
	TestMap()
	{
		cout << "ctor" << endl;
	}
	TestMap(const TestMap&) { cout << "copy" << endl; }
	TestMap& operator=(const TestMap& arg) { cout << "assignment" << endl; return *this; }
	TestMap(TestMap&&) { cout << "move ctor" << endl; }
	TestMap& operator=(TestMap&&) { cout << "move assignment" << endl; }
	~TestMap() { cout << "dtor" << endl; }
};

void map_impl_sqbracket()
{
	cout << endl << "map_impl_sqbracket() : " << endl;

	//1.
	unordered_map <int, int> mapi;
	mapi.insert(pair<int, int>(5, 5));
	mapi.insert(pair<int, int>(6, 6));
	mapi.insert(pair<int, int>(6, 6));
	if (mapi[5] == 5)
		cout << mapi[5] << endl; // 5 // access element using key	

	//2.
	unordered_map <string, int> mapStr;
	mapStr["a"] = 5;
	cout << "mapStr[\"a\"] : " << mapStr["a"] << endl; // [] can contain any type

	//3.
	/*
	unordered_map <TestMap, int> mapTest; // not possible, needs Hash, comparer() like equal_to()
	TestMap objTest;
	mapTest[objTest] = 5;
	cout << "mapStr[objTest] : " << mapTest[objTest] << endl; // [] can contain any type
	*/

	//4. 
	unordered_map < int, TestMap> mapTest; // TestMap as 2nd param should be value initialized
	TestMap objTest;
	cout << "before putting in map : " << &objTest << endl;
	objTest.n = 10;
	mapTest[5] = reference_wrapper<TestMap>(objTest); // calls ctor -> assignment
	objTest.n = 20;
	mapTest[5] = objTest; // ok .. same as above

	TestMap& rett = mapTest[5];
	rett.n = 30;
	TestMap& ret = mapTest[5];
	cout << "getting back from map : " << &ret << " " << ret.n; // 30
	/*
		0. both objects addresses are different.
		1. calls dtor, dtor for 2 times
		2. so it create the obj copy to put inside the map
	*/
	cout << endl;

	//5.
	cout << "unordered_map < int, TestMap&> : " << endl;

	unordered_map < int, TestMap*> mapTestt;
	TestMap* pTestt = new  TestMap();
	pTestt->n = 40;
	mapTestt[5] = pTestt; // ok
	mapTestt[5] = reference_wrapper<TestMap*>(pTestt);// ok
	auto retObj = mapTestt[5];
	cout << retObj->n << endl; // 40
	//5.1
	TestMap objTest1;
	objTest1.n = 50;
	mapTestt[5] = &objTest1;//ok
	retObj = mapTestt[5];
	cout << retObj->n << endl; // 50

	//6.
	cout << "unordered_map < int, TestMap&> : " << endl;
	unordered_map < int, TestMap&> mapTestRef;
	TestMap objTest2;
	objTest2.n = 70;
	//mapTestRef[5] = objTest2;  // (IMP)
	//mapTestRef[5] = reference_wrapper<TestMap>(objTest2);

	/*
		1.'std::pair<const int,TestMap &>::second': a reference type cannot be value-initialized

		2. The important difference apart from the syntactic sugar is that references cannot be changed to refer to another object than the one they were initialized with. This is why they cannot be stored in maps or other containers, because containers need to be able to modify the element type they contain
		3. Container values must be copyable or moveable if you do much of anything with the container. Clearly, that is not possible with references. Therefore, your program is illegal.
		4. References aren't copyable nor assignable. They're not supported as value types in any standard library container.
			You can store std::reference_wrapper<MyClass> or, almost equivalently MyClass* though
		https://stackoverflow.com/questions/29423487/stdunordered-map-with-references-as-values-does-not-work
	*/



}

void run_map()
{
	map_impl();
	map_impl_sqbracket();
}

//int main()
//{
//	run_map();
//	return 0;
//}