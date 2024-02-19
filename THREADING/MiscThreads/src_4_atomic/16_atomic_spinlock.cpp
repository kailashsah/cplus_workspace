#include <iostream>
using namespace std;

/*
	1. Motivation -
		When a thread tries to lock a mutex and the mutex is already locked, it will move to a sleep state, now another thread can run. this state will change only when the thread is awakened and when the mutex is unlocked by the thread holding the lock.

		a) On the contrary, when a thread locks a spinlock and fails, it will continuously re-try locking it, until it succeeds. This time it will not allow another thread to take its place, note that the operating system will switch to another thread eventually once the CPU runtime quota of the current thread has been exceeded.
		b) In the case of a mutex putting a thread to sleep, creates a context switch and has its performance penalty. If you wish to avoid this penalty and have a short lock time then spinlock may be the answer for you. Be aware most of the time spinlock is not your answer.

	2. We will need an atomic way to determine if the lock is currently free or in use, atomic means it is guaranteed to be isolated from other operations that may be happening at the same time. So we know for sure that when we test the variable for its state or even change its state we are guaranteed we are safe from context switching.

		A nice definition I reviewed: an operation acting on shared memory is atomic if it completes in a single step relative to other threads.

		In our case, one might think that we can just use a boolean and alter it when we acquire the lock – but this operation does not guarantee atomics since when setting a boolean we actually have 2 steps to load and write. Luckily we have the atomic library that we can use that will currently set and check a variable will be atomic.

		#include <atomic>


		std::atomic_flag atomic_flag = ATOMIC_FLAG_INIT;
		ATOMIC_FLAG_INIT – This is the only way to initialize std::atomic_flag to a definite value: the value held after any other initialization is unspecified.

		std::atomic_flag is an atomic boolean type. Unlike all specializations of std::atomic, it is guaranteed to be lock-free. Unlike std::atomic<bool>, std::atomic_flag does not provide load or store operations.

			std::atomic_flag is the only atomic data type that is always lock-free

			ex. Spinlock class https://www.talkinghightech.com/en/implementing-a-spinlock-in-c/

	3. load() - Return value The current value of the atomic variable.
*/
struct ttas_lock;
class Spinlock;
//
#include <string>
#include <vector>
#include <mutex> 
#include <thread>
#include <atomic>

struct ttas_lock {
	atomic<bool> lock_{ false };

	void lock() {
		for (;;) {
			if (!lock_.exchange(true, std::memory_order_acquire)) {
				// tries spin but failed
				// for exchange() - https://en.cppreference.com/w/cpp/atomic/atomic/exchange
				break;
			}
			while (lock_.load(std::memory_order_relaxed)) { // if spin failed, do wait
				//__builtin_ia32_pause(); // On GCC 
				_mm_pause(); // on msvc
				/*
					reduce power usage and contention on the load-store units.
					problem -
						allowing multiple logical CPU cores to share the main execution resources such as arithmetic logic unit (ALU), load-store unit (LSU or cache) etc.

						Our improved lock above will execute a load operation almost every cycle while spinning. This will starve other logical CPU cores sharing the same load-store unit as the spinning core.

						https://rigtorp.se/spinlock/
				*/
			}
		}
		// This implementation is usually called a test and test-and-set (TTAS) lock.
	}

	void unlock() {
		lock_.store(false, std::memory_order_release);
	}

};
//.....
class Spinlock
{
private:
	std::atomic_flag atomic_flag = ATOMIC_FLAG_INIT;

public:
	void lock()
	{
		//1.
		//while (atomic_flag.test_and_set()) //ok

		//2.
		while (atomic_flag.test_and_set(std::memory_order_acquire))
		{
		}

	}
	void unlock()
	{
		//1.
		//atomic_flag.clear(); //ok

		//2.
		atomic_flag.clear(std::memory_order_release);
	}
};
const int count_to = 1000000;
volatile int g_iValue = 0;
//1.
//Spinlock l;
mutex m;

//2.
ttas_lock l;



int task_using_reg_lock_guard(int count_to)
{
	//this created to evaluate the time taken while using regular locks.
	int local_var = 0;
	std::cout << "Started  " << count_to << std::endl;
	for (int i = 0; i < count_to; ++i)
	{
		local_var++;
		//usleep(1);
	}
	lock_guard<mutex> lk(m);
	g_iValue += local_var;
	cout << this_thread::get_id() << " :" << local_var << endl;// all 5 threads prints 10000, 10000 .... to value variable
	return 0;
}


int task_using_spinlock(int count_to)
{

	std::cout << "Started  " << count_to << std::endl;
	for (int i = 0; i < count_to; ++i)
	{
		//1.
		l.lock();
		g_iValue++;
		l.unlock();

		//2.
		//lock_guard<mutex> lk(m);
		//value++;  // both methods takes equal time // difference comes out "2". 

		// std::cout << "Value  " << value << std::endl;
		// l.unlock();
	}

	return 0;
}
void run_spin_lock() {
	time_t begin, end; // time_t is a datatype to store time values.
	time(&begin);      // note time before execution
	const int num_workers = 5;
	std::vector<std::thread> threads;
	std::cout << "SpinLock inc MyTest start" << std::endl;
	g_iValue = 0;
	for (int i = 0; i < num_workers; ++i)
		threads.push_back(std::move(std::thread(task_using_spinlock, count_to)));

	for (auto it = threads.begin(); it != threads.end(); it++)
		it->join();

	time(&end); // note time after execution
	double difference = difftime(end, begin);
	std::cout << "job done" << std::endl;
	std::cout << "count_: " << g_iValue << std::endl;
	std::cout << "time taken for function() %.2lf seconds.\n" << std::endl;

	//std::cout << std::fixed << std::setw(11) << std::setprecision(6)  << std::setfill('0') << difference;
	std::cout << difference;
	if (g_iValue == count_to * num_workers)
	{
		std::cout << "SpinLock  passed" << std::endl;
		return;
	}
	else
	{
		std::cout << "SpinLock failed" << std::endl;
		return;
	}

}

//int main(int, char**)
//{
//	run_spin_lock();
//}