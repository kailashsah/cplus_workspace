#include <iostream>
#include "cplus20.h" //#define cplus20


using namespace std;
#ifdef cplus20


///////////////////////////////////// // to_array 

#include <array> // to_array
#include <algorithm> // for_each

void run_to_array() // to_array 
{
	int a[] = { 1,3,2 };
	std::array b = std::to_array(a);
	for_each(begin(b), end(b), [=](auto a) {cout << a << " "; });
	//
	cout << endl;
	array c = to_array<double>({ 4,5,6 });
	cout << typeid(c).name() << endl;		//class std::array<double, 3>
	for_each(begin(c), end(c), [=](auto a) {cout << a << " "; });

	cout << endl;
	array d = to_array("abc");
	cout << typeid(d).name();			// class std::array<char,4>
	for_each(begin(d), end(d), [=](auto a) {cout << a << " "; });
}



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

///////////////////////////////////// // concepts


//template <typename T>
//concept canAddtoInt = requires (T t) {
//	//{t + 1} -> same_as<T>;
//};


template <typename T>
concept canAddtoInt = requires  {	
	typename enable_if < is_integral<T>::value, T>::type ;
};

template <typename T>
T func_add(T&& t) requires canAddtoInt<T>
{
	return t + 2;
}

void run_func_add()
{
	//cout << func_add(4.5) << endl; // no instance of function templ matches the argument list
	cout << func_add(4) << endl; // 6
}

///////////////////////////////////// // concepts writing in function

// concepts writing in function

// C++11/14, SFINAE
//https://www.kdab.com/cpp23-will-be-really-awesome/ 

template <typename T>
std::enable_if_t<std::is_same_v<T, int>> f(T x);

// C++20: concepts
void f1(std::same_as<int> auto x);


/////////////////////////////////////

//int main()
//{
//	//run_func_add();
//	
//	//run_concept();
//	
//	 
//	//run_to_array();
//	
//	return 1;
//}


#endif // cplus20