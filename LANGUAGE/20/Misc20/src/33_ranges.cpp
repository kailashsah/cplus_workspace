#include <iostream>
using namespace std;

/*
	1.  Range is a simple concept: it’s just a pair of two iterators - to the beginning and to the end of a sequence (or a sentinel(guard) in some cases). Yet, such an abstraction can radically change the way you write algorithms.
	
	2.  you can take advantage of a set of standard algorithms that support activities like 
		data filtering, 
		transformation, and 
		sorting

	3. views can provide mutable access to the underlying range. (sort() example)
*/
#include <vector>
#include <ranges>
void run_filter_adaptor()
{
	std::vector<int> nums = { 1, 2, 3, 4, 5 };
	auto even_nums = nums | std::views::filter(
		[](int n) {	return n % 2 == 0;} // lambda
	); //the nums range can be linked with the filter adaptor via the | pipe operator
	cout << typeid(even_nums).name() << endl; // std::ranges::filter_view  
	
	//(scene 1)
	//nums[0] = 2; // it changes the output of for() -> 2 2 4

	// (scene 3)
	//auto view1 = even_nums.base(); // prints 1 2 3 4 5 fm below loop
	
	for (auto num : even_nums) {
		std::cout << num << " "; // 2 4
		//(scene 2)
		//nums[0] = 2; 
	}
	/*
		Observations - 
		1. in case (scene 1) -> it prints 2 2 4. it means the for() execution brings the call to filter_view ie, on-demand
		2. (scene 2) brings no changes bcoz by that time filter_view was created.
	*/
}

void run_transform()
{
	std::vector<int> ints{ 0,1,2,3,4,5 };
	auto even = [](int i) { return 0 == i % 2; };
	auto square = [](int i) { return i * i; };

	//evens are 0 2 4
	for (int i : ints | std::views::filter(even) | std::views::transform(square)) {
		std::cout << i << ' '; // 0 4 16
	}

	for (int i : ints) {
		std::cout << i << ' '; // 0 1 2 3 4 5 
	}
}

#include <algorithm>
void run_sort() {
	std::vector<int> ints{ 0,1,2,3,4,5 };
	std::vector<int>* intss = &ints;

	auto rev_ints = ints | std::views::reverse;
	cout << typeid(rev_ints).name() << endl; // std::ranges::reverse_view
	for (int i : rev_ints)
		cout << i << " "; // 5 4 3 2 1 0 
	
	//ints[0] = 10; // it will change the views also
	cout << endl;
	std::ranges::sort(rev_ints); // <algorithm>
	for (int i : rev_ints)
		cout << i << " "; // 0 1 2 3 4 5 
	
	cout << endl;
	for (int i : *intss)
		cout << i << " "; // 5 4 3 2 1 0 
	/* 
		strange - if reverse_view saved in local variable it mutates the orignal container; 
		if used directly in for(), it won't be changed. see (3)
	*/

}

//(3).
void run_reverse_view() {
	std::vector<int> ints{ 0,1,2,3,4,5 };
	
	for (int i : ints | std::views::reverse)
		cout << i << " ";  // 5 4 3 2 1 0

	cout << endl;
	for (int i : ints)
		cout << i << " "; // 0 1 2 3 4 5

}

void run_all_views() {

	//1.
	run_filter_adaptor();
	cout << endl;

	//2.
	puts("run_transform()");
	run_transform();
	cout << endl;

	//3.
	puts("run_sort()");
	run_sort();

	//4.
	puts("run_reverse_view()");
	run_reverse_view();
}

//int main()
//{
//	run_all_views();
//	return 1;
//}

