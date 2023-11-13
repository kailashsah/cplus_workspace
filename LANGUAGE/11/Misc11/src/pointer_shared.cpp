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

	//1.
	shared_ptr<ex> sptr(pi);
	
	//2.
	shared_ptr<int> sptr_int = make_shared<int>(5);

	//3.
	shared_ptr<int> sptr_int1 = sptr_int; // copy ctor
	cout << sptr_int << endl; // print address
	cout << *sptr_int << endl; // 5
	cout << sptr_int.use_count() << endl; // 2,  count shared b/t pointers

	//4.
	cout << endl << "sptr_int.reset() : " << endl;
	sptr_int.reset(); // remove underlying memory
	
	
	//5.
	cout << endl << "* sptr_int : " << endl;
	//cout << *sptr_int << endl; // crash
	/*
		Exception thrown: read access violation.
		std::shared_ptr<int>::operator*<int,0>(...) returned nullptr.
	*/

	//6.
	cout << endl << "sptr_int.use_count() : " << endl;
	cout << sptr_int.use_count() << endl; // after reset, it is zero 
}

//int main()
//{
//	run_shared_ptr();
//	return 0;
//}



