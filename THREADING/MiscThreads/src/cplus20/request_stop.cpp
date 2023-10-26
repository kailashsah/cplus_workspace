#include <iostream>
using namespace std;

/*
	1. jthread - advantage that it can be used to stop a thread by releasing resources

	2. stop_source ss = thread.get_stop_source();
		if (ss.stop_possible())
			thread.request_stop();
	
	3. check section "problems/thread_stop" 
*/
