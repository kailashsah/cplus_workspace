#include <iostream>
using namespace std;


///////////////////////////////////// // concepts

 // concepts  (moveconstructible)

class widget {
public :
	int i;
	widget();
	//widget(widget&&)  = delete; // move ctor
	//widget(const widget&) = delete;    // copy

	//widget& operator=(widget&) = delete; // std::movable return false if == not there

	
};
widget::widget() 
{
	cout << "ctor called" << endl;
} 

#include <vector>

template<typename T>
concept Fooconcept = true;  // always satsify

// https://en.cppreference.com/w/cpp/language/requires 
// https://en.cppreference.com/w/cpp/language/constraints
// 
//1.
//template<typename T>
//concept moveConstructible = requires {
//	typename std::enable_if_t< std::is_move_constructible_v<T> >;
//	//typename std::enable_if<std::is_move_constructible_v<T>, T>::type;
//};	

//2.
//template<typename T>
//concept moveConstructible = std::is_move_constructible_v<T>;

//3.
template<typename T>
concept moveConstructible = requires (T t) { T(std::move(t)); };

//template<moveConstructible T> // 1.
template<class T> 
void foo(T&& arg) requires moveConstructible<T> // 2.
//void foo(T&& arg) requires movable<T>  // 3.
{
	vector<T> vec;
	//vec.emplace(forward<T>(args));
	//T t = move(arg);
	cout << arg.i;
	cout << typeid(arg).name() << " " <<  typeid(T).name();;
	cout << "called";
}
void run_concept()
{
	
	foo(widget{});
	//widget a = std::move( widget{});
}


//int main()
//{
//	//run_func_add();
//	
//	//run_concept();
//	
//	return 1;
//}


