#include <iostream>
//import <iostream>;
using namespace std;
 
class ex {
public:
	int i;
	~ex()
	{
		cout << "dtor " << endl;
	}
};

void run_shared_ptr()
{
	ex* pi = new ex;

	shared_ptr<ex> sptr(pi);
	shared_ptr<int> sptr_int = make_shared<int>(5);

	shared_ptr<int> sptr_int1 = sptr_int;
	cout << sptr_int << endl; // print address
	cout << *sptr_int << endl;
	cout << sptr_int.use_count() << endl; // count shared b/t pointers

	sptr_int.reset(); // remove underlying memory
	cout << *sptr_int << endl; // crash
	cout << sptr_int.use_count() << endl; // after reset, it is zero 
}
//int main()
//{
//	run_shared_ptr();
//	return 0;
//}



