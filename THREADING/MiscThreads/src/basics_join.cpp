#include <iostream>
using namespace std;

#include <thread> // std::this_thread, thread class
void pause_thread(int n)
{
	std::this_thread::sleep_for(std::chrono::seconds(n));
	std::cout << "pause of " << n << " seconds ended\n";
}

void run_thread_join() {
	/*
		1. join() - The function returns when the thread execution has completed.
			This synchronizes the moment this function returns with the completion of all the operations in the thread
		2. After a call to this function, the thread object becomes non-joinable and can be destroyed safely.
		3. when you join a thread that doesn't cause the thread to terminate. It simply blocks until that thread dies of natural (or unnatural) causes.
	*/
	std::cout << "Spawning 3 threads...\n";
	std::thread t1(pause_thread, 1);
	std::thread t2(pause_thread, 2);
	std::thread t3(pause_thread, 3);
	std::cout << "Done spawning threads. Now waiting for them to join:\n";
	t1.join();
	t2.join();
	t3.join();
	std::cout << "All threads joined!\n";

}



//int main()
//{
//	run_thread_join();
//	return 1;
//}