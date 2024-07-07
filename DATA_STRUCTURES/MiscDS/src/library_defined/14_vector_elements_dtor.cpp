#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
/*
	1.

*/

//......................................... class inside vector

class CPersonA {
public:
	char ch;
	CPersonA(char arg) :ch(arg) {}
	virtual ~CPersonA() {
		cout << "dtor for " << ch << endl;
	}
};


void run_vector_dtor()
{
	vector<CPersonA> vec;
	vec.emplace_back('a');
	vec.emplace_back('b');
	vec.emplace_back('c');
	/*
		dtor called for CPersonA
		dtor a

		dtor a
		dtor b

		dtor a  --> in third insert it puts all the 3 elem. so 3 dtor called
		dtor b
		dtor c

		this might be vector is expanding and creating new mem allocaton on each emplace
	*/
}
//......................................... vector inside class

class CPersonB {
public:
	char ch;
	vector<CPersonA> vec;
	CPersonB(char arg) :ch(arg) {}
	virtual ~CPersonB() {
		cout << "dtor  CPersonB for " << ch << endl;
	}
};

void run_vector_inside_class() {
	CPersonB b('A');
	b.vec.emplace_back('1');
	b.vec.emplace_back('2');
	/*
		dtor for 1  //--> vec

		dtor  CPersonB for A
		dtor for 1	//--> vec
		dtor for 2	//--> vec

		clear off members inside the vecotr
	*/
}
//......................................... vector with unique_ptr

class CPersonC {
public:
	char ch;
	vector<unique_ptr<CPersonA>> vec;
	CPersonC(char arg) :ch(arg) {}
	virtual ~CPersonC() {
		cout << "dtor  CPersonC " << ch << endl;
	}
};

void run_vector_with_unique_ptr() {
	CPersonC b('A');
	b.vec.emplace_back(make_unique<CPersonA>('1'));
	b.vec.emplace_back(make_unique < CPersonA>('2'));
	/*
		dtor  CPersonC A
		dtor 1
		dtor 2

	*/
}
unique_ptr<CPersonA> fun() {
	auto a = make_unique<CPersonA>('3');
	// std::unique_ptr<CPersonA, std::default_delete<CPersonA> > a = std::make_unique<CPersonA>('3') 
	// /* NRVO variable */;

	return a;
}

void run_vector_with_unique_ptr_auto() {
	//3.
	auto c = fun();
	//auto d = c; // error deleted function

	unique_ptr<CPersonA> ptr;
	//ptr = c; // error op = deleted function

	CPersonC b('A');
	//1.
	//auto a = make_unique<CPersonA>('1');
	//b.vec.emplace_back(a);// error - calling copy constuctor of unique_ptr<>, its a deleted function.

	//2.
	b.vec.emplace_back(make_unique < CPersonA>('2'));


	/*
		dtor  CPersonC A
		dtor 1			CPersonA
		dtor 2			CPersonA

	*/
}
//......................................... main


//int main()
//{
//	//run_vector_dtor();
//	//run_vector_inside_class();
//	//run_vector_with_unique_ptr();	
//	//run_vector_with_unique_ptr_auto();
//	return 0;
//}
