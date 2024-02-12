#include <iostream>
using namespace std;
/*
	1. Designated Initialization is a form of Aggregate Initialization. more readable way of initializing aggregate types.
	2. As of C++20, an Aggregate type::

		is an array type or,
		is a class type that:
		has no private or protected direct non-static data members
		has no user-declared or inherited constructors
		has no virtual, private, or protected base classes
		has no virtual member functions.

	3. Type obj = { .designator { val }, .designator { val2 }, ... };
		Designator points to a name of a non-static data member from our class, like .x or .y.
*/
void run_designated_constructor();
void run_designated_constructor2();
//
class Date {
public:
	int year; int month;  int day;
	/*virtual void a() {

	}*/ // 'Date': designated initialization can only be used to initialize aggregate class types

	/*Date()
	{

	}*/ // error

	//protected: // error
	//	int m;
};

void run_designated_constructor()
{
	Date d{
	.year = 2050, .month = 5, .day = 10
	};
}

void run_designated_contructor2() {
	struct Point {
		double x{ 0.0 };
		double y{ 0.0 };
	};

	const Point p{ .x = 10.0, .y = 20.0 };

	const Point offset{ .x { 100.0 }, .y { -100.0 } };

	// mix also possible:
	const Point translation{ .x = 50.0, .y { -40.0 } };
}

//int main() {
//	run_designated_constructor();
//}