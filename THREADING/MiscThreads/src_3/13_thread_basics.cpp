#include <iostream>
using namespace std;

/*
	1. mutex - The mutex class is a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads.

		mutex offers exclusive (restricted to one person), non-recursive ownership semantics:

		-- A calling thread owns a mutex from the time that it successfully calls either lock or try_lock until it calls unlock.
		-- When a thread owns a mutex, all other threads will block (for calls to lock) or receive a false return value (for try_lock) if they attempt to claim ownership of the mutex.
		-- A calling thread must not own the mutex prior to calling lock or try_lock.

	2.  If lock is called by a thread that already owns the mutex, the behavior is undefined: for example, the program may deadlock. 
		An implementation that can detect the invalid usage is encouraged to throw a std::system_error with error condition "resource_deadlock_would_occur" instead of deadlocking.  

	3. diff mutex.lock() vs std::lock() - std::lock(m1, m2, m2) lockable objects.
*/

#include <thread> // std::this_thread, thread class
//1. ------------------
void run_thread_basics()
{
	//1.
	unsigned num_threads = std::thread::hardware_concurrency();
	
}


//2. ------------------
struct my_thread {
	int my_data = 0;
	void operator()() { my_data = 1; }
};

my_thread this_threadfn;
std::thread t1;

void run() {
	int a;
	t1 = thread(std::ref(this_threadfn));
	if (t1.joinable()) // check required to see if t1 hold the alive thread or valid thread.
		t1.join();
}

//int main()
//{
//	run_all_thread_basics();
//	return 1;
//}