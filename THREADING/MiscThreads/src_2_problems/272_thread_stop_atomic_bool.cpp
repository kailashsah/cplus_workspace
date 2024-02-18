#include <iostream>
using namespace std;
/*
	1. use 'std::atomic<bool> stop_thread ' to identify the thread is stopped.
*/
#include <chrono>
void run_stop_thread() {

	//1.  use atomic variable to flag stop
	std::atomic<bool> stop_thread = false;

	//2. in thread function
	if (stop_thread)
		return;
}

//void main()
//{
//	
//}