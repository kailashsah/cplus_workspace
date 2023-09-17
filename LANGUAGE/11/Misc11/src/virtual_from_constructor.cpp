#include <iostream>
using namespace std;

/*
	A Indeed, C# behaves differently from C++ in this respect. In C++, if you call a virtual function from a constructor or destructor, the compiler calls the instance of the virtual function defined for the class being constructed (for example, Base::SomeVirtFn if called from Base::Base), not the most derived instance. As you say, this is because the vtable is not fully initialized until the most derived constructor executes. Another way to think of it is that the derived class is not created yet.
	2. but for different reasons—it's considered bad practice to call a virtual function from a constructor or destructor.
*/
class BaseTest {
public:
	BaseTest()
	{
		printf(" Base::ctor\n");
		Hello();
	}
	~BaseTest()
	{
		printf(" Base::dtor\n");
		Goodbye();
	}
	virtual void Hello() { printf(" Base::Hello\n"); }
	virtual void Goodbye() { printf(" Base::Goodbye\n"); }
};

// Derived native C++ class overrides fn, but not called from ctor.
class DerivedTest : public BaseTest {
public:
	DerivedTest()
	{
		printf(" Derived::ctor\n");
	}
	~DerivedTest()
	{
		printf(" Derived::dtor\n");
	}
	virtual void Hello() { printf(" Derived::Hello\n"); }
	virtual void Goodbye() { printf(" Derived::Goodbye\n"); }
};

void run_virtual_from_destructor()
{
	printf("Create native object:\n");
	DerivedTest* pd = new DerivedTest();
	printf("Destroy native object:\n");
	delete pd;
}

//int main()
//{
//  run_virtual_from_destructor();
//	return 0;	
//}

/*
 output
	 Create native object:
	 Base::ctor
	 Base::Hello
	 Derived::ctor
	Destroy native object:
	 Derived::dtor
	 Base::dtor
	 Base::Goodbye
*/
