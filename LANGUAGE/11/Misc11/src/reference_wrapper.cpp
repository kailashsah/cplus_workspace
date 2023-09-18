#include <iostream>
#include <vector>
#include <string> // to_string()
using namespace std;

/*
	std::reference_wrapper<T> is a copyable and assignable object that imitates a reference (T&). It gives the non-nullable guarantee of a reference and the pointer-like flexibility to rebind to another object.

	The usual way to create an std::reference_wrapper<T> is via std::ref (or std::cref for reference_wrapper<const T>)
	https://www.nextptr.com/tutorial/ta1441164581/stdref-and-stdreference_wrapper-common-use-cases
*/
class RefTest {
public:
	int i;
};

void run_vectorr()
{
	vector <RefTest*> vec;
	RefTest* c = nullptr;
	vec.push_back(c);

	auto a = vec[0];
	if (vec[0])
		cout << vec[0]->i; // crash if no if validation, use reference_wrapper instead
	else
		cout << "null ptr" << endl;
}

void run_reference_vector()
{
	vector <reference_wrapper<RefTest>> vec;

	RefTest b;
	b.i = 20;

	vec.push_back(b);

	b.i = 40;
	auto a = vec[0];
	cout << to_string(a.get().i) << endl;
}


//int main()
//{
//	run_reference_vector();
//	return 0;	
//}
