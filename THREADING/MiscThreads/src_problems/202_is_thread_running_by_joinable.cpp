#include <iostream>
using namespace std;

/*
	1.
*/
#include <future>
#include <thread>
#include <chrono>
#include <iostream>

#include <chrono>
const uint8_t max_time = 100;
void thread_fn() {

	
	cout << "thread_fn() ends" << endl;
}
void is_thread_alive_v2(jthread& th) {

	while (th.joinable())
	{
		this_thread::sleep_for(chrono::milliseconds(max_time));
		cout << "thread is still alive" << endl;
	}
	cout << "fn_thread_checker() ends" << endl;
}
//.................................................


void run_is_thread_running() {
	jthread thread(thread_fn);
	jthread threadChecker(is_thread_alive_v2, std::ref(thread));
	thread.join();
}

//void main()
//{
//	run_is_thread_running();
//}