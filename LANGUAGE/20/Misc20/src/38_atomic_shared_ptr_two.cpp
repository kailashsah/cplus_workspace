#include <iostream>
using namespace std;

/*
	1. The partial template specialization of std::atomic for std::shared_ptr<T> allows users to manipulate shared_ptr objects atomically.

		If multiple threads of execution access the same std::shared_ptr object without synchronization and any of those accesses uses a non-const member function of shared_ptr then a data race will occur unless all such access is performed through an instance of std::atomic<std::shared_ptr>
	
	2. std::atomic<std::weak_ptr>

	3.
*/

void run_atomic_shared_ptr_2()
{
	// see store() & load() calls
	std::atomic<std::shared_ptr<int>> ptr; // <memory>

	shared_ptr<int> sp = make_shared<int>(10);

	ptr.store(sp);
	shared_ptr<int> sp_1 = ptr.load();
	cout << sp_1.get() << endl;//009A53AC
	cout << *sp_1.get() << endl; //10 

}

//int main() {
//	run_atomic_shared_ptr_2();
//}
