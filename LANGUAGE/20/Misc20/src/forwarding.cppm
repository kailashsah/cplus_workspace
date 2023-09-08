#include <iostream>
#include "./cplus20.h"
using namespace std;

//#define cplus20
#ifdef cplus20

template <typename Arg, typename... Args>
void forwarding_ostream(std::ostream& out, Arg&& arg, Args&&... args)
{
	out << std::forward<Arg>(arg);
	((out << ',' << std::forward<Args>(args)), ...);
}

template <typename... Args>
void forwarding_cout(Args&&... args)
{
	((cout << std::forward<Args>(args)), ...);
}

void run_lambda_returned_()
{

   //forwarding_ostream(std::cout, 1, 2, 3);

   //forwarding_cout( 1, 2, 3);
   

}

//int main()
//{
//	run_lambda_returned_();
//	return 1;
//}


////////////////////////

#endif
