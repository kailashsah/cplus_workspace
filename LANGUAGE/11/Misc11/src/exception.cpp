#include <iostream>
using namespace std;

class Base {};
class Derived : public Base {
public:
	~Derived()
	{
		//delete this;
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


	getchar();
}

//int main()
//{
//	run_exception();
//	return 0;	
//}
