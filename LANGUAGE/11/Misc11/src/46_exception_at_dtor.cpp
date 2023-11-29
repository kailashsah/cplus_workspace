#include <iostream>
using namespace std;

class TryException {
public:
	~TryException() noexcept(false)
	{
		cout << "dtor" << endl;
		/*
			//1.
			throw 1;  // terminates the program
			// solution is below step 2.

			output -
				inside try
				dtor
				dtor
		*/

		//2.
		try {

			throw 1;
		}
		catch (...)
		{
			cout << "dtor exception" << endl;
		}
	}
};

void run_dtor_exception()
{
	try {
		TryException a;
		TryException b;
		cout << "inside try" << endl;
		// dtor called for a, b
	}
	catch (...)
	{
		cout << "exc" << endl;
	}

	// code to check conituation of prg, above code terminated the process if more than one inner exception called & not handled inside the source point.
	int i;
	cout << "int i " << endl;
	std::cout << "ends";
	return;
}

void run_exception_two()
{
	run_dtor_exception();
}

//int main()
//{
//	run_exception_two();
//	return 0;
//}
