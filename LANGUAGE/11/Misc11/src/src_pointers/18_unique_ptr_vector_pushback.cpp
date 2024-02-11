#include <iostream>

#include <memory> // make_unique
#include <algorithm>
using namespace std;
#include <vector>
/*
	1. Why can I not push_back a unique_ptr into a vector?
*/
void run_unique_ptr_pushback()
{
	std::vector<std::unique_ptr<int>> vec;

	int x(1);
	std::unique_ptr<int> ptr2x(&x);
	//1.
	//vec.push_back(ptr2x); //This tiny command has a vicious error.
	//std::unique_ptr<int,std::default_delete<int>> &)': attempting to reference a deleted function	

	/*
		1. vec.push_back(std::move(ptr2x));
		unique_ptr guarantees that a single unique_ptr container has ownership of the held pointer. This means that you can't make copies of a unique_ptr (because then two unique_ptrs would have ownership), so you can only move it.

		2. std::unique_ptr has no copy constructor. You create an instance and then ask the std::vector to copy that instance during initialisation. that's not possible.
	*/
}

//int main()
//{
//	run_unique_ptr_pushback();
//	return 0;
//}
