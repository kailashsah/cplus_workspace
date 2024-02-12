#include <iostream>
using namespace std;
/*
	1. The main advantage of this feature is that it allows us to use a function to evaluate compile-time constant. With this, we could calculate the size of the array at compile time which was not possible before.
	2. https://www.geeksforgeeks.org/understanding-constexper-specifier-in-cpp/ 
	3. constexpr can be used with constructors but with condition that argument and return type must be of literal types. 
	4. Literals - https://www.geeksforgeeks.org/literals-in-c-cpp-with-examples/, interger, float, char, string, bool. Literals represent fixed values that cannot be modified
*/

constexpr int addOne(int n)
{
	return [n] { return n + 1; }();
}

constexpr void void_fn() {
	// ok
}

// .............................................
// A class with constexpr 
// constructor and function 
class Rectangle
{
    int _h, _w;
public:
    // A constexpr constructor 
    constexpr Rectangle(int h, int w) : _h(h), _w(w) {}

    constexpr int getArea() const { return _h * _w; }
};

// driver program to test function 
int run_rectangle()
{
    // Below object is initialized at compile time 
    constexpr Rectangle obj(10, 20);
    std::cout << obj.getArea(); 
    /*
        cannot convert 'this' pointer from 'const Rectangle' to 'Rectangle &'
        replace 
         constexpr int getArea() { return _h * _w; }
        with
         constexpr int getArea() const { return _h * _w; }
    */ 

    /*
        Restrictions on constructors that can use constexpr:
            No virtual base class
            Each parameter should be literal
            It is not a try block function
    */
    return 0;
}

// .............................................
