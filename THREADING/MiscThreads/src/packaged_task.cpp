#include <iostream>
using namespace std;

/*
	1. The  std::packaged_task class wraps any Callable objects (function, lambda expression, bind expression, or another function object) so that they can be invoked asynchronously. A packaged_task won’t start on its own, you have to invoke it, As its return value is stored in a shared state that can be called/accessed by  std::future objects.

	2. Need of packaged_task

		The main advantage of a packaged task is that it can link a callable object to a future and that is very important in a flooding environment. For example, if we have an existing function that fetches the data from Database (DB) and returns it. Now there is a need to execute this function in a separate thread. This can be done using:

		std::packaged_task<>
		otherwise, we’ll have to use:

		std::promise<>

		and have to change code but with the help of  std::packaged_task<> its simple and we don’t need to do that.



*/
// Factorial function 
int factorial(int N)
{
    int res = 1;
    for (int i = N; i > 1; i--)
    {
        res *= i;
    }

    cout << "Result is = " <<
        res << "/n";
    return res;
}
#include <deque>
#include <mutex>
#include <future> // packaged_task<>
// packaged task 
std::deque<std::packaged_task<int()> > task_q;
std::mutex mu;
std::condition_variable cond;

void thread_func()
{
    // packaged task 
    std::packaged_task<int()> task;
    {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, []()
            {
                return !task_q.empty();
            });
        task = std::move(task_q.front());
        task_q.pop_front();
    }
    task(); // this stmt returns when task completes
}

// Driver Code 
void run_packaged_task()
{
    std::thread th(thread_func);

    // Create a packaged_task<> that  
    // encapsulated the callback i.e. a function 
    std::packaged_task<int()> task(bind(factorial, 6));

    // Fetch the associated future<>  
    // from packaged_task<> 
    std::future<int> fu = task.get_future();
    {
        std::lock_guard<std::mutex> locker(mu);
        task_q.push_back(std::move(task));
    }

    cond.notify_one();

    // Fetch the result of packaged_task<> 
    cout << fu.get();

    // Join the thread. Its blocking and  
    // returns when thread is finished. 
    th.join();

}

//int main()
//{
//    run_packaged_task();
//}