#include <iostream>
using namespace std;
/*
	1. rvalue return fm function
	2. One thing that can greatly benefit from returning an rvalue reference is a member function of a temporary object.
		
*/

#include <vector>
//1.
class foo_basic
{
	std::vector<int> bar;
public:
	foo_basic(int n) : bar(n) {}
	std::vector<int>& get_vec() { return bar; }
};

void run_rvalue_return_v1 () {
	auto vec = foo_basic(10).get_vec(); // you have to copy because get_vec returns an lvalue.
}

//2.	
class foo_fix
{
	std::vector<int> bar;
public:
	foo_fix(int n) : bar(n) {}
	std::vector<int>& get_vec()& { return bar; }
	std::vector<int>&& get_vec()&& { return std::move(bar); }
};
void run_rvalue_return_v2() {
	auto vec = foo_basic(10).get_vec(); // Then vec would be able to move the vector returned by get_vec and you save yourself an expensive copy operation.
}
//int main()
//{
//	run_rvalue_return_v1();
//	run_rvalue_return_v2();
//	return 0;
//}

