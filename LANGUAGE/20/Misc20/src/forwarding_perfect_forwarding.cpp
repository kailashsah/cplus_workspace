#include <iostream>
using namespace std;
/*
	1. perfect forwarding -  means that a function template can pass its arguments through to another function whilst retaining the lvalue/rvalue nature of the function arguments by using std::forward. This is called "perfect forwarding", avoids excessive copying, and avoids the template author having to write multiple overloads for lvalue and rvalue references.

	2. Perfecting forwarding is an important technique built atop rvalue references. It allows move semantics to be automatically applied, even when the source and the destination of a move are separated by intervening function calls.

	Common examples -  standard library functions like make_shared, which “perfect-forwards” its arguments to the class constructor of whatever object the to-be-created shared_ptr is to point to.

	3. https://www.justsoftwaresolutions.co.uk/cplusplus/rvalue_references_and_perfect_forwarding.html

*/
void run_perfect_forwarding();
//
#include <vector>
class X
{
	std::vector<double> data;
public:
	X() :
		data(100000) // lots of data
	{}
	X(X const& other) : // copy constructor
		data(other.data)   // duplicate all that data
	{}

	X(X&& other) :  // move constructor
		data(std::move(other.data)) // move the data: no copies
	{}

	X& operator=(X const& other) // copy-assignment
	{
		data = other.data; // copy all the data
		return *this;
	}

	X& operator=(X&& other) // move-assignment
	{
		data = std::move(other.data); // move the data: no copies
		return *this;
	}

};

X make_x(); // build an X with some data

void g(X&& t) {}	// A
void g(X& t) {}     // B

template<typename T>
void f(T&& t)
{
	g(std::forward<T>(t));
	/*
		This time our function f forwards its argument to a function g which is overloaded for lvalue and rvalue references to an X object. g will therefore accept lvalues and rvalues alike, but overload resolution will bind to a different function in each case.
	*/
}

void h(X&& t)
{
	g(t);// t is treated as lvalue
}

void run_perfect_forwarding()
{
	X x;
	f(x);   // 1
	/*
		At line "1", we pass a named X object to f, so T is deduced to be an lvalue reference: X&, as we saw above. When T is an lvalue reference, std::forward<T> is a no-op: it just returns its argument. We therefore call the overload of g that takes an lvalue reference (line B).
	*/
	f(X()); // 2
	/*
		At line "2", we pass a temporary to f, so T is just plain X. In this case, std::forward<T>(t) is equivalent to static_cast<T&&>(t): it ensures that the argument is forwarded as an rvalue reference. This means that the overload of g that takes an rvalue reference is selected (line A).

		This is called perfect forwarding because the same overload of g is selected as if the same argument was supplied to g directly. It is essential for library features such as std::function and std::thread which pass arguments to another (user supplied) function.
	*/
	//h(x); // error
	/*
		Note that perfect forward is unique to template functions: we can't do this with a non-template function such as h, since we don't know whether the supplied argument is an lvalue or an rvalue.

		Within a function that takes its arguments as rvalue references, the named parameter is treated as an lvalue reference. Consequently the call to g(t) from h always calls the lvalue overload.

		If we changed the call to g(std::forward<X>(t)) then it would always call the rvalue-reference overload.
		The only way to do this with "normal" functions is to create two overloads: one for lvalues and one for rvalues.
	*/
	h(X()); // 3
}

//int main()
//{
//	run_perfect_forwarding();
//}

