#include <iostream>
using namespace std;

/*
	1. fire & forget issue. Advised always capture the return from the std::async() call.
	2. this issue not there in std::packaged_task or std::promise
	3. https://www.modernescpp.com/index.php/the-special-futures/
	4.

*/
#include <chrono>
#include <future>
#include <iostream>
#include <thread>
/*
	1. The future that is created by std::async, waits in its destructor until its work is done. Another word for waiting is blocking. The future blocks the progress of the program in its destructor. This becomes obvious in case you use fire-and-forget futures.

	2. The program executes two promises in its own thread. The resulting futures are fire-and-forget futures. These futures block in their destructor until the associated promise is done. The result is that the promise will be executed with high probability in that sequence in which you find them in the source code. That is exactly what you see in the output of the program.

	3. I want to stress this point once more. Although I create in the main-thread two promises, which are executed in separate threads, the threads run in sequence one after the other. That is why the thread with the more time-consuming work package (line 12) finishes first. Wow, that was disappointing. Instead of three threads running concurrently, each thread will be executed after another.
*/
void run_future_blocking();
void run_future_non_blocking();
void run_fix();

void run_future_blocking() {
	
	// this version is without the return value capture from async() call
	std::cout << std::endl;
	//1.
	std::async(std::launch::async, [] {
		std::this_thread::sleep_for(std::chrono::seconds(2));// sleep_for(2s) also OK
		std::cout << "first thread" << std::endl;
		});
	// here future waits in ~future() for completion of above async task/work.

	//2.
	std::async(std::launch::async, [] {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "second thread" << std::endl; }
	);
	/*
		1. warning C4858: discarding return value: The result of 'std::async' should be stored in a variable. If the return value is discarded, the temporary 'std::future' is destroyed, waiting for an async result or evaluating a deferred result, thus defeating the purpose of 'std::async'.

		2. here future waits in ~future() for completion of above async task/work. so, it is behaving sequential.
	*/
	

	std::cout << "main thread" << std::endl;
	/*
		first thread
		second thread
		main thread
	*/
}
/*
	1. The key issue is that the by std::async created thread is waiting in its destructor until the associated promise is made, which can not be solved. The problem can only be mitigated. In case you bind the future to a variable, the blocking will take place at the time point when the variable goes out of scope. That is the behavior you can observe in the following example.

	2. Now, the output of the program matches our intuition because the three threads are executed in parallel. The future first  and second  are valid until the end of the main function "}". So, the destructor will perhaps block at this time point. The result is that the threads with the smallest work package are the fastest ones.

*/
void run_future_non_blocking() {

	std::cout << std::endl;

	//1.
	auto first = std::async(std::launch::async, [] {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::cout << "first thread" << std::endl;
		});

	//2.
	auto second = std::async(std::launch::async, [] {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "second thread" << std::endl; }
	);

	std::cout << "main thread" << std::endl;

	/*
		main thread
		second thread
		first thread
	*/

}

/*
	a, for fire-and-forget future, which is not bound to a variable, must be handled carefully.
	b, But this point doesn’t hold for futures, which are created by std::packaged_task or std::promise
*/

void run_fix() {
	using namespace std::literals;

	//1. get a std::future<> by std::async<>();
	std::future<int> BlockingFuture = std::async([]()
		{
			std::this_thread::sleep_for(2s);
			cout << "async" << endl;
			return 1;
		});

	//2. get a std::future<> by packaged_task<>
	std::packaged_task<int()> task([]()
		{
			std::this_thread::sleep_for(1s);
			cout << "packaged_task" << endl;
			return 2;
		}); // NON blocking, so not sequential, it completes first than which starts before.

	std::future<int>	NonBlockingFuture = task.get_future(); // not req
	std::thread         task_thread(std::move(task));

	cout << "BlockingFuture.get(): " << BlockingFuture.get() << std::endl;
	cout << "NonBlockingFuture.get(): " << NonBlockingFuture.get() << std::endl;// not req

	task_thread.join();
	/*
		output --
			BlockingFuture.get(): packaged_task
			async
			1
	*/
}

//void main()
//{
//	run_fix();
//}