#include <type_traits>
#include <iostream>

using namespace std;
namespace is_pointer_src {
	class MyClass
	{
	};

	template <typename Object>
	class List
	{
	public:

		template<class T = Object>
		void insert(T t, typename std::enable_if<std::is_pointer<T>::value >::type* = 0)
		{
			std::cout << "insert pointer" << std::endl;
		}

		template<class T = Object>
		void insert(T t, typename std::enable_if<!std::is_pointer<T>::value >::type* = 0)
		{
			std::cout << "insert non-pointer" << std::endl;
		}
		/*MyClass a;

		List<MyClass> lst;
		List<MyClass*> plst;

		lst.insert(a);
		plst.insert(new MyClass());
		cout << "<end>";*/

	}; // end of class List

	template <class T>
	class odd {
	public:
		template <class Q = T>
		typename std::enable_if<std::is_integral<Q>::value, bool>::type	is_odd(Q i)
		{
			return bool(i % 2);
		}

		template <class Q = T>
		typename std::enable_if<std::is_same<Q, string >::value, int>::type is_odd(Q i)
		{
			return false;
		}

		/*odd<string> find_odd;
		bool ret = find_odd.is_odd((string)"a");*/
	};
	void run_class_list()
	{
		MyClass a;
		List<MyClass> lst;
		List<MyClass*> plst;

		lst.insert(a); // this will call different version of insert based on object/pointer as arg
		plst.insert(new MyClass());
		cout << "<end>";

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