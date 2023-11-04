#include <iostream>
using namespace std;

/*
	1.
*/

void run_atomic_shared_ptr_2()
{
	std::atomic<std::shared_ptr<int>> ptr;
	shared_ptr<int> sp = make_shared<int>(10);
	ptr.store(sp);
	shared_ptr<int> sp_1 = ptr.load();
	cout << sp_1.get() << endl;//009A53AC
	cout << *sp_1.get() << endl; //10 

}

//int main() {
//	run_atomic_shared_ptr_2();
//}
