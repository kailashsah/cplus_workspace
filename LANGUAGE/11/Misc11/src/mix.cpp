#include <iostream>
//import <iostream>;
	
using namespace std;

#include <iomanip>

#include <memory> // for std::shared_ptr
#include <string>

class Person
{
	std::string m_name;
	std::shared_ptr<Person> m_partner; // initially created empty

public:
	Person() {}
	Person(const std::string& name) : m_name(name)
	{
		std::cout << m_name << " created\n";
	}
	~Person()
	{
		std::cout << m_name << " destroyed\n";
	}

	friend bool partnerUp(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2)
	{
		if (!p1 || !p2)
			return false;

		cout << p1.use_count() << endl;
		//p1->m_partner = p2;


		//auto ricky{ std::make_shared<Person>("Ricky1") };
		//p1->m_partner = ricky ;
		//p2->m_partner = p1;

		std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

		return true;
	}
	ostream& print(ostream& os) const
	{
		os << "printing person" << endl;
		return os;
	}
};
 ostream& operator<<(ostream& os, const Person& per) {
	return per.print(os);
	
}
 inline Person& GetPerson()
 {
	 // check single instance
	 static Person per;
	 return per;
 }

int run_cyclic_dependecy()
{
	auto lucy{ std::make_shared<Person>("Lucy") }; // create a Person named "Lucy"
	
	auto ricky{ std::make_shared<Person>("Ricky") }; // create a Person named "Ricky"

	partnerUp(lucy, ricky); // Make "Lucy" point to "Ricky" and vice-versa

	cout << Person("aa");
	Person&& s = std::move(GetPerson());
	cout << &s << endl;
	Person&& s1 = std::move(GetPerson());
	cout << &s1 << endl;

	return 0;
}

void run_mix()
{
	unsigned char buf[sizeof(int) * 4];

	int* pInt = new (buf) int(1);
	int* nInt = new (buf + sizeof(int)) int(2);

	int* pbuf = (int*)(buf + 0);
	int* nbuf = (int*)(buf + sizeof(int));

	cout << pInt << " " << pbuf << endl;
	cout << nInt << setw(14) << nbuf << endl;
}
#include <vector>
#include <algorithm>
void run_vector()
{
	vector<int> vec;
	cout << vec.max_size() << endl;
	vector <Person> v_per;
	cout << sizeof(Person) << endl;
	cout << v_per.max_size() << endl;

	// swap in vectors
	vector<int> n{ 1,2,3 };
	vector<int> p;
	cout << "n size: " << n.size() << endl;
	n.swap(p);
	cout << n.size() << endl;
	cout << p.size() << endl;
	for_each(p.begin(), p.end(), [](const int i){ cout << i; });
}



//auto test(const auto & v) {
//	auto a1 = decltype(v){2}; // what is a1's qualified TYPE?
//	string ss(typeid(a1).name());
//	cout << ss << endl;
//	//cout<< type_name<decltype(a1)>();
//	decltype(v) a2{ 2 }; // what is a2's qualified TYPE?
//	cout << typeid(a2).raw_name() << endl;
//	a1++; // is this legal? Why
//	//a2++; // is this legal? Why
//	return a1 + a2;
//}
void run_decltype()
{
		/*int x = 6;
		auto c = test(x);
		return ;*/
}


//template<class A1>
//class B
//{
//public:
//	A1* a;
//	int GetInt() { return a->dummy; }
//};
//
//template<template <class> class B>
//class A
//{
//public:
//	A() : dummy(3) { b.a = this; }
//	B<A> b;
//	int dummy;
//};

//class AInstance : public A<B> //happy
//{
//public:
//	void Print() { std::cout << b.GetInt(); }
//};

void run_tmpl_tmpl()
{
	std::cout << "hello";
	/*AInstance test;
	test.Print();*/
}
#include <forward_list>
void run_forward_list()
{
	forward_list<int> fl;
	int a = 0;
	puts("aaaa");
	puts("bbb");
}

///////////////////////////////////////////
int operator "" _int(const char* str, std::size_t ss) {
		return std::stoi(str);
	}
void run_literal()
{
	int a = "123"_int;
	cout << a  << endl;
}

///////////////////////////////////////////
struct S {
	S() : id{ count++ } {}
	~S() { count--; }
	int id;
	static inline int count{ 0 }; // declare and initialize count to 0 within the class
};

///////////////////////////////////////////
template<typename T>
using Vec = vector<T>;

using ss = string;
void run_type_alias()
{
	Vec<int> v{2,1,4,5};
	ss s= "hi";
	cout << s;

}
///////////////////////////////////////////
constexpr int addOne(int n) {
	return [n]{ return n + 1; }();
}


void run_version()
{
	if (__cplusplus == 201703L) std::cout << "C++17\n";
	else if (__cplusplus == 201402L) std::cout << "C++14\n";
	else if (__cplusplus == 201103L) std::cout << "C++11\n";
	else if (__cplusplus == 199711L) std::cout << "C++98\n";
	else std::cout << "pre-standard C++\n";

}
class Parent {

public:
	virtual void foo(){
		cout << "Parent version" << endl;
	}
};

class Child : public Parent{
public:
	void foo() override {
		cout << "Child version" << endl;
	}
};

void run_int_float_ptr()
{
	// int ptr & float ptr
	int* pint = new int{ 5 };
	float* pFloat = new float{6};
	cout << *pint << endl;
	//pint = (int*)pFloat; // garbage value
	//pint = static_cast<int*>(pFloat); // compile err // strong type checking

	pint = reinterpret_cast<int*>(pFloat); cout << *pint << endl; // garbage value
	int newint = static_cast<int>(*pFloat); cout << "newint " << newint << endl; // 6
	int& int_ref = reinterpret_cast<int&>(*pFloat); cout << "int_ref " << int_ref << endl; //  garbage value 
	cout << pFloat;// print address 00DCE570
	int int_bit = std::bit_cast<int>(pFloat); cout << "int_bit " << int_bit << endl;
	
	// static cast
	int i = 8;
	float f = 5.5;
	int ii = static_cast<int>(f);
	float ff = static_cast<float>(i);
	//cout << ii; // 5
	cout << ff;

}
void run_virtual()
{
	//Parent* pPar = nullptr;
	Parent* pPar = new Parent;
	Child* pChild = new Child;

	// child -> parent
	//pPar = pChild;
	//pPar = (Parent*) pChild;
	//pPar = dynamic_cast<Parent*> (pChild);
	//pPar->foo();

	// parent -> child
	//pChild = pPar; // cnnot convert, compile err 
	pChild = (Child*)pPar;
	pChild->foo();
}


class Int {
	int x;

public:
	Int()
	{
		cout << "ctor default " << endl;
	}
	Int(int x_in = 0)
		//: x{ x_in }
		: x(x_in)
	{
		cout << "Conversion Ctor called" << endl;
	}
	Int& operator=(const Int&) {
		cout << " assignment called " << endl;
		return *this;
	}
	operator string()
	{
		cout << "Conversion Operator" << endl;
		return to_string(x);
	}
	~Int()
	{
		cout << "dtor called " << endl;
	}
};

void  run_static_cast()
{
	Int obj(3);
	string str = obj;
	cout << " obj assignment" << endl;
	obj = 20.3;
	//string str2 = static_cast<string>(obj);
	//obj = static_cast<Int>(30);
	
}

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



///////////////////////////////////////////
class check_static_parent {

public: virtual void add() {}
};
class check_static : public check_static_parent {
public:
	void add()
	{
		check_static_parent::add(); // calling base version
		cout << "add()";
	}
};
#include <array>
#include <iterator>
#include <algorithm>
void check_vector()
{
	vector<int> vec(100);
	std::fill_n(vec.begin(), vec.end() - vec.begin(), 1200);
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));

}
#include <execution>
void check_array()
{
	const int n = 5;
	 int val = 1;

	int arr1[n];
	
	std::fill_n(begin(arr1), n, val);
	copy(begin(arr1), end(arr1), ostream_iterator<int>(cout, " "));


	array<int, 100> arr;
	//fill_n(arr, 100 , 1);
	//array<int, 100> arr;
	//array<int, 100> arr{};
	//for_each(begin(arr), end(arr), ostream_iterator<int>(cout, " ")); // it needs a func
	//for_each(begin(arr), end(arr), [](int x) {cout << x; }); // ok
}

class A
{
	int i;
	int y;
public:
	A() { cout <<  "default ctor"; };
	A(int i) {
		cout << "ctor 1 param" << endl; 
	}
	A(int i , int y) : i{ i }{ cout << "ctor 2 param" << endl; }
	A(const A&) { cout << "copy" << endl;  }
	A(A&&){ cout << "move" << endl; }
	A& operator=(A&&) { cout << "m assign" << endl; return *this; }
	A& operator=(const A&) { cout << "assign" << endl; }
	//A(initializer_list<int>) { cout << "ini list " << endl; }

};
void check_aggregate_init()
{
	//A a = A(1,2);// ctor 2 param
	//A b = a; // copy
	//b = a; // assignment


	//A a = A( 1, 2 );// ctor 2 param
	//A a = { 1, 2 }; // ctor 2 param, if ini list not present
	//A a = A{ 1, 2 }; // ctor 2 param , if ini list not present
	//A a{ 1, 2 }; // ctor 2 param, if no ini list
	//A a{ 1, 2, 3 }; // ini list
	//A a = A{ 1 }; // ctor 1 param
	
	//A a { 1 }; // ctor 1 param
	//A a(1); // ok 

	//A a; // default 
	//a = A{ 1 }; // ctor 1 param -> m assign
	//a = A(1); // same
}
///////////////////////////////////////////
void run_main() {

	//check_aggregate_init();
	//check_array();
	check_vector();

	//check_static::add();
	

	//int s = 0;	static_assert(s == 3);
	
	//cout << f3<int, 2>(4 , 8 );
	//cout << f2(4, 8);
	// 
	//run_virtual_cxpr();
	//run_static_cast();
	//run_int_float_ptr();
	//run_virtual();

	//run_version();



	//static_assert(addOne(1) == 2);
	//run_variadic();
	//run_type_alias();

	//run_literal();

	//ref_check::run_ref_check();

	//run_forward_list();

	//run_tmpl_tmpl();

	//run_decltype();
	//run_singleton();
	//run_vector();
	//run_cyclic_dependecy();
	//run_mix();
}

//int main()
//{
//	run_main();
//	
//	return 0;
//}


