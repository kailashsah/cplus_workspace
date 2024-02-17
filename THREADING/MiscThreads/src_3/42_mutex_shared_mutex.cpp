#include <iostream>
using namespace std;

/*
	1. std::shared_mutex - While a regular mutex exposes 3 methods: lock, unlock and try_lock,

		Shared Mutex however adds 3 more methods::
		lock_shared
		try_lock_shared
		unlock_shared
		where shared means  several threads can share ownership of the same mutex.

	2. shared mutex class adds the ability to provide shared access to the mutex.

		This allows one to, for example, provide read access to a resource by multiple threads, while a writing thread would still be able to gain exclusive access.
		
		provides shared mutual exclusion facility

	3. Point to note::
		a, If one thread has acquired the exclusive lock (through lock, try_lock), no other threads can acquire the lock (including the shared).
		b, If one thread has acquired the shared lock (through lock_shared, try_lock_shared), no other thread can acquire the exclusive lock, but can acquire the shared lock.
		c, Only when the exclusive lock has not been acquired by any thread, the shared lock can be acquired by multiple threads.
		Within one thread, only one lock (shared or exclusive) can be acquired at the same time.

	4. Read Write Lock - This has a variety of uses, but one common one is to implement a Read Write Lock where you could have multiple threads reading shared data, but only one thread exclusively writing at any time. So when you have multiple readers the mutex acts in "shared mode", but when a write is requested it changes into "exclusive mode".

	5. https://cppsecrets.com/
*/

#include <iostream>
#include <thread>
#include <shared_mutex>

int g_iValue = 0;
std::shared_mutex smutex;

// Reads the value and sets v to that value
void readValue(int& v) {
	smutex.lock_shared();
	// Simulate some latency/time to run
	std::this_thread::sleep_for(std::chrono::seconds(1));
	v = g_iValue;
	smutex.unlock_shared();
}

// Sets value to v
void setValue(int v) {
	smutex.lock();
	// Simulate some latency/time to run
	std::this_thread::sleep_for(std::chrono::seconds(1));
	g_iValue = v;
	smutex.unlock();
}
void run_shared_mutex() {
	int read1;
	int read2;
	int read3;
	std::thread t1(readValue, std::ref(read1));
	std::thread t4(setValue, 1);
	std::thread t2(readValue, std::ref(read2));
	std::thread t3(readValue, std::ref(read3));

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	std::cout << read1 << "\n";
	std::cout << read2 << "\n";
	std::cout << read3 << "\n";
	std::cout << g_iValue << "\n";
	/*
		0
		0
		1
		1
	*/
}

//int main() {
//	run_shared_mutex();
//}

