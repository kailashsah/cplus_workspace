
#include <iostream>
using namespace std;

#include <mutex>
class singleton {
private:
	static singleton* ptr;
	static mutex mtx;
	singleton()
	{

	}
public:
	static singleton* getInstance();
};
singleton* singleton::ptr;
mutex singleton::mtx;
singleton* singleton::getInstance()
{
	cout << "getInstance called." << endl;
	if (ptr == nullptr) {
		lock_guard<mutex> lock(mtx);
		if (ptr == nullptr)
		{
			cout << "object pointer created" << endl;
			ptr = new singleton();
		}

	}

	return ptr;
}

void run_singleton_non_thread() {
	singleton* objA = singleton::getInstance();
	singleton* objB = singleton::getInstance();
	if (objA == objB)
		cout << "equal objects" << endl;
	else
		cout << "objects not equal" << endl;
}

#include<thread>
void run_singleton_using_thread() {
	//jthread th1{ &singleton::getInstance }; // error : jthread is undeclared identifier
	//jthread th2{ singleton::getInstance };

	thread th3{ singleton::getInstance }; // error : jthread is undeclared identifier
	thread th4{ singleton::getInstance };

	th3.join();
	th4.join();

}

//int main() {
//
//	//run_singleton_non_thread();
//	run_singleton_using_thread();
//	return 1;
//}
