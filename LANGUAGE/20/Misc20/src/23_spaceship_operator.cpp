#include <iostream>
using namespace std;

/*
	1. 3-way comparision operator
	2. 
*/

void fn_one() {
	int x = 10;
	int y = 20;

	auto res = x <=> y; // spaceship operator

	if (res < 0)
		cout << "x(10) is smaller than y(20)" << endl;
	else if (res > 0)
		cout << "y(20) is smaller than x(10)" << endl;
	else if (res == 0)
		cout << "x(10) is equal y(20)" << endl;
}

void fn_two() {
	constexpr int m{ 1 };
	constexpr int n{ 2 };
	constexpr auto res{ m <=> n };

	//1.
	if (std::is_lt(res)) { // header <compare>
		std::cout << m << " is less than " << n << std::endl;
	}
	else if (std::is_gt(res)) {
		std::cout << m << " is greater than " << n << std::endl;
	}
	else if (std::is_eq(res)) {
		std::cout << m << " is equal to " << n << std::endl;
	}
	
	//2.
	if(res == strong_ordering::less)
		std::cout << m << " is less than " << n << std::endl;
	else if(res == strong_ordering::greater)
		std::cout << m << " is greater than " << n << std::endl;
	else if (res == strong_ordering::equal)
		std::cout << m << " is equal to " << n << std::endl;
	else if (res == strong_ordering::equivalent)
		std::cout << m << " is equivalent than " << n << std::endl;
	/*
		equal vs equivalent -
		1. there is no difference between the two. Hovewer, std::strong_ordering is the only category that defines equal. All other categories only define equivalent.
		
		2. equivalent means "considered to be equal according to a certain criteria, but may have irrevelant differences", while equal means "indistinguishable". Thus equality implies equivalence.
		
		3. std::{weak,partial}_ordering::equivalent is intended to be used when different objects are considered to be the same, but may have irrevelant differences.
	*/


}

void run_spaceship_op() {
	//1.
	fn_one();
	
	//2.
	puts("fn_two");
	fn_two();
}

//int main()
//{
//	run_spaceship_op();
//	return 1;
//}