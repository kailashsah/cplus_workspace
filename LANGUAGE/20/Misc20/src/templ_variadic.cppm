import <iostream>;
using namespace std;

///////////////////////////////////// // example 1.

// variadic template
import <numeric>;
template<typename Type, typename... Types>
auto sum(Type first, Types... args) -> decltype(first)
{
	auto values = { first, args... };	// fold expression
	cout << typeid(values).name();		// class std::initializer_list<int>
	return std::accumulate(values.begin(), values.end(), Type{ 0 }); // include numeric header
}
void run_variadic()
{
	cout << sum(1, 3, 5); // 9
}


///////////////////////////////////// // example 2.
import <vector>;
import <algorithm>;
template<typename T, typename... Args>
void push_back_vec(std::vector<T>& v, Args&&... args)
{
	// folding over comma - https://riptutorial.com/cplusplus/example/14773/folding-over-a-comma
	(v.push_back(args), ...); // fold expression forward<Args>(args)
	
}
 
void run_fold_expression()
{
	int a = 4;
	//int& i = a;
	int&& i = 5;
	vector<int> vec;
	push_back_vec(vec, 1, 2, 3, i);
	for_each(vec.begin(), vec.end(), [](auto& a) { cout << a << " "; });
}

//int main()
//{
//	//run_variadic();
//	//run_fold_expression();
//
//	return 0;
//}

