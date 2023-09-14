#include <iostream>
#include <string>
#include<iomanip> // setw()
//import <iostream>;
using namespace std;

const int width_space = 50;
/*
setw C++ is a method of iomaip library present in C++. setw function is a C++ manipulator which stands for set width.
*/
//....................................
void run_placment_new_constructor()
{
	cout << setw(width_space) << "run_placment_new_constructor() " << endl<< endl;
	unsigned char buf[sizeof(int) * 4];

	int* pInt = new (buf) int(1);
	int* nInt = new (buf + sizeof(int)) int(2);

	int* pbuf = (int*)(buf + 0);
	int* nbuf = (int*)(buf + sizeof(int));

	cout << pInt << setw(14) << pbuf << endl; // 1.
	cout << nInt << setw(14) << nbuf << endl; // 2.
	/*
	                   run_placment_new_constructor()
		0094FB2C      0094FB2C // 1.
		0094FB30      0094FB30 // 2.
	*/
}

//....................................
int operator "" _int(const char* str, std::size_t ss) {
	return std::stoi(str);
}
void run_literal()
{
	cout << setw(width_space) << "run_literal() " << endl << endl;

	int a = "123"_int;
	cout << a << endl;
}


//....................................
/// returns a callable object with two int parameters
//template <typename ... Args>
//auto f2(Args&& ... args) {
//
//	//return capture_call([](int param1, int param2, auto&& ... args) {
//		return ([](Args&& ... args) {
//		// args are perfect captured here
//		//std::cout << param1 << param2;
//			cout << 2;
//		(std::cout << ... args) << '\n';}	
//		, 
//		std::forward<Args>(args) ...);
//}

template<typename T, int s>
auto f3(T a, T b)
{
	//int c = 0;
	//return (static_assert(s = 3, " ")), b;
	return a, b, 10;
}
void run_templates() {
	cout << setw(width_space) << "run_templates() " << endl << endl;

	static int s = 0;	
	//static_assert(s == 3); // todo

	cout << f3<int, 2>(4 , 8 ); // it print the right most in the return stmt -> return a, b, 10;
	//cout << f2(4, 8); // todo
	// 
}

//....................................
class check_static_parent {

public: 
	virtual void add() {}
};

class check_static : public check_static_parent {
public:
	void add()
	{
		check_static_parent::add(); // calling base version
		cout << "add()";
	}
};

void run_main() {
	
	//check_static::add();
	run_literal();
	run_placment_new_constructor();
	run_templates();
}

int main()
{
	run_main();
	
	return 0;
}


