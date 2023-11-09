#include <iostream>
using namespace std;

/*
	1.

	2. shared_future<>

	3. all thread wait at some point till some work completion, & resume after that. (latch, barrier) 

*/

/*
	Tutotial in sequence - 
		- Datarace, deadlock concepts
		- thread, join(), detach(), jthread{}
		- mutex, mutex.lock(), unique_lock<>, lock_guard<>
		- future, future.valid(), promise, promise.set_value()
		- packaged_task
		- async
		- lock(m,m,m..), scoped_lock{m,m,m...} - for deadlock safe algorithms
		- condition_variable, wait(), 

	todo
		- run_promise_as_signal() - promise<>
		- shared_future - one future obj used by multiple threads
		- timed_mutex - try_lock_for(duration), try_lock_until(time), now + duration.
		- shared_mutex - mutex_shared_mutex.cpp, same thing for shared_timed_mutex
		- shared_lock - mutex_shared_lock_two.cpp .. more than 1 reader thread can enter

	semaphores 
		- latch
		- barrier, on_completion function callback 
		- 

*/

