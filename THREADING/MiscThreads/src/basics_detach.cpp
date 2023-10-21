#include <iostream>
using namespace std;
/*
	1. In the destructor of std::thread, std::terminate is called if:

		the thread was not joined (with t.join())
		and was not detached either (with t.detach())
		Thus, you should always either join or detach a thread before the flows of execution reaches the destructor.

	2. When a program terminates (ie, main returns) the remaining detached threads executing in the background are not waited upon; instead their execution is suspended and their thread-local objects are not destructed.

	3. Hopefully the OS will release the locks on files, etc... but you could have corrupted shared memory, half-written files, and the like.

	4. So, should you use join or detach ?

		Use join
		Unless you need to have more flexibility AND are willing to provide a synchronization mechanism to wait for the thread completion on your own, in which case you may use detach

	5. detach basically will release the resources needed to be able to implement join.

	6. There is no way to make such a thread to exit gracefully so use of join will just lead to primary thread blocking. That's a situation when using detach would be a less evil alternative to, say, allocating thread object with dynamic storage duration and then purposely leaking it.

	7. detach() is mainly useful when you have a task that has to be done in background, but you don't care about its execution. This is usually a case for some libraries. They may silently create a background worker thread and detach it so you won't even notice it.
*/

#include <thread> // std::this_thread, thread class

auto NastyBlockingFunction() { return int{}; }
auto LegacyApiThreadEntry(void)
{
	auto result = NastyBlockingFunction();
	return result;
	// do something...
}

void run_thread_detach() {

	::std::thread legacy_api_thread{ &LegacyApiThreadEntry };
	// do something...
	legacy_api_thread.detach();

}

//int main()
//{
//	run_thread_detach();
//	return 1;
//}