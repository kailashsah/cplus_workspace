#include <iostream>
using namespace std;

/*
	1.  std::move_if_noexcept obtains an rvalue reference to its argument if its move constructor does not throw exceptions or if there is no copy constructor (move-only type), otherwise obtains an lvalue reference to its argument. It is typically used to combine move semantics with strong exception guarantee.

	2. Templates like move_if_noexcept will detect if the move constructor is defined with noexcept and will return a const& instead of a && of the type if it is not. It's a way of saying to move if it is very safe to do so.

*/

#include <iostream>
#include <utility>

struct Bad
{
	Bad() {}
	Bad(Bad&&) // may throw
	{
		std::cout << "Throwing move constructor called\n";
	}
	Bad(const Bad&) // may throw as well
	{
		std::cout << "Throwing copy constructor called\n";
	}
};

struct Good
{
	Good() {}
	Good(Good&&) noexcept // will NOT throw
	{
		std::cout << "Non-throwing move constructor called\n";
	}
	Good(const Good&) noexcept // will NOT throw
	{
		std::cout << "Non-throwing copy constructor called\n";
	}
};


void run_move_if_noexcept()
{
	Good g;
	Bad b;

	//1.
	[[maybe_unused]] Good g2 = std::move_if_noexcept(g); // Non-throwing move constructor called

	//2.
	[[maybe_unused]] Bad b2 = std::move_if_noexcept(b);   // Throwing copy constructor called becoz "noexcept" is not specified
	/*
		if  Bad(const Bad&) removed, it calls  // Throwing move constructor called
	*/

	//[[maybe_unused]] Bad b2 = std::move(b);               //Throwing move constructor called
}

//int main()
//{
//	run_move_if_noexcept();
//	return 0;
//}
