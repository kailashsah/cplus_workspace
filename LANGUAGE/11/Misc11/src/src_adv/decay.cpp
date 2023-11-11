#include <iostream>
using namespace std;
/*
	1. decay<> - std::decay type trait lists all these decay conversions. std::decay can be used to simulate them and there is also a templated type alias std::decay_t for convenience.

	q. https://64.github.io/cpp-faq/decay/#:~:text=For%20parameters%20which%20are%20passed,const%20qualifier%20in%20our%20example.
*/

void run_decay()
{
	/*
		// no decay
		std::decay_t<int>           -> int
		
		// discarding references
		std::decay_t<int&>          -> int
		
		// discarding references and const qualifier
		std::decay_t<const int&>    -> int
		
		// discarding volatile
		std::decay_t<volatile int>  -> int
		
		// array-to-pointer
		std::decay_t<int[8]>        -> int*
		
		// array-to-pointer, and also discarding the reference
		std::decay_t<int(&)[8]>     -> int*
		
		// function-to-pointer
		std::decay_t<int(int)>      -> int(*)(int)
	*/

	/*
		template <class T1, class T2>  
		inline pair< typename decay<T1>::type, typename decay<T2>::type >  
		make_pair(T1&& x, T2&& y) 
		{  
			return pair< typename decay<T1>::type,  
						 typename decay<T2>::type >(std::forward<T1>(x),  
													std::forward<T2>(y));  
		} 

		ex. std::pair<std::string, int> p = make_pair("foo", 0);
		
	*/
}
/*
	usage - When dealing with template functions that take parameters of a template type, you often have universal parameters. Universal parameters are almost always references of one sort or another. They're also const-volatile qualified. As such, most type traits don't work on them as you'd expect:
*/
template<class T>
void func(T&& param) { // arg with universal parameters
	if (std::is_same<T, int>::value)
		std::cout << "param is an int\n";
	else
		std::cout << "param is not an int\n";
}
template<class T>
void func_d(T&& param) {
	if (std::is_same<typename std::decay<T>::type, int>::value)
		std::cout << "param is an int\n";
	else
		std::cout << "param is not an int\n";
}

void run_decay_2() {
	int three = 3;
	func(three);  //prints "param is not an int"!!!!
}

//int main()
//{
//	run_decay_2
//}
