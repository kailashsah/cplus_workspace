#include <iostream>
using namespace std;

/*
	1. Constructor can't be virtual but here we've simulated the virtual constructor.
	1. Base class creates the Derived class objects with the help of static method.
	2. Consumer class calls the interface method which in turn calls the Derived class method
	3.
*/

//// LIBRARY START
class Base
{
public:

	// The "Virtual Constructor"
	static Base* Create(int id);

	Base() {}

	virtual // Ensures to invoke actual object destructor
		~Base() {}

	// An interface
	virtual void DisplayAction() = 0;
};

class Derived1 : public Base
{
public:
	Derived1()
	{
		cout << "Derived1 created" << endl;
	}

	~Derived1()
	{
		cout << "Derived1 destroyed" << endl;
	}

	void DisplayAction()
	{
		cout << "Action from Derived1" << endl;
	}
};

class Derived2 : public Base
{
public:
	Derived2()
	{
		cout << "Derived2 created" << endl;
	}

	~Derived2()
	{
		cout << "Derived2 destroyed" << endl;
	}

	void DisplayAction()
	{
		cout << "Action from Derived2" << endl;
	}
};

class Derived3 : public Base
{
public:
	Derived3()
	{
		cout << "Derived3 created" << endl;
	}

	~Derived3()
	{
		cout << "Derived3 destroyed" << endl;
	}

	void DisplayAction()
	{
		cout << "Action from Derived3" << endl;
	}
};

// We can also declare "Create" outside Base
// But it is more relevant to limit it's scope to Base
Base* Base::Create(int id)
{
	// Just expand the if-else ladder, if new Derived class is created
	// User code need not be recompiled to create newly added class objects

	if (id == 1)
	{
		return new Derived1;
	}
	else if (id == 2)
	{
		return new Derived2;
	}
	else
	{
		return new Derived3;
	}
}
//// LIBRARY END

//// UTILITY START
class User
{
private:
	Base* pBase;

public:
	User() : pBase(0) // initialize the private member
	{
		// Receives an object of Base heirarchy at runtime

		int input;

		cout << "Enter ID (1, 2 or 3): ";
		cin >> input;

		while ((input != 1) && (input != 2) && (input != 3))
		{
			cout << "Enter ID (1, 2 or 3 only): ";
			cin >> input;
		}

		// Get object from the "Virtual Constructor"
		pBase = Base::Create(input);
	}

	~User()
	{
		if (pBase)
		{
			delete pBase;
			pBase = 0;
		}
	}

	// Delegates to actual object
	void Action()
	{
		pBase->DisplayAction();
	}

};

//// UTILITY END

//// Consumer of User (UTILITY) class
void run_virtual_ctr()
{
	User* user = new User();

	// Action required on any of Derived objects
	user->Action();

	delete user;
	getchar();
	getchar();

	/*
		Enter ID (1, 2 or 3):
		1
		Derived1 created
		Action from Derived1
		Derived1 destroyed
	*/
}

//void main()
//{
//	run_virtual_ctr();
//}

