#include <iostream>
using namespace std;

template<class InputIt, class UnaryFunction>
UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f)
{
	for (; first != last; ++first) {
		f(*first);
	}
	return f;
}


void run_template()
{
	
}

//int main()
//{
//	run_template();
//	return 0;	
//}
