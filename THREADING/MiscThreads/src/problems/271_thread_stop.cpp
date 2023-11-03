#include <iostream>
using namespace std;

/*
	1. jthread - advantage that it can be used to stop a thread by releasing resources

	2. This request is likely to be granted, but there is no guarantee that it will be granted. If the request is granted, then the thread stops as soon as possible, without reaching its natural end, everything being equal.

	3. Once a stop request has been made, it cannot be withdrawn (a subsequent stop request has no effect).
		https://linuxhint.com/kill-thread-c/
	
	4. std::terminate kills your entire process . The correct (and only correct in standard C++) way to terminate a thread is to return from its thread function. std::terminate is meant to be used on a critical failure where your program cannot possibly continue.

*/
#include <chrono>
const uint8_t max_time = 100;
void th_function() {

	for (uint8_t i{}; i < 10; i++) {
		this_thread::sleep_for( chrono::milliseconds(max_time) );
		cout << i << endl;
	}
	cout << "th_function() ends" << endl;
	for (uint8_t i{}; i < 10; i++) {
		this_thread::sleep_for(chrono::milliseconds(max_time));
		cout << i << endl;
	}
	cout << "th_function() ends" << endl;
}
void is_thread_alive(jthread& th) {

	while (th.joinable())
	{
		this_thread::sleep_for(chrono::milliseconds( max_time));
		cout << "thread is still alive" << endl;
	}
	cout << "fn_thread_checker() ends" << endl;
}
//.................................................

void run_thread_request_stop() {
	jthread thread(th_function);
	string log = (thread.request_stop())?   "stop accepted": "stop rejected"; // Accepting the request does not guarantee that the thread will stop as soon as possible
	cout << log << endl;
	thread.join();
}
void run_thread_stop_possible() {
	jthread thread(th_function);
	stop_source ss =  thread.get_stop_source();
	if (ss.stop_possible())
	{
		string log = (thread.request_stop()) ? "stop accepted" : "stop rejected"; // Accepting the request does not guarantee that the thread will stop as soon as possible
		cout << log << endl;
	}
	else {
		cout << "stop is not possible" << endl;
	}

	thread.join();
}

void run_thread_stop_requested() {
	jthread thread(th_function);
	jthread threadChecker(is_thread_alive, std::ref(thread));
	
	//
	stop_source ss = thread.get_stop_source();
	if (ss.stop_possible())
	{
		string log = (thread.request_stop()) ? "stop accepted" : "stop rejected"; // Accepting the request does not guarantee that the thread will stop as soon as possible
		cout << log << endl;
	}
	else {
		cout << "stop is not possible" << endl;
	}

	//
	stop_token st =  thread.get_stop_token();
	string log = st.stop_requested() ? "stop requested" : "stop not requested";
	cout << log << endl;
	thread.request_stop();  // no use if called earlier


	thread.join();
}

//void main()
//{
//	//run_thread_request_stop();
//	//run_thread_stop_possible();
//	run_thread_stop_requested();
//}