#include <iostream>
using namespace std;
/*
	1. c++20
	
	2. Function templates ref and cref are helper functions that generate an object of type std::reference_wrapper, using template argument deduction to determine the template argument of the result.

	3. parameter - 
		t -	lvalue reference to object that needs to be wrapped or an instance of std::reference_wrapper
*/

int run_ref();
//
#include<thread>
#include <string> // to_string
void update(int& data)  //expects a reference to int
{
	// demo of std::ref(data)
	data = 15;
}

int run_ref()
{
	int data = 10;

	//1. This doesn't compile as the data value is copied when its reference is expected.
	//std::thread t2(update, data);   
	//std::thread t3(update, move(data));

	//2.
	std::thread t1(update, std::ref(data));  // works, if reference provided in this way
	t1.join();
	cout<< to_string(data); //  15

	return 0;
}

//2.
#include<functional> //function<> .. bind()
void f(int& n1, int& n2, const int& n3)
{
	std::cout << "In function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
	++n1; // increments the copy of n1 stored in the function object
	++n2; // increments the main()'s n2
	// ++n3; // compile error
}

void run_with_bind()
{
	int n1 = 1, n2 = 2, n3 = 3;
	std::function<void()> bound_f = std::bind(f, n1, std::ref(n2), std::cref(n3));
	n1 = 10;
	n2 = 11;
	n3 = 12;
	std::cout << "Before function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
	bound_f();
	std::cout << "After function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
	/*
		Before function: 10 11 12
		In function: 1 11 12
		After function: 10 12 12
	*/
}

void run_with_pointers()
{
	int n1 = 1;
	int* n2 = new int (2);
	int* n3 = new int (3);
	//1.
	//std::function<void()> bound_f = std::bind(f, n1, std::ref(n2), std::cref(n3)); // binding issue with pointer for reference_wrapper<int*> & reference_wrapper<const int*>
	
}

//int main()
//{
//	run_ref();
//	return 0;
//}
