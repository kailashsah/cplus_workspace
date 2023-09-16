#include <type_traits>
#include <iostream>

using namespace std;
/*
	enable_if (C++11)
conditionally removes a function overload or template specialization from overload resolution
*/

namespace is_pointer_src {
	class MyClass
	{
	};

	template <typename Object>
	class Listt
	{
	public:

		// function template below
		template<class T = Object>
		void insert(T t, typename std::enable_if< std::is_pointer<T>::value >::type* = 0)
		{
			std::cout << "insert pointer" << std::endl;
		}

		template<class T = Object>
		void insert(T t, typename std::enable_if< !std::is_pointer<T>::value >::type* = 0)
		{
			std::cout << "insert non-pointer" << std::endl;
		}

	}; // end of class List

	template <class T>
	class odd {
	public:
		//ver 1: the return type(bool) is only valid if Q is an integral type
		template <class Q = T>
		typename std::enable_if<std::is_integral<Q>::value, bool>::type	is_odd(Q i)
		{
			return bool(i % 2);
		}

		//ver2 : the return type(int) is only valid if Q  is an string type
		template <class Q = T>
		typename std::enable_if<std::is_same<Q, string >::value, int>::type is_odd(Q i)
		{
			//return "a"; // return': cannot convert from 'const char [2]' to 'int'
			return false;
		}


	};

	void run_class_list()
	{
		//1.
		MyClass a;
		Listt<MyClass> lst;
		Listt<MyClass*> plst;

		lst.insert(a); // this will call different version of insert based on object/pointer as arg
		plst.insert(new MyClass());
		cout << "<end>";

		//2.
		odd<string> find_odd;

		cout << endl << "find_odd.is_odd((string)\"a\")  : ";
		bool ret = find_odd.is_odd((string)"a"); // calls ver 2
		cout << ret;

	}
	void run()
	{
		run_class_list();
	}


}
//int main()
//{
//	is_pointer_src::run();
//	return 0;
//}

/*
	output-
		insert non-pointer
		insert pointer
		<end>
*/