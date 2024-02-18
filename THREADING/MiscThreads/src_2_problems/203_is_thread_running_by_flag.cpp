#include <iostream>
using namespace std;

/*
	1. check if( thread_done ) to evaluate thread running

*/



std::atomic<bool> thread_done = false;

void* real_thread_function(void*) {

	return nullptr;
}

void* run_thread(void* arg)
{
	void* res = nullptr;

	try
	{
		res = real_thread_function(arg);
	}
	catch (...)
	{
	}

	thread_done = true;

	return res;
}