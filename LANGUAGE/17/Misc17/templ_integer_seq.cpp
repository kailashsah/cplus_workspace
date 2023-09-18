#include <iostream>
using namespace std;


// problem statement, gives error, check run
template<typename... ElementTypes>
auto sum(const std::tuple<ElementTypes...>& tup)
{
	return (std::get<ElementTypes>(tup) + ...); // fold expression
}

// integer_sequence while using position to access tuple
template <typename... ElementTypes, int ... Indices>

auto sum_(const std::tuple<ElementTypes ... >& tup, std::integer_sequence<int, Indices...> seq) // dummy param
{
	return (get<Indices>(tup) + ...);
}


void run_integer_seq()
{
	tuple tup{ 1, 3.5, 2 };
	cout << sum(tup); // becoz of 1 --  error C2338: duplicate type T in get<T>(tuple)

	constexpr auto size = std::tuple_size_v<decltype(tup)>;
	auto indices = std::make_integer_sequence<int, size>{};
	cout << sum_(tup, indices);
}

//int  main()
//{   
//	run_integer_seq();
//
//	return 0;
//}
