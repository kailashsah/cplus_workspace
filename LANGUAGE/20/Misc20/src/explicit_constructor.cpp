#include <iostream>
using namespace std;

/*
	1. explicit(bool), ctor made explicit at compile time
	2. explicit constructor - https://leimao.github.io/blog/CPP-Explicit-Constructor/
*/

struct foo {

	template<typename T>
	//explicit(true)	foo(T) {}
	explicit(!is_integral_v<T>)	foo(T arg) {
		cout << "ctor called : "<< arg << endl;
	}
};

void run_explicit_bool()
{
	//By explicit call, constructor becomes explicit for non-integral types, for all integral it behaves implicit, check template generations  
	//1.
	foo a{ 123 };
	foo b = 123; // ok // // explicit specifier evaluates to false, so it works as implicit   (IMP)

	//2.
	//foo b = "123"; // explicit specifier evaluates to true //error C2440: 'initializing': cannot convert from 'const char [4]' to 'foo'
	
	
	//3.
	foo c{ "123" }; // implicit call
	
	//4.
	foo d = 'a';    // explicit success // explicit specifier evaluates to false
	
	//5.
	foo e{ 5.5 }; // direct call // implicit call
}

//int main()
//{
//	run_explicit_bool();
//	return 1;
//}

/*
struct foo
{
		  template<typename T>
		  inline explicit(!is_integral_v<T>) foo(T arg)
		  {
			operator<<(operator<<(std::operator<<(std::cout, "ctor called : "), arg), endl);
		  }
  
  
		//   First instantiated from: insights.cpp:21 
		template<>
		inline explicit(false) foo<int>(int arg)
		{
			std::operator<<(std::cout, "ctor called : ").operator<<(arg).operator<<(std::endl);
		}
		#endif



		// First instantiated from: insights.cpp:27 
		template<>
		inline explicit(true) foo<const char*>(const char* arg)
		{
			std::operator<<(std::operator<<(std::cout, "ctor called : "), arg).operator<<(std::endl);
		}
		#endif



		// First instantiated from: insights.cpp:30 
		template<>
		inline explicit(false) foo<char>(char arg)
		{
			std::operator<<(std::operator<<(std::cout, "ctor called : "), arg).operator<<(std::endl);
		}
		#endif



		// First instantiated from: insights.cpp:33 
		template<>
		inline explicit(true) foo<double>(double arg)
		{
			std::operator<<(std::cout, "ctor called : ").operator<<(arg).operator<<(std::endl);
		}
		#endif


};

*/