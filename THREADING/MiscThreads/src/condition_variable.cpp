#include <iostream>
using namespace std;
/*
	1. https://www.todaysoftmag.com/article/753/multithreading-in-c-11-standard-ii

	2. ex. if one thread is preparing data & other thread is processing that data. these both thread should be in sync by condition variable, which gives us wait() facility.

	3. one wants a thread to wait until an event occurs or until a condition becomes true.
		basically, it is a signaling facility

	4. notify_all() - If there are ten threads blocked on the condition variable, for example, notify_one() will unblock only one thread(whose chance comes first), while notify_all() will unblock them all.

	5. "wait_for()" waits for a specified amount of time and wait_until() waits until a specified point in time

		5.1 A time_point has an associated clock, and that clock is what's used to determine if the appropriate time has come. That means that clock adjustments are taken into account by the wait_until function.
		5.2 wait_until(..., system_clock::now() + std::chrono::seconds(10)) could end up waiting an hour and 10 seconds if the clock happens to be adjusted back by an hour before the wait is up.

	6. Two kinds of wait
		Wait for an object to be in a signaled state	-> use notify()
		Wait until a timeout elapses					-> use wait_for() or wait_until()

	7. order of execution - see at bottom

*/
#include <thread> // std::this_thread, thread class
#include <mutex> // lock_guard<>
#include <queue>
#include <algorithm>
#include <numeric> // iota()
//
void run_condition_variable();
void data_preparation_thread();
void data_processing_thread();
//
std::mutex mutexv;
std::queue<string> buffer;
std::condition_variable buffer_cond;
using  buffer_data = string;
vector<int> vec(50);
int countt{};
const int max_count{ 50 };

#include <syncstream>
void process(buffer_data data) {
	osyncstream os{ cout };
	os << "process data " << data << endl;
}

bool is_last_data_entry(std::queue<string> buffer) {
	return buffer.empty() && countt > max_count;
}

bool  has_data_to_prepare() {
	if (countt > max_count) // 49
		return false;
	return true;
}

#include <sstream> // osyncstream
buffer_data prepare_data() {
	stringstream ss;
	if (countt < max_count)
		ss << vec[countt];
	/* if (countt > 48)
		 countt = 0;

	 else*/
	countt++;
	buffer_data s;
	ss >> s;
	return s;

}

void data_preparation_thread()
{
	while (has_data_to_prepare())         //--  (1)    
	{
		buffer_data data = prepare_data();
		std::lock_guard<mutex> lock(mutexv);  //--  (2) 
		buffer.push(data);
		osyncstream os{ cout };
		os << "inserted : " << data << endl;
		buffer_cond.notify_one();                 //-- (3)  
	}
}

void data_processing_thread()
{
	while (true)
	{
		std::unique_lock lock(mutexv);              //-- (4)  
		buffer_cond.wait(lock, [] {return !buffer.empty(); });    //-- (5)   // has callable predicate
		buffer_data data = buffer.front();
		buffer.pop();
		lock.unlock();                                         //-- (6)   
		process(data);
		if (is_last_data_entry(buffer))
			break;
	}
}

void run_condition_variable() {

	thread thread_dataProcess(data_processing_thread);
	thread thread_dataPrepare(data_preparation_thread);

	thread_dataPrepare.join();
	thread_dataProcess.join();
}

//int main()
//{
//	iota(vec.begin(), vec.end(), 0);
//	run_condition_variable();
//	return 1;
//}

/*
	1. mutex together with a condition variable and a predicate boolean. In pseudo-code:

	To block:

		Acquire the mutex.

		While the predicate is false, block on the condition variable.

		If you want to re-arm here, set the predicate to false.

		Release the mutex.

	To release:

		Acquire the mutex.

		Set the predicate to true.

		Signal the condition variable.

		Release the mutex.

	To rearm:

		Acquire the mutex.

		Set the predicate to false.

		Release the mutex.

*/
