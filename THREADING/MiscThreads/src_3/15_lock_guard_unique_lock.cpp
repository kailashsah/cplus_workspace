#include <iostream>
/*
	1.  you can lock and unlock a std::unique_lock. 
		std::lock_guard will be locked only once on construction and unlocked on destruction (RAII version of unique_lock).

	2. std::unique_lock might have a  more overhead. 
		we can unlock() unique_lock<> before the end of scope of parent.
*/

void run_lockxyz()
{
}

//int main()
//{
//	run_lock();
//	return 1;
//}

