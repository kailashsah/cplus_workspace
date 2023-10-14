import <iostream>;

using namespace std;

// Type your code here, or load an example.
#include <memory>
// #include  <experimental/atomic>

#include  <atomic>
#include <atomic>
#include <memory>
#include <thread>
#include <syncstream> // osyncstream

void run_atomic_shared_ptr()
{
	atomic< shared_ptr<int>> ptr = make_shared<int>(10);
	//    shared_ptr<int> ptr = make_shared<int> (10); 
	std::jthread thread1(
		[&ptr]() mutable {

			auto sharedPtr = ptr.load();
			std::osyncstream(std::cout) << "  1 value " << *(sharedPtr.get()) << endl;
			//ptr = make_shared<int>(5);
			ptr.store(make_shared<int>(5));
		});
	std::jthread thread2(
		[&ptr]() mutable {
			auto sharedPtr = ptr.load();
			std::osyncstream{ std::cout } << " 2 value " << *(sharedPtr.get()) << endl;
			//ptr = make_shared<int>(6);
			ptr.store(make_shared<int>(6));

		}
	);
	this_thread::sleep_for(chrono::microseconds(2000));

	auto sharedPtr = ptr.load(); // threadsafe
	std::osyncstream(std::cout) << " value " << *(sharedPtr.get()) << endl;

	//    thread1.join();
	//    thread2.join();
	std::osyncstream(std::cout) << "ends" << endl;
}

void run_simple_shared_ptr()
{
	shared_ptr<int> ptr = make_shared<int>(10);
	std::jthread thread1(
		[&ptr]() mutable {

			//auto sharedPtr = ptr.load(); // load() not for shared_ptr<>
			std::osyncstream(std::cout) << "  1 value " << *(ptr.get()) << endl;
			ptr = make_shared<int>(5);
		});
	std::jthread thread2(
		[&ptr]() mutable {
			//auto sharedPtr = ptr.load();
			std::osyncstream{ std::cout } << " 2 value " << *(ptr.get()) << endl;
			ptr = make_shared<int>(6);

		}
	);
	this_thread::sleep_for(chrono::microseconds(2000));

	std::osyncstream(std::cout) << " value " << *(ptr.get()) << endl;

	//    thread1.join();
	//    thread2.join();
	std::osyncstream(std::cout) << "ends" << endl;
}

void run_file_atomic_src() {
	//1.
	run_atomic_shared_ptr();
	/*  2 value 10
	   1 value 10
	   value 6
	   ends
	*/

	//2.
	run_simple_shared_ptr();
	/*  2 value 10
		1 value 10
		value 5
		ends
	 */
}

//int main()
//{
//	run_file_atomic_src();
//	return 1;
//}

