#include <iostream>
using namespace std;

/*
	1. 

*/
#include <thread>
void run_one() {
	//<atomic>
	atomic<int> at_int;
	at_int = 1;
	at_int = 2;
	cout << at_int << endl; // 2

}

void run_copy_ctor_deleted() {

	atomic<int> at_int;
	at_int = 1;
	
	atomic<int> iat2;
	//1.
	//iat2 = at_int;  // error C2280: 'std::atomic<int>::atomic(const std::atomic<int> &)': attempting to reference a deleted function .. copy ctor is deleted
	
	
	cout << at_int << endl; 

}

void run_using_thread() {

	atomic<int> at_int;
	at_int = 1;
	//<thread>
	thread th = thread([&]() {
		cout << endl;
		int t = at_int.load();
		at_int++;
		cout << t;
		});

	th.join();
	cout << at_int << endl;

}

int main()
{
	//run_one();
	run_using_thread();
}

