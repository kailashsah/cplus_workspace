#include <iostream>
using namespace std;

class Base {};
class Derived : public Base {
public:
	~Derived()
	{
		//delete this;
		/*
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


	catch (Derived& d) {
		cout << "Caught Derived Exception";
	}
	catch (Base& b) {
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
