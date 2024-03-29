#include <iostream>
using namespace std;

/*
	1. A race condition occurs when two or more threads can access shared data and they try to change it at the same time. Because the thread scheduling algorithm can swap between threads at any time, you don't know the order in which the threads will attempt to access the shared data. Therefore, the result of the change in data is dependent on the thread scheduling algorithm, i.e. both threads are "racing" to access/change the data.

		Problems often occur when one thread does a "check-then-act" (e.g. "check" if the value is X, then "act" to do something that depends on the value being X) and another thread does something to the value in between the "check" and the "act". E.g:

		if (x == 5) // The "Check"
		{
		   y = x * 2; // The "Act"

		   // If another thread changed x in between "if (x == 5)" and "y = x * 2" above,
		   // y will not be equal to 10.
		}
		The point being, y could be 10, or it could be anything, depending on whether another thread changed x in between the check and act. You have no real way of knowing.

		In order to prevent race conditions from occurring, you would typically put a lock around the shared data to ensure only one thread can access the data at a time. This would mean something like this:

		// Obtain lock for x
		if (x == 5)
		{
		   y = x * 2; // Now, nothing can change x until the lock is released. 
					  // Therefore y = 10
		}
		// release lock for x

	2. A race condition is a semantic error. It is a flaw that occurs in the timing or the ordering of events that leads to erroneous program behavior.
	
		when two threads access the same location in memory at the same time, and at least one of the accesses is a write." In the situation the "reader" thread may get the old value or the new value, depending on which thread "wins the race."

*/