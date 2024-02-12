#include <iostream>
using namespace std;

/*
	1.  recursive mutex allows mutex to be locked more than once without getting to a deadlock and should be unlocked the same number of times.
	2. For example when you have function that calls it recursively, and you want to get synchronized access to it:

		void foo() {
		   ... mutex_acquire();
		   ... foo();
		   ... mutex_release();
		}
		without a recursive mutex you would have to create an "entry point" function first, and this becomes cumbersome when you have a set of functions that are mutually recursive. Without recursive mutex:

		void foo_entry() {
		   mutex_acquire(); foo(); mutex_release(); }

		void foo() { ... foo(); ... }

	3. If you want to call functions recursively, which lock the same mutex, then they either
		a, have to use one recursive mutex, or
		b, have to unlock and lock the same non-recursive mutex again and again (beware of concurrent threads!) (assuming this is semantically sound, it could still be a performance issue), or
		c, have to somehow annotate which mutexes they already locked (simulating recursive ownership/mutexes).

*/
void run_recursive_mutex();
//
#include <iostream>
#include <mutex> // recursive_mutex
#include <thread>

class X
{
	std::recursive_mutex m;
	//mutex mr;
	std::string shared;
public:
	void fun1()
	{
		std::lock_guard<std::recursive_mutex> lk(m);
		//unique_lock<mutex> lk(mr);
		//lock_guard<mutex> lk(mr);
		shared = "fun1";
		std::cout << "in fun1, shared variable is now " << shared << '\n';
	}
	void fun2()
	{
		//1.
		std::lock_guard<std::recursive_mutex> lk(m);
		//2.
		//unique_lock<mutex> lk(mr); // crashing at t2.join()
		//3.
		//lock_guard<mutex> lk1(mr); // 
		/*
			only these two are coming with values.
			"in fun1, shared variable is now "
			"in fun2, shared variable is now "
			crashed.
		*/

		shared = "fun2";
		std::cout << "in fun2, shared variable is now " << shared << '\n';
		fun1(); // recursive lock becomes useful here
		std::cout << "back in fun2, shared variable is " << shared << '\n';
	}
};

void run_recursive_mutex() {
	X x;
	std::thread t1(&X::fun1, &x);
	std::thread t2(&X::fun2, &x);
	t1.join();
	t2.join();

	/*
		in fun2, shared variable is now fun2
		in fun1, shared variable is now fun1
		back in fun2, shared variable is fun1
		in fun1, shared variable is now fun1
	*/
}

//void main() {
//    run_recursive_mutex();
//}