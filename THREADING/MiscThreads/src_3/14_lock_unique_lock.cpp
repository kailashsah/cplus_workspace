#include <iostream>
using namespace std;

/*
	1. unique_lock - The class unique_lock is a general-purpose mutex ownership wrapper allowing deferred locking, time-constrained attempts at locking, recursive locking, transfer of lock ownership, and use with condition variables.

	2.  use a unique lock when you want to conditionally lock or unlock a mutex, such as waiting for a condition variable or using a try_lock method.

	3. std::unique_lock use the RAII pattern

	4. If a exceptions is thrown, the std::unique_lock destructor will be called and so the mutex will be unlocked.   (IMP)

*/



