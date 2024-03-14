#include <iostream>
using namespace std;

/*
	1.

*/
void run_simple_one();
void run_copy_ctor_deleted();
void run_using_thread();
void run_using_thread_function();
void run_using_atomic_ref();
#include <thread>
void run_simple_one() {
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
	// [=] can't be used for atomic but [&] ref captured works

	atomic<int> at_int;
	at_int = 1;
	//<thread>

	//1.
	thread th = thread([&]() {
		cout << endl;
		int t = at_int.load(); // 1
		at_int++;
		cout << t;
		});

	th.join();
	cout << at_int << endl; // 2

	//2.

	//thread th2 = thread([=]() {
	//	cout << endl;
	//	int t = at_int.load(); // 1
	//	at_int++;
	//	cout << t;
	//	}); // error C2280: 'std::atomic<int>::atomic(const std::atomic<int> &)': attempting to reference a deleted function  .. here capture is [=] and for atomic its not possible, copy ctor is deleted. 

	//th2.join();
}

void th_func_with_atomic_int(atomic<int>& at_arg) {
	at_arg = at_arg + 1;
	cout << at_arg; //2
}

void run_using_thread_function() {
	// 

	atomic<int> at_int;
	at_int = 1; 
	
	//1. calling as regular function
	th_func_with_atomic_int(at_int);

	//2.
	//thread th1 = thread(th_func,  at_int); 
	// from memory - 'std::tuple<void (__cdecl *)(std::atomic<int> &),std::atomic<int>>::tuple(std::allocator_arg_t,const _Alloc &,_Other &&)': expects 3 arguments - 2 provided
	// from thread - 'invoke': no matching overloaded function found	MiscThreads	C : \Program Files\Microsoft Visual Studio\2022\Professional\VC\Tools\MSVC\14.39.33519\include\thread	60

	

	//2.
	thread th2 = thread(th_func_with_atomic_int, ref(at_int));
	th2.join();

	
}

#include <vector>
#include <mutex>
mutex mutex_print;
vector<int> vec_int;
#include <syncstream>
osyncstream osync(cout);
void th_func_with_int_ref(int& at_arg, vector<int>& vec_int) {
	at_arg = at_arg + 1; // here sometime it gives repeated numbers bcoz of race conditions, see below for atomic_ref<>()
	
	lock_guard<mutex> lk(mutex_print);
	vec_int.push_back(at_arg); // vector is not threadsafe, it crashes sometime 
	
	
	//cout << at_arg << " " ; // 2 4 56 1110 9 7   8 3
	
	//osync << at_arg << " "; // 4 3 7 8 2 5 6 9 10 12 13 13 14 15 16 17 19 19 20 21  .. it has repeated numbers
}

void th_func_with_int_ref_v2(int& at_arg, vector<int>& vec_int) {
	atomic_ref local =  atomic_ref<int>(at_arg);
	//local = local + 1;
	//this_thread::sleep_for(chrono::milliseconds(3)); // some time delay task
	local++;
	

	lock_guard<mutex> lk(mutex_print);
	vec_int.push_back(local.load()); // this is no repeated numbers bcoz of atomic_ref<>()
	
}

void run_using_atomic_ref() {
	
	int i_arg = 1;
	vector<thread> vec_threads;
	for (uint16_t i{}; i < 20; i++) // using 20 threads
	{
		vec_threads.push_back(thread(th_func_with_int_ref_v2, ref(i_arg), ref(vec_int))); // ref()
	}
	this_thread::sleep_for(chrono::seconds(2s)); // giving time for all threads to do their task
	for (auto& th : vec_threads)
		th.join();

	for (auto i : vec_int)
		cout << i << " "; //2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21

}

//int main()
//{
//	//run_one();
//	//run_using_thread();
//	//run_using_thread_function();
//
//	//run_using_atomic_ref();
//}

