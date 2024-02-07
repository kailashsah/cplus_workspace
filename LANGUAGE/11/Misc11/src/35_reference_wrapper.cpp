#include <iostream>
#include <vector>
#include <string> // to_string()
using namespace std;

/*
	1. std::reference_wrapper<T> is a copyable and assignable object that imitates a reference (T&). It gives the non-nullable guarantee of a reference and the pointer-like flexibility to rebind to another object.

	2. The usual way to create an std::reference_wrapper<T> is via std::ref (or std::cref for reference_wrapper<const T>)
	https://www.nextptr.com/tutorial/ta1441164581/stdref-and-stdreference_wrapper-common-use-cases
*/
class RefTest {
public:
	int i;
};

void run_pointer_vectorr()
{
	// why use reference_wrapper over pointers (pointers drawback)
	vector <RefTest*> vec;
	RefTest* c = nullptr;
	vec.push_back(c);

	auto a = vec[0];
	if (vec[0])
		cout << vec[0]->i; // crash if 'no if validation', use reference_wrapper instead
	else
		cout << "null ptr" << endl;
}

void run_reference_vector()
{
	//1.
	{
		vector <RefTest> vec;
		RefTest b;
		b.i = 20;

		vec.push_back(b);

		b.i = 40; // its not updating the value.
		auto a = vec[0];
		cout << to_string(a.i) << endl; // 20 , its not updating the value. 
	}

	//2.
	{
		vector <reference_wrapper<RefTest>> vec;

		RefTest b;
		b.i = 20;

		vec.push_back(b);

		b.i = 40;
		auto a = vec[0];
		cout << to_string(a.get().i) << endl; // 40 // a.i is not possible
	}
}

//int main()
//{
//	run_reference_vector();
//	return 0;
//}
