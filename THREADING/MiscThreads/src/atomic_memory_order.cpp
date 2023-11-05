#include <iostream>
using namespace std;

/*
	1.  'release' and 'acuire' can be used separately to prevent corresponding reordering.

		problem - The statements about 'moving before' or 'moving after' are instructions to the optimizer that it shouldn't re-order operations to take place . Optimizers are very good at re-ordering instructions and even omitting redundant reads/writes but if they re-organise the code across the memory barriers they may unwittingly violate that order.

	2. memory_order_acquire and memory_order_release as:

		Acquire operation: no reads in the current thread can be reordered before this load.
		Release operation: no writes in the current thread can be reordered after this store.

	3. The point is this: acquires and releases are sequentially consistent1 (all threads globally agree on the order in which acquires and releases happened.) All threads globally agree that the stuff that happens between an acquire and a release on a specific thread happened between the acquire and release.

		But normal loads and stores after a release are allowed to be moved (either by hardware or the compiler) above the release,
		and normal loads and stores before an acquire are allowed to be moved (either by hardware or the compiler) to after the acquire.

	4. A store operation with this memory order performs the release operation: no reads or writes in the current thread can be reordered after this store. All writes in the current thread are visible in other threads that acquire the same atomic variable (see Release-Acquire ordering below) and writes that carry a dependency into the atomic variable become visible in other threads that consume the same atomic (see Release-Consume ordering below).

	5. All memory writes (including non-atomic and relaxed atomic) that happened-before the atomic store from the point of view of thread A, become visible side-effects in thread B. That is, once the atomic load is completed, thread B is guaranteed to see everything thread A wrote to memory. This promise only holds if B actually returns the value that A stored, or a value from later in the release sequence.
		   The synchronization is established only between the threads releasing and acquiring the same atomic variable. Other threads can see different order of memory accesses than either or both of the synchronized threads.

	6. Mutual exclusion locks, such as std::mutex or atomic spinlock, are an example of release-acquire synchronization: when the lock is released by thread A and acquired by thread B, everything that took place in the critical section (before the release) in the context of thread A has to be visible to thread B (after the acquire) which is executing the same critical section.
		ex. consumer()

	7. This example demonstrates dependency-ordered synchronization for pointer-mediated publication: the integer data is not related to the pointer to string by a data-dependency relationship, thus its value is undefined in the consumer.
		ex. consumerr()


*/
void run_producer_consumer();
//
#include <atomic>
#include <cassert>
#include <string>
#include <thread>

std::atomic<std::string*> ptrr;
int data2;

void producerr()
{
	std::string* p = new std::string("Hello");
	//this_thread::sleep_for(1s);
	data2 = 42;
	ptrr.store(p, std::memory_order_release);
}

void consumerr()
{
	std::string* p2;
	while (!(p2 = ptrr.load(std::memory_order_consume)))
		;
	assert(*p2 == "Hello"); // never fires: *p2 carries dependency from ptr
	assert(data2 == 42); // may or may not fire: data does not carry dependency from ptr
}
void consumer()
{
	std::string* p2;
	while (!(p2 = ptrr.load(std::memory_order_acquire)))
		;
	assert(*p2 == "Hello"); // never fires
	assert(data2 == 42); // never fires
}
void run_producer_consumer() {
	std::thread t1(producerr);
	std::thread t2(consumerr);
	t1.join(); t2.join();
}

int main()
{
	run_producer_consumer();
}

/*
memory_order_consume - A load operation with this memory order performs a consume operation on the affected memory location: no reads or writes in the current thread dependent on the value currently loaded can be reordered before this load. Writes to data-dependent variables in other threads that release the same atomic variable are visible in the current thread. On most platforms, this affects compiler optimizations only.

memory_order_acquire -	A load operation with this memory order performs the acquire operation on the affected memory location: no reads or writes in the current thread can be reordered before this load. All writes in other threads that release the same atomic variable are visible in the current thread .

memory_order_release - 	A store operation with this memory order performs the release operation: no reads or writes in the current thread can be reordered after this store. All writes in the current thread are visible in other threads that acquire the same atomic variable (see Release-Acquire ordering below) and writes that carry a dependency into the atomic variable become visible in other threads that consume the same atomic .

memory_order_seq_cst -	A load operation with this memory order performs an acquire operation, a store performs a release operation, and read-modify-write performs both an acquire operation and a release operation, plus a single total order exists in which all threads observe all modifications in the same order.
*/

