#include <iostream>
using namespace std;

/*
	Lazy means the instantiation of a member function of a class template happens only when needed.
	https://www.modernescpp.com/index.php/surprise-included-inheritance-and-member-functions-of-class-templates/
*/
template<class T>
struct Lazy {
	void func() { std::cout << "func\n"; }
	void func2(); // not defined (1) - still compiler has accepted it.
};


void run_template_lazy()
{

	std::cout << '\n';

	Lazy<int> lazy;
	lazy.func();

	std::cout << '\n';
}

//int main()
//{
//	run_template_lazy();
//	return 0;	
//}
