#include <iostream>
using namespace std;

/*
	1. You cannot pause a thread in an arbitrary point with C++ facilities. Maybe you can with platform facilities (like, Windows has SuspendThread), but it may not be a good idea (imagine a thread acquires malloc internal lock when paused).

	2. use of	cv.wait()
				cv.notify_one()

	3.
*/

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex> // condition_variable

class TaskManager {
private:
	std::condition_variable cv;
	std::mutex		mtx;
	std::thread		task_thread;
	bool			paused = true;
	bool			finished = false;
	int				counter = 0; // may cause data race, needs atomic<> here
	int				MAX_COUNT = 500000;//INT_MAX; .. INT_MAX is taking too much time

public:
	~TaskManager() {
		if (this->task_thread.joinable()) {
			this->task_thread.join();
		}
	}
	void task() {
		// Finishing condition. ==> counter < this->MAX_COUNT
		while (counter < this->MAX_COUNT) {
			std::unique_lock<std::mutex> ul(this->mtx);
			this->cv.wait(ul, [this] {return (!this->paused); });

			// CORE LOGIC...
			counter++;

		}
		std::cout << "Finished!" << std::endl;
		this->finished = true;
	}

	void start() {
		std::unique_lock<std::mutex> ul(this->mtx);
		this->paused = false;
		task_thread = std::thread([this] {this->task(); });
		cv.notify_one(); // IMP .. required for first time
	}

	void pause() {
		std::unique_lock<std::mutex> ul(this->mtx);
		if (!this->finished) {
			this->paused = true;
			this->cv.notify_one();
		}
	}

	void resume() {
		std::unique_lock<std::mutex> ul(this->mtx);
		if (!this->finished) {
			this->paused = false;
			this->cv.notify_one();
		}
	}

	int getCounter() {
		return this->counter;
	}

};

void run_thread_pause() {
	TaskManager tm;
	std::cout << "counter before start(): " << tm.getCounter() << std::endl;
	tm.start();

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::cout << "counter after 10 ms: " << tm.getCounter() << std::endl;

	tm.pause();
	std::cout << "counter after pause(): " << tm.getCounter() << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::cout << "counter after 10 ms (still paused): " << tm.getCounter() << std::endl;

	tm.resume();
	std::cout << "counter just after resume(): " << tm.getCounter() << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::cout << "counter after 10 ms (resumed state): " << tm.getCounter() << std::endl;

	/*
		counter before start(): 0
		counter after 10 ms:	121098
		counter after pause():	163182
		counter after 10 ms (still paused):		163182
		counter just after resume():			171847
		counter after 10 ms (resumed state):	394747
		Finished!
	*/
}

//void main()
//{
//	run_thread_pause();
//}
