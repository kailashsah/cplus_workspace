#include <iostream>
using namespace std;
/*
	
*/

// concepts writing in function

// C++11/14, SFINAE
//https://www.kdab.com/cpp23-will-be-really-awesome/ 

//1.
template <typename T>
std::enable_if_t<std::is_same_v<T, int>> f(T x);

// 2. C++20: concepts
void f1(std::same_as<int> auto x);

