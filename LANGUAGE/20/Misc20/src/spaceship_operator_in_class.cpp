#include <iostream>
using namespace std;

/*
	1. default , delete - It means that you want to use the compiler-generated version of that function, so you don't need to specify a body.
        You can also use = delete to specify that you don't want the compiler to generate that function automatically.
    
    2. struct compare_three_way;
*/

struct Point {
    int x;
    int y;
    auto operator<=>(const Point& other) const {
        if (auto cmp = x <=> other.x; cmp != 0)
            return cmp;
        return y <=> other.y;
    }
    bool operator==(const Point& other) const = default;
};

void run_class_with_spaceship_op() {
    Point pt1{ 1, 1 }, pt2{ 1, 2 };
    //Point pt1{ 1, 1 }, pt2{ 1, 1 };
    
    //1.
    if(pt1 < pt2)
        std::cout <<"pt1 is less than pt2 "<< std::endl;
    else if (pt1 == pt2)
        std::cout << "pt1 is equal to pt2 " << std::endl; // not calling operator <=>, calls operator==()
    else if (pt1 > pt2)
        std::cout << "pt1 is grater than pt2 " << std::endl;

    /*
        1. if below is given
            auto operator<=>(const Point&)const = default;
        then all the operators ==, <,>,<=,>= comes free

        2. auto operator<=>(const Point& other) const {...} if defined explicitly
            bool operator==(const Point& other) this op has not got defaulted by self, so we have to mention. 
            2.1 if operator==() not defined, no compilation error
                 2.1.1  but stmt else if (pt1 == pt2) -> gives the compilation error for operator==()
    */

    //2.
    strong_ordering value =  std::compare_three_way{}(pt1, pt2);
    if (value < 0)
        std::cout << "pt1 is less than pt2 " << std::endl;
    else if (value == 0)
        std::cout << "pt1 is equal to pt2 " << std::endl; 
    else if (value > 0)
        std::cout << "pt1 is grater than pt2 " << std::endl;
    /*
        1. if not defined -> //bool operator==(const Point& other) const = default;        
        'std::compare_three_way::operator ()': the associated constraints are not satisfied
        
        2. struct compare_three_way; Function object for performing comparisons. Deduces the parameter types and the return type of the function call operator.
    */
}

void run_partial_ordering() {

    constexpr double m{ 1.1 };
    const double n{ sqrt(-1) }; // n is NaN
    const auto res{ m <=> n };

    if (res == std::partial_ordering::unordered) {
        std::cout << m << " <=> " << n << " is unordered" << std::endl;
    }
    /*
        std::partial_ordering::less
        std::partial_ordering::greater
        std::partial_ordering::equal
        std::partial_ordering::unordered
    */
}

//int main()
//{
//    run_class_with_spaceship_op();
//    run_partial_ordering();
//    return 1;
//}