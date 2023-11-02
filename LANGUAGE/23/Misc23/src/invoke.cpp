#include <iostream>
using namespace std;
/*
	1. c++11. std::invoke takes something callable, and arguments to call it with, and does the call.

	2. Something callable includes a function pointer or reference, a member function pointer, an object with an operator(), or a pointer to member data.

	3. In the member cases, the first argument is interpreted as the this. Then remaining arguments are passed to () (except in the pointer-to-member-data-case), with std::reference_wrappers unwrapping.

	4. 
*/
#include <functional>
#include <functional>
#include <iostream>
#include <type_traits>

struct Foo
{
    Foo(int num) : num_(num) {}
    void print_add(int i) const { std::cout << num_ + i << '\n'; }
    int num_;
};

void print_num(int i)
{
    std::cout << i << '\n';
}

struct PrintNum
{
    void operator()(int i) const
    {
        std::cout << i << '\n';
    }
};
void run_invoke()
{
    // invoke a free function
    std::invoke(print_num, -9);

    // invoke a lambda
    std::invoke([]() { print_num(42); });

    // invoke a member function
    const Foo foo(314159);
    std::invoke(&Foo::print_add, foo, 1);

    // invoke (access) a data member
    std::cout << "num_: " << std::invoke(&Foo::num_, foo) << '\n'; // IMP

    // invoke a function object
    std::invoke(PrintNum(), 18);
}

//int main()
//{
//	run_invoke();
//	return 0;
//}