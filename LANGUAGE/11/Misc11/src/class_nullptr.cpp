#include <iostream>
#include <iomanip>
using namespace std;

/*
    1. he most likely behavior, on most modern computers, is that it will run, and print "fun", because:

        C++ doesn't check whether the pointer is NULL before calling the function
        fun() is not virtual, so there's no need to refer to a vtable to call fun()
        fun() never access any member variables in class, so it doesn't need to dereference the null this pointer.

    2.  1) All Functions are stored in code or text section.
        2) Non Virtual functions are resolved at complie time.
        3) While calling to member functions of class, we pass current object as this pointer to that function.

         here fun() function is already in memory(code section / text section). As function fun() is non virtual , it will be resolved at complie time (i.e, for this line it will jump to instruction X at code section with this pointer as NULL). As no member variable and no virtual function are used/called in fun() function, it is working fine.
    
    3. it shows undefined behavior in some compilers.

    4.  method doesn't access any member variables of the object it is called on (the memory where the object supposedly lives doesn't need to be accessed, so access violations don't necessarily occur).
*/
class ANullPtr
{
public:
    void fun()
    {
        std::cout << "fun" << std::endl;
    }
};


void run_class_by_nullptr()
{

    ANullPtr* a = nullptr;
    a->fun(); // prints 'fun'
}

//int main()
//{
//    run_class_by_nullptr();
//	return 0;
//}
