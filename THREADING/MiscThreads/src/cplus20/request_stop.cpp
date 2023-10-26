#include <iostream>
using namespace std;

/*
	1. jthread - methods available in jthread class. request_stop().

	2. stop_source class
		stop_source ss = thread.get_stop_source(); 
		if (ss.stop_possible())
		{
			thread.request_stop();
		}
	
	3. check section "problems/thread_stop" 
*/
