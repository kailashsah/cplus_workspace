#include <iostream>
#include <vector>
using namespace std;

//.................................................

// dtor_sequence()
class researcher {
public:
	~researcher()
	{
		cout << "~researcher" << endl;
	}
};
class professor {
public:
	~professor() {
		cout << "~professor" << endl;
	}
};
class teacher : public professor {
public:
	~teacher()
	{
		cout << "~teacher" << endl;
	}
};
class myprofessor : public teacher, public virtual researcher {
public:
	~myprofessor() {
		cout << "~myprofessor" << endl;
	}
};
void dtor_sequence() {
	myprofessor prof;
	//~myprofessor
	//~teacher
	//~professor
	//~researcher
}
//.................................................

// run_virtual_call()
class Base {
public:
	virtual void method() {
		cout << "From base" << endl;
	}
	void basemethod() {
		method();
	}
	virtual ~Base() {
		method();
		cout << "~Base()" << endl;
	}

};

class A : public Base {
public:
	void method() {
		cout << "From A" << endl;
	}
	~A() {
		method();
		cout << "~A()" << endl;
	}
};
void run_virtual_call() {
	Base* b = new A();
	b->basemethod();
	delete b;
	// 1. - if base dtor is not virtual
	/*
	From A
	From base
	~Base()
	*/

	// 2.
	// if base dtor is virtual
	/*
		From A
		From A
		~A()
		From base
		~Base()
	*/
}
//.................................................
void run_string_literal_compare() {
	string somestring;
	if ("string_literal" == somestring) {
		// overloaded string operator
		cout << "equal" << endl;
	}
	else cout << "not equal" << endl;
}
//.................................................

int static_fn() {
	static int i = 1;
	return ++i;
	return i;
}
#include <format>
void run_static() {

	string str = format("{}, {}", static_fn(), static_fn()); // 3,2  if static int i=1;
	cout << str;
	//printf("%d, %d", static_fn(), static_fn()); // 2,1 if static int i;
	//printf("%d %d %d", printf("(1) "), printf("(2) "), printf("(3)  ")); //(3)  (2) (1) 4 4 5

}
//.................................................

void run_string() {
	string str("Hello");
	//char* c = str.c_str();// error C2440 : 'initializing' : cannot convert from 'const _Elem *' to 'char *'
	const char* c = str.c_str();
	int len = strlen(c);
}
//.................................................
class ABC {
public:
	void fn() {};
protected:
	ABC() {

	}
	ABC(const ABC& obj) {}

};
class BCD :public ABC {

};
void run_downcasting() {
	//ABC a;
	BCD b;
	BCD bc = b;
	bc.fn();

	// upcasting
	BCD* pb = new BCD;
	ABC* pa = pb;
	// downcasting
	//BCD* pbb = new ABC; // error
						//initializing': cannot convert from 'ABC * ' to 'BCD *'
						//'ABC::ABC': cannot access protected member declared in class 'ABC'
	//
	//BCD* pbb = dynamic_cast<BCD*> (new ABC); // error ABC is not a polymorphic type
}
//.................................................

class XYZ {

public:
	void f();
protected:
	XYZ() { cout << "xyz dtor ;" << endl; }
	XYZ(const XYZ&) {}
};

class XYZ_DERI : public XYZ {
public:
	~XYZ_DERI() { cout << "xyz-derived dtor" << endl; }
};

void run_restricted_class() {
	// 1. XYZ obj; // cannot access protected member declared in class 'xyz'
	// 2. XYZ_DERI obj;
		//xyz dtor;
		//xyz - derived dtor

}
//.................................................

class screen;

class screen_user {
public:
	//const screen scr; //'screen_user::scr' uses undefined class 'screen'
	//const screen* scr; // ok
	//const shared_ptr<screen> scr; // ok
	const shared_ptr<screen>* scr;  // ok
};
class display {
public:
	int i{};
};

void run_undefined_class() {

	//1. - error case
	//const shared_ptr<display>* scr = new display(); //cannot convert from 'display *' to 'const std::shared_ptr<display> *'

	//2. 
	const shared_ptr<display>* scr = new shared_ptr<display>(new display); // ok
	scr = new shared_ptr<display>(new display);
	scr->get()->i = 10;

	// 3.
	// shared_ptr<display>* scr = new shared_ptr<display>(new display()); // ok
	//scr->get()->i = 10;
	//cout << "inside obj value : " << scr->get()->i << endl;


	// - make_shared ok
	//const shared_ptr<display> scr1 = make_shared<display>(); // ok

	// - constant normal case
	//const shared_ptr<int> sptr = make_shared<int>(10); // ok
	//sptr = make_shared<int>(11); // binary '=': no operator found which takes a left-hand operand of type 'const std::shared_ptr<int>' (or there is no acceptable conversion)
	// with out const shared_ptr it would compile fine

	// - normal case
	//shared_ptr<int> sptr(new int{10}); // ok
	//sptr = new int{10}; // binary '=': no operator found which takes a right-hand operand of type 'int *' (or there is no acceptable conversion)
	//cout << "sptr<int> value " << *sptr.get() << *sptr; // 1010

}

//.................................................
class Excep {
public:
	void foo() throw (int, double)
	{}
};
class Excep_d : Excep
{
	//void foo() throw();		// ok
	//void foo() throw(int);	// ok
	void foo() throw(int, double, float); // ok
};
void run_exception() {

}
//.................................................

void HandleNoMemory();

void run_memory_except() {
	int* p = new int[100];
	if (!p)
	{
		//HandleNoMemory(); // error LNK2019: unresolved external symbol "void __cdecl HandleNoMemory(void)" (?HandleNoMemory@@YAXXZ) referenced in function "void __cdecl run_memory_except(void)" (?run_memory_except@@YAXXZ)
	}
	cout << "size of int[100]" << sizeof(p) << endl; // 4
}

//.................................................

class MyClass
{
public:
	MyClass();
	~MyClass();
	MyClass(int ii) :i(ii) {
		cout << "parameterized ctor " << endl;
	}
	MyClass(const MyClass& abc) {
		i = abc.i;
		cout << "copy ctor " << endl;
	}
	MyClass& operator=(const MyClass& abc) {
		i = abc.i;
		cout << "assignment " << endl;
		return *this;
	}

private:
	int i;
};

MyClass::MyClass() : i{ 0 }
{
	cout << "ctor " << endl;
}

MyClass::~MyClass()
{
	cout << "dtor " << endl;
}

void run_check_ctor_in_vec_elements() {
	vector<MyClass> vec(2);
	cout << " ------------ " << endl;
	vec.insert(vec.begin() + 1, MyClass());
	cout << " ------------ " << endl;
	/*
	ctor
	ctor
	----------
	ctor
	copy ctor
	copy ctor
	copy ctor
	dtor
	dtor
	dtor
	----------
	dtor
	dtor
	dtor*/
}

//.................................................
struct  Aassign {
	int i, j;
public:
	Aassign(int ii, int jj) : i(ii), j(jj) {
		cout << "ctor " << endl;

	}
	Aassign(const Aassign& a) {
		cout << "(" << a.i << "," << a.j << ")";
	}
	Aassign& operator=(const Aassign& a) {
		cout << "[" << a.i << "," << a.j << "]";
		return *this;
	}

};
void run_class_assignment() {
	Aassign x(1, 2);
	Aassign y(3, 4);
	Aassign z = (x = y); // [3,4](1,2)
}
//.................................................
//https://www.learncpp.com/cpp-tutorial/constructors-and-initialization-of-derived-classes/

class Vbase {
public:
	//Vbase(){ cout << " vbase ctor " << endl;}
	Vbase(int i) {}
};

class Vbase_d : public Vbase
{
public:
	Vbase_d(int ii) : Vbase{ ii } {
		//Vbase::Vbase(ii);
		cout << " vbase_d ctor " << endl;
	}
};

void run_virtual_inheritance() {
	Vbase_d obj{ 1 }; //'Vbase::Vbase': no appropriate default constructor available
}

//.................................................

class basexyz {
	int* i;
public:
	basexyz() :i(new int) {

	}
	~basexyz() {
		delete i;
		cout << "base dtor" << endl;
	}

};
class basexyz_d : public basexyz {
	int* j;
public:
	basexyz_d() : basexyz(), j(new int) {

	}
	~basexyz_d() {
		delete j;
		cout << "base_d dtor" << endl;
	}
};
void run_derived_issue() {

	basexyz* basep = new basexyz_d();
	delete basep;  // this is the case of memory leap,because there is no virtual class involved.
}

//.................................................
class baseabc {

};
class baseabc_d : public baseabc {

};

void run_exception_catch() {
	try {
		//throw new baseabc_d;
		baseabc_d obj_derived;
		throw obj_derived;
	}
	// 1.
	/*catch (...) {
		cout << " default exception" << endl;
	}
	*///'baseabc_d *': is caught by '...' on line 394
	//error C2311 : 'baseabc_d *' : is caught by '...' on line 394

	// 2.
	// whoever comes first exception will be caught there

	// for value
	catch (baseabc_d derived) {
		cout << " derived value exception" << endl;
	}
	catch (baseabc base) {
		cout << " base value exception" << endl;
	}

	// for pointer objects
	catch (baseabc_d* derived) {
		cout << " derived exception" << endl;
	}

	catch (baseabc* base) {
		cout << " base exception" << endl;
	}
	catch (...) {
		cout << " default exception" << endl;
	}
}
//.................................................
class Someclass {
public:
	void foo(int i) {
		cout << "foo() " << i << endl;

	}
};

void run_class_mem_fn_pointer() {

	// function pointer
	typedef void(Someclass::* fn)(int);
	// 1.
	fn fp = &(Someclass::foo);

	// 2.
	//fn fp = Someclass::foo; //Someclass::foo': non-standard syntax; use '&' to create a pointer to member

	Someclass* p = new Someclass;
	// 1.
	//(p->fp)(10); // error C2039: 'fp': is not a member of 'Someclass'

	// 2.
	//(p.*fp)(10); // ok -> Someclass p

	// 3.
	(p->*fp)(10); // ok
}
//.................................................
#include <iterator>
void run_iterator_base1() {
	vector<int> v;
	for (int i{}; i < 5; ++i) {
		v.push_back(i); // {0, 1, 2, 3, 4}

	}
	auto it = std::find(v.rbegin(), v.rend(), 2);
	// logically pointing to 2 but physically pointing to 3
	v.erase(it.base()); // 0,1,2,4  -> base() return physically pointing to an element

	//v.erase(find(v.rbegin(), v.rend(), 1).base()); // 2 will be erased

	v.insert(find(v.rbegin(), v.rend(), 1).base(), 10);
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); // 0,1,10,2,4
}

void run_iterator_base() {
	std::vector<int> v{ 0, 1, 2, 3, 4 };
	auto i = find(begin(v), end(v), 2);

	std::cout << *i << std::endl; // 2

	std::reverse_iterator<decltype(i)> ri(i);
	std::cout << *ri << std::endl; // 1

	std::cout << *ri.base() << std::endl; // 2

	std::cout << *(++ri) << std::endl; // 0

	std::cout << *ri.base() << std::endl; // 1
}
//.................................................
class classthrow {
public:
	classthrow() {

	}
	~classthrow() {
		throw 42;
	}
};

void run_excetion_1() {
	// prg terminates
	// two exception in the same context
	try {
		classthrow obj;
		throw 32;
	}
	catch (int a) {
		cout << "excep caught " << a << endl; // prg terminates
	}
}

//.................................................
template <class T, class X>
class Obj {
	T t_;
	X x_;
public:
	Obj(T t, X x) : t_(t), x_(x) {

	}
	operator T() const {
		return t_;
	}
};

void run_casting_operator() {
	int iT;
	Obj<int, float> obj(15, 10.3);
	iT = obj;
	cout << "casting op " << iT << endl;

}

//.................................................
// power of x
int power(int n, int& pow, int& calc) {
	if (pow > 0) {
		pow--;
		calc = calc * n;
		return power(n, pow, calc);
	}
	else
		return calc;
}
int power1() {
	//https://www.topcoder.com/thrive/articles/calculate-pow-x-n?utm_source=thrive&utm_campaign=thrive-feed&utm_medium=rss-feed#:~:text=Output%20Snippet-,Complexity%20Analysis,extra%20space%20has%20been%20used.
		//write fn in O(logn)

	return 0;
}
void run_power_x() {
	int calc = 1;
	int n = 2;
	int pow = 8;

	//int result = power(n, pow, calc);
	//cout << result << endl;

	cout << power(n, pow, calc) << endl;
}
//.................................................
class Assign {
public:
	int n;
public:
	//Assign& operator=(const Assign& obj);
	//const Assign& operator +(const Assign& obj) const;
	//const Assign& operator +(int m);
	Assign(int i) :n(i) {}
	Assign& operator=(const Assign& obj) {
		n = obj.n;
		return *this;
	}
	Assign& operator +(const Assign& obj) {
		n += obj.n;
		return *this;
	}
	const Assign& operator +(int m) {
		cout << "addition op with int" << endl;
		n += m;
		return *this;
	}
};

void run_class_mult_assignment() {
	Assign a(1), b(2), c(3);

	// 1.
	//a = a + 5 + c; //error C2678 : binary '+' : no operator found which takes a left - hand operand of type 'const Assign' (or there is no acceptable conversion)
	// if  const Assign& operator +(const Assign& obj)

		//a = a = b + c ; cout << "a = a = b + c " << a.n << endl; // 5
		//(c = a + a) = b + c; cout << "(c = a + a) = b + c " << c.n << endl; // 5
	 //a = b + 5;
	  //a =  5 + b; // binary '+': no global operator found which takes type 'Assign' (or there is no acceptable conversion)
	 //a = b + c + 5;
	 //a = c + 5;
}
//.................................................

class Foo {
public:
	virtual ~Foo() {}
};
class Bar : public Foo {
};
class Bar2 :public Foo {
};

class FooBar: public Bar{};
class FooBar2 :public Bar2 {  };

void run_virtual_porlymorphism() {
	// 1.
	//FoorBar2* fb = new Foo(); // cannot convert from 'Foo *' to 'FoorBar2 *'
	
	// 2.
	//FooBar2& fb2 = dynamic_cast<Foo&>(new FooBar2); // cannot use 'dynamic_cast' to convert from 'FoorBar2 *' to 'Foo &'  // see pointer & reference conversion is the issue
	//3.
	//FooBar2& fb2 = dynamic_cast<Foo&>(FooBar2());// cannot convert from 'Foo' to 'FooBar2 &'
	// 4.
	//Foo& fb2 = dynamic_cast<Foo&>(FooBar2()); // ok // upcasting also took by dynamic_cast
	// 5.
	//Foo& foo2 = new FooBar; //cannot convert from 'FooBar *' to 'Foo &'
	// 6.
	//Foo& foo = static_cast<Foo&>(FooBar2 f); // syntax error
	// 7.
	//Foo& foo = dynamic_cast<Foo&>(*(new FooBar2)); // ok
	//Foo& foo = (Foo&)(*(new FooBar2));// ok , bcoz upcasting
}
//.................................................
int x;
void function(int ) {

}
void run_function_assignment() {
	//function(3) = x; //left operand must be l - value
}
//.................................................

//.................................................

//.................................................
//.................................................

//.................................................
//to read
//https://www.geeksforgeeks.org/queue-using-stacks/
//.................................................

void run_main_natwest() {

	run_class_mult_assignment();
	//run_power_x();
	//run_casting_operator();
	//run_excetion_1();
	//run_iterator_base1();
	//run_iterator_base();
	//run_class_mem_fn_pointer();
	//run_exception_catch();
	//run_derived_issue();
	//run_virtual_inheritance();
	//run_class_assignment();
	//run_check_ctor_in_vec_elements();
	//run_memory_except();
	//run_exception();
	//run_undefined_class();
	//run_restricted_class();
	//run_downcasting();
	//run_static();
	//run_string_literal_compare();
	//run_virtual_call();
	//dtor_sequence();
}

//int main()
//{
//	run_main_natwest();
//	//return 0;
//}
