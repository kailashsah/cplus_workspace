#include <iostream>
using namespace std;

/*
	1. The class template std::future provides a mechanism to access the result of asynchronous operations:

		An asynchronous operation (created via std::async, std::packaged_task, or std::promise) can provide a std::future object to the creator of that asynchronous operation.
    
    2. The creator of the asynchronous operation can then use a variety of methods to query, wait for, or extract a value from the std::future. These methods may block if the asynchronous operation has not yet provided a value.

    3. When the asynchronous operation is ready to send a result to the creator, it can do so by modifying shared state (e.g. std::promise::set_value) that is linked to the creator's std::future.

*/

#include <future>
#include <iostream>
#include <thread>

void run_future()
{
	//1. future from a packaged_task
	std::packaged_task<int()> task([] { return 7; }); // wrap the function
	std::future<int> f1 = task.get_future(); // get a future
	std::thread th(std::move(task)); // launch on a thread

	//2. future from an async()
	std::future<int> f2 = std::async(std::launch::async, [] { return 8; });

	//3. future from a promise
	std::promise<int> prom;
	std::future<int> f3 = prom.get_future();
	std::thread([&prom] { prom.set_value_at_thread_exit(9); }).detach(); // set_value_at_thread_exit()
    // we safely detach() here bcoz f3.wait() is there in the call downstream. which will wait for the thread to complete. Otherwise, also with detach() it won't crash at caller func returns.

	std::cout << "Waiting..." << std::flush;
	f1.wait();
	f2.wait();
	f3.wait();
	std::cout << "Done!\nResults are: "
		<< f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';
	th.join();

	/*
		Waiting...Done!
		Results are: 7 8 9
	*/
}

void run_future_with_exception()
{
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    std::thread th([&prom]
        {
            try
            {
                // code that may throw
                throw std::runtime_error("Example");
            }
            catch (...)
            {
                try
                {
                    // store anything thrown in the promise
                    prom.set_exception(std::current_exception());
                }
                catch (...) {} // set_exception() may throw too
            }
        });

    try
    {
        std::cout << fut.get();
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception from the thread: " << e.what() << '\n';
    }
    th.join();

    /*
        Exception from the thread: Example
    */
}