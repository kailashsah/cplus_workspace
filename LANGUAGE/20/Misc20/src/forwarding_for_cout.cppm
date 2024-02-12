#include <iostream>
using namespace std;
/*
	1.	In order to avoid this copy, you need "perfect forwarding". 
		(https://stackoverflow.com/questions/8526598/how-does-stdforward-work-especially-when-passing-lvalue-rvalue-references)
	2. 
*/

//1.
template <typename Arg, typename... Args>
void forwarding_ostream(std::ostream& out, Arg&& arg, Args&&... args)
{
	out << std::forward<Arg>(arg);
	((out << ',' << std::forward<Args>(args)), ...);
}

//2.
template <typename... Args>
void forwarding_cout(Args&&... args)
{
	((cout << std::forward<Args>(args)), ...);
}

void run_lambda_returned_()
{
   forwarding_ostream(std::cout, 1, 2, 3); // 1,2,3
   forwarding_cout( 4, 5, 6); // 456
}

//int main()
//{
//	run_lambda_returned_();
//	return 1;
//}


////////////////////////

