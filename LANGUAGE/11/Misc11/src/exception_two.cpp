#include <iostream>
using namespace std;

class A {
public:
    ~A() noexcept(false)
    {
        cout << "dtor" << endl;
        /*
            throw 1;  // terminate the program
            // solution is below
        */

        try {
            
            throw 1;
        }
        catch (...)
        {

        }
    }
};

void run_dtor_exception()
{
    try {
        A a;
        A b;
        cout << "inside try" << endl;
        // dtor called for a, b
    }
    catch (...)
    {
        cout << "exc" << endl;
    }
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
//	run_exception();
//	return 0;	
//}
