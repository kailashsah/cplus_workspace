#include <iostream>
using namespace std;

/*
	1.  1) A counting_semaphore is a lightweight synchronization primitive that can control access to a shared resource. Unlike a std::mutex, a counting_semaphore allows more than one concurrent access to the same resource, for at least LeastMaxValue concurrent accessors. The program is ill-formed if LeastMaxValue is negative.
		2) binary_semaphore is an alias for specialization of std::counting_semaphore with LeastMaxValue being 1. Implementations may implement binary_semaphore more efficiently than the default implementation of std::counting_semaphore.

	2. specialization binary_semaphore, LeastMaxValue is equal to 1.
		As its name indicates, the LeastMaxValue is the minimum max value, not the actual max value

	3. You can create a semaphore object like this:

		std::counting_semaphore<LeastMaxValue> sem(1); // Initialize a semaphore with an initial count of 1
		std::counting_semaphore is a type of semaphore that allows a specified number of threads to access a resource concurrently. In this example, only one thread can access the resource protected by sem at a time.

	4.	sem.acquire();
		// Critical section code
		sem.release();

	5. if (sem.try_acquire()) {
			// Successfully acquired the semaphore
			// Critical section code
			sem.release();
		} else {
			// Semaphore was not acquired

	6.   if (sem.try_acquire_for(std::chrono::seconds(1))) {
			// Successfully acquired the semaphore within 1 second
			// Critical section code
			sem.release();
		} else {
			// Semaphore was not acquired within 1 second
		}
}

*/
#include <iostream> 
#include <semaphore> 
#include <thread> 
#include <syncstream>
using namespace std;

// Initialize semaphore with a count of 3 
counting_semaphore<10> semaphoree(3);
osyncstream os{ cout };
#include <format> // std::format(): string
mutex mut_log;
//unique_lock lk(mut_sem);
#include <mutex> // std::lock()
void worker_sem(int id)
{
	mut_log.lock();
	//os << "Thread " << id << " before acquire"<< endl;
	string s = format("Thread {} before acquire \n", id);
	os << s;
	mut_log.unlock();

	// aquiring 
	semaphoree.acquire();

	// doing some work 
	os << "Thread " << id << " acquired the semaphore."
		<< endl;

	this_thread::sleep_for(2s);
	// releasing 
	semaphoree.release();
	os << "Thread " << id << " released the semaphore."
		<< endl;
}

void run_semaphore() {
	time_t begin, end;
	time(&begin);
	thread t1(worker_sem, 1);
	thread t2(worker_sem, 2);
	thread t3(worker_sem, 3);
	thread t4(worker_sem, 4);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	time(&end);
	double diff = difftime(end, begin);
	cout << "total seconds : " << diff << endl;

}

//int main()
//{
//	run_semaphore();
//	return 0;
//}

/*
	total seconds : 4
	Thread 3 before acquire
	Thread Thread 1 before acquire
	Thread Thread 2 before acquire
	Thread 3 acquired the semaphore.21 acquired the semaphore.

	 acquired the semaphore.
	Thread 4 before acquire
	Thread 4 acquired the semaphore.
	Thread Thread 1 released the semaphore.
	2 released the semaphore.
	Thread 3 released the semaphore.
	Thread 4 released the semaphore.
*/

/*
	Types of Semaphores
		The <semaphores> header provides two types of semaphores that are:

	1. std::counting_semaphore
		A counting semaphore is a synchronization primitive that allows multiple threads to access a shared resource up to a certain limit.

		It is a generalization of a mutex or a binary semaphore.
		You can initialize a counting semaphore with an initial count, which represents the number of threads that can access the resource simultaneously without blocking.
		Threads can acquire and release counts, and the semaphore’s count is incremented or decremented accordingly.
		If a thread tries to acquire more counts than are available, it will block until counts become available.

	2. std::binary_semaphore
		A binary semaphore is a simpler version of a semaphore that can have only two values: 0 and 1.

		It is often used for basic mutual exclusion or signaling between two threads.
		It can be thought of as a mutex with a more lightweight interface.
*/