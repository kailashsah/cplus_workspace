#include <iostream>
using namespace std;

/*
	1. https://codereview.stackexchange.com/questions/255959/c17-multi-threaded-thread-pauser

*/


#include <condition_variable>
#include <mutex>
class ThreadPause {
public:
	explicit ThreadPause(bool paused = false);
	[[nodiscard]]
	bool is_paused() const;
	void wait();
	void pause();
	void resume();
private:
	bool m_paused;
	std::mutex m_mutex;
	std::condition_variable m_cv;
};


ThreadPause::ThreadPause(bool paused) : m_paused(paused) {

}

bool ThreadPause::is_paused() const {
	return m_paused;
}

void ThreadPause::wait() {
	while (is_paused()) {
		std::unique_lock<std::mutex> lock(m_mutex);
		//need the condition in here in case of spurious wake up, 
		//wont exit condition unless condition true
		m_cv.wait(lock, [&paused = m_paused] {return !paused; });
	}
}

void ThreadPause::pause() {
	cout << "thread paused" << endl;
	//lock around the variable so with can modify it
	std::unique_lock<std::mutex> lock(m_mutex);
	m_paused = true;
}

void ThreadPause::resume() {
	cout << "thread resumed" << endl;
	//lock around the variable so with can modify it
	std::unique_lock<std::mutex> lock(m_mutex);
	m_paused = false;
	//unlock to stop threads from immediately locking when notify is called.
	lock.unlock();
	m_cv.notify_all();
}

#include <vector>
void run_pause_multithreader() {
	using namespace std::chrono_literals;

	std::size_t thread_count = 10;
	std::atomic<bool> exit_threads(false);
	ThreadPause thread_pause;
	std::vector<int> increments(thread_count, 0);

	auto thread_function = [](
		std::atomic<bool>& exit_threads,
		ThreadPause& thread_pause,
		int& increment)
	{
		while (!(exit_threads.load())) 
		{
			thread_pause.wait();
			//... your work would normally go here
			increment += 10;
		}
	};

	std::vector<std::thread> threads;
	for (std::size_t i = 0; i < thread_count; ++i) {
		threads.emplace_back(thread_function,
			std::ref(exit_threads),
			std::ref(thread_pause),
			std::ref(increments[i]));
	}

	std::this_thread::sleep_for(100ms);
	thread_pause.pause();

	std::this_thread::sleep_for(100ms);
	std::cout << "Current values for increments: \n";
	for (auto increment : increments) {
		std::cout << increment << "\n";
	}

	std::this_thread::sleep_for(100ms);
	std::cout << "Pause values for increments: (after wait for 100ms, thread still in paused state ) \n";
	for (auto increment : increments) {
		std::cout << increment << "\n";
	}
	thread_pause.resume();
	std::this_thread::sleep_for(100ms);

	thread_pause.pause();
	std::this_thread::sleep_for(100ms);

	std::cout << "Resume values for increments: \n";
	for (auto increment : increments) {
		std::cout << increment << "\n";
	}

	thread_pause.resume();
	exit_threads.store(true);

	for (auto& thread : threads) {
		thread.join();
	}
	std::cout << "Threads Joined!\n";
}

//int main() {
//
//	run_pause_multithreader();
//	return 0;
//}

/*
	thread paused
	Current values for increments:
	3197390
	2849230
	4658020
	2417130
	2384830
	2288520
	2505920
	2275280
	2306440
	2187540
	Pause values for increments: (after wait for 100ms, thread still in paused state )
	3197390
	2849230
	4658020
	2417130
	2384830
	2288520
	2505920
	2275280
	2306440
	2187540
	thread resumed
	thread paused
	Resume values for increments:
	16485200
	17551420
	16091530
	16957040
	14311900
	14389780
	13524020
	14586620
	14289520
	13049040
	thread resumed
	Threads Joined!
*/