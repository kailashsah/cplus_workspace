#include <iostream>
using namespace std;

/*
	use of template class inside template
*/
template<class A1>
class B
{
public:
	A1* a;
	int GetInt() { return a->dummy; }
};

template<template <class> class B>
class A
{
public:
	A() : dummy(3) { b.a = this; }
	B<A> b;
	int dummy;
};

class AInstance : public A<B> //happy
{
public:
	void Print() { std::cout << b.GetInt(); }
};

void run_tmpl_tmpl()
{
	std::cout << "hello";
	
	AInstance test;
	test.Print();
}

//int main()
//{
//	run_tmpl_tmpl();
//	return 0;	
//}
