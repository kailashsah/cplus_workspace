#include <iostream>
#include <vector>


// template as template argument
using namespace std;
template<typename Type, typename... Types>
auto build_vector(Type first, Types... args)
{
	std::vector<Type> v{ first, args... };
	return v;
}

template < template<typename> class container_type,
	typename Type,
	typename... Types>
	auto build_vector_advanced(Type&& first, Types&&... args)
{
	container_type<Type> v{ first, args... };
	return v;

}

// this one also compiled without first type & type template parameter (good to know)
template < template<typename> class container_type,	
	typename... Types>
	auto build_vector_advanced1(Types&&... args)
{
	container_type<int> v{  args... };
	return v;

}

#include <deque>
void run_templ_temp()
{
	auto v = build_vector<int>(1, 5, 3, 6);
	auto v_container = build_vector_advanced<std::deque>(1, 3, 2, 4);
	for (auto i : v)
		cout << i << " ";
	cout << endl;

}

//int main()
//{
//	run_templ_temp();
//	return 0;
//}