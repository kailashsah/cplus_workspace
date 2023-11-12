#include <iostream>
using namespace std;

/*
	1.  A semaphore is a non-negative variable which can be used to access a common resource of the operating system.

		Semaphores are used to overcome the critical section problem. The critical section is an area in a program that is used to access common resources. But, two programs cannot enter the critical section simultaneously Semaphores come in handy in such situations.

	2. There are two types of semaphores:

		Binary semaphores: As the name suggests, a binary semaphore can take only two values, 0 and 1. The default value of a binary semaphore is 1. It is also known as a mutex lock.
		Counting semaphores: These have values which may range from 0 to any number ‘n’. They have an unrestricted domain.

	3. Semaphores solve the critical section problem by using two atomic operations, wait() and signal().

		a) wait operation: if the value of the semaphore s is negative or zero, no operation is performed. If the value of s is positive, it is decremented. The pseudocode for wait operation is as follows:

		wait(s)
		{
		while(s<=0);
		s--;
		}
		
		b) signal operation: This operation is used to increase the value of the semaphore s. The pseudocode for signal operation is as follows:

		signal(s)
		{
		s++
		}

	4. https://www.codespeedy.com/semaphores-in-cpp/  (code difficult to read)

*/

int main()
{
    

}

