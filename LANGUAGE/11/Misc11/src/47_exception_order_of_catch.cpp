#include <iostream>
using namespace std;

class Base {};
class Derived : public Base {
public:
	~Derived()
	{
		//delete this;
		/*
			if we delete inside dtor -
				unhandled exception - stack overflow
		*/
	}
};

void run_exception()
{
	Derived d;

	try {

		throw d;
	}


	catch (Derived& ) {
		cout << "Caught Derived Exception";
	}
	catch (Base& ) {
		cout << "Caught Base Exception";
	}
	//getchar();

	/*
		output -
		Caught Derived Exception
	*/
}

//int main()
//{
//	run_exception();
//	return 0;	
//}
