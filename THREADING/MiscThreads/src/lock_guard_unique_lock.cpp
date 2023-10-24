#include <iostream>
/*
	1.  you can lock and unlock a std::unique_lock. std::lock_guard will be locked only once on construction and unlocked on destruction.

	2. std::unique_lock might have a  more overhead.
*/

void run_lockxyz()
{
	std::cout << "Hello World!\n";
}

//int main()
//{
//	run_lock();
//	return 1;
//}

