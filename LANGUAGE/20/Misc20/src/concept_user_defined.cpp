#include <iostream>
using namespace std;
/*
	1. Class templates, function templates, and non-template functions (typically members of class templates) may be associated with a constraint, which specifies the requirements on template arguments, which can be used to select the most appropriate function overloads and template specializations.

		Named sets of such requirements are called concepts. Each concept is a predicate, evaluated at compile time, and becomes a part of the interface of a template where it is used as a constraint

	2. Violations of constraints are detected at compile time, early in the template instantiation process, which leads to easy to follow error messages.

	3. A concept is a named set of requirements.
	4. Constraints
		A constraint is a sequence of logical operations and operands that specifies requirements on template arguments. They can appear within requires expressions or directly as bodies of concepts.
*/

//1.
template <typename T>
concept canAddtoIntV1 = requires (T t) {
	{t + 1} -> same_as<T>;
};

template <typename T>
T func_addV1(T&& t) requires canAddtoIntV1<T>
{
	return t + 2;
}


//2.
template <typename T>
concept canAddtoIntV2 = requires  {
	typename enable_if < is_integral<T>::value, T>::type;
};

template <typename T>
T func_addV2(T&& t) requires canAddtoIntV2<T>
{
	return t + 2;
}


void run_concepts_user_defined()
{
	//1.
	cout << func_addV1(4.5) << endl; // 6.5
	cout << func_addV1(4) << endl; // 6

	//2.
	//cout << func_addV2(4.5) << endl; // no instance of function templ matches the argument list
	cout << func_addV2(4) << endl; // 6
}

//int main()
//{
//	run_concepts_user_defined();
//	return 1;
//}