#include <iostream>
using namespace std;

/*
	1. if you have a use-case for is_pod, you might want to consider the possibility that is_standard_layout might actually be a better (more accurate) choice in that case, since POD is essentially a subset of standard layout.

	2. A standard-layout type is a type with a simple linear data structure and access control that can easily be used to communicate with code written in other programming languages, such as C. This is true for scalar types, standard-layout classes and arrays of any such types.
	
	3. Standard layout types trigger several special clauses in the standard, which may affect code generation and optimizations, or simply whether certain constructs are undefined. In particular, standard layout classes require the empty base optimization.

		Note that standard layout types are a generalization of PODs in the 2003 standard, if the POD/standard layout refinement has not happened when this type function is initially implanted.

*/

#include <type_traits>
class st {
	st() = delete;
	st(st&&) = delete;
};

void run_is_pod()
{
	//cout << is_pod<st>; // deprecated in c++20
	cout << is_standard_layout<st>::value; // returns false if any private member, in case of public return is ture;
}
