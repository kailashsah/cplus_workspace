#include <iostream>
using namespace std;

/*
	1. std::packaged_task allows us to get the std::future "bounded" to some callable, and then control when and where this callable will be executed without the need of that future object.

		std::async enables the first, but not the second. Namely, it allows us to get the future for some callable, but then, we have no control of its execution without that future object.

	2. https://stackoverflow.com/questions/18143661/what-is-the-difference-between-packaged-task-and-async#:~:text=std%3A%3Apackaged_task%20allows%20us,first%2C%20but%20not%20the%20second.
	
    3. p> Packaged task holds a task [function or function object] and future/promise pair. When the task executes a return statement, it causes set_value(..) on the packaged_task's promise.

        a> Given Future, promise and package task we can create simple tasks without worrying too much about threads [thread is just something we give to run a task].

*/
/*
std::packaged_task allows us to get the std::future "bounded" to some callable, and then control whenand where this callable will be executed without the need of that future object.

std::async enables the first, but not the second.Namely, it allows us to get the future for some callable, but then, we have no control of its execution without that future object.

Practical example
Here is a practical example of a problem that can be solved with std::packaged_task but not with std::async.

Consider you want to implement a thread pool.It consists of a fixed number of worker threadsand a shared queue.But shared queue of what ? std::packaged_task is quite suitable here.
*/
#include <future>
#include <queue>
template <typename T>
class ThreadPool {
public:
    using task_type = std::packaged_task<T()>;

    std::future<T> enqueue(task_type task) {
        // could be passed by reference as well...
        // ...or implemented with perfect forwarding
        std::future<T> res = task.get_future();

        { 
            std::lock_guard<std::mutex> lock(mutex_);
            tasks_.push(std::move(task));
        }
        cv_.notify_one();
        return res;
    }

    void worker() {
        while (true) {  // supposed to be run forever for simplicity
            task_type task;
            { 
                std::unique_lock<std::mutex> lock(mutex_);
                cv_.wait(lock, [this] { 
                    return !this->tasks_.empty(); 
                    });

                task = std::move(tasks_.top());
                tasks_.pop();
            }
            task();
        }
    }
    //... // constructors, destructor,...
private:
    std::vector<std::thread> workers_;
    std::queue<task_type> tasks_;
    std::mutex mutex_;
    std::condition_variable cv_;
};

/*
    Such functionality cannot be implemented with std::async. We need to return an std::future from enqueue().If we called std::async there(even with deferred policy) and return std::future, then we would have no option how to execute the callable in worker().Note that you cannot create multiple futures for the same shared state(futures are non - copyable).
*/
