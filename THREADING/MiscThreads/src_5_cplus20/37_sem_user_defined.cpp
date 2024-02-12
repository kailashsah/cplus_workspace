#include <iostream>
using namespace std;

/*
	1.  https://devtut.github.io/cpp/semaphore.html#semaphore-c-11

*/

#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    Semaphore(int count_ = 0)
        : count(count_)
    {
    }

    inline void notify(int tid) {
        std::unique_lock<std::mutex> lock(mtx);
        count++;
        cout << "thread " << tid << " notify " << count << endl;
        //notify the waiting thread
        cv.notify_one();
    }
    inline void wait(int tid) {
        std::unique_lock<std::mutex> lock(mtx);
        while (count == 0) {
            cout << "thread " << tid << " wait" << endl;
            //wait on the mutex until notify is called
            cv.wait(lock);
            cout << "thread " << tid << " run " << count <<endl;
        }
        count--;
    }
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};

void run_semaphore_user_created() {
    Semaphore sem(1);

    // wait threads - similar to reading resources.
    thread s1([&]() {
        while (true) {
            this_thread::sleep_for(std::chrono::seconds(5));
            sem.wait(1);
        }
        });
    thread s2([&]() {
        while (true) {
            sem.wait(2);
        }
        });
    thread s3([&]() {
        while (true) {
            this_thread::sleep_for(std::chrono::milliseconds(600));
            sem.wait(3);
        }
        });

    // notify thread - similar to writing resources
    thread s4([&]() {
        while (true) {
            this_thread::sleep_for(std::chrono::seconds(5));
            sem.notify(4);
        }
        });


    s1.join();
    s2.join();
    s3.join();
    s4.join();
}

//int main()
//{
//    run_semaphore_user_created();
//
//}

/*
thread 2 wait
thread 3 wait
thread 1 wait
thread 4 notify
thread 2 run
thread 2 wait
thread 4 notify
thread 3 run
thread 3 wait
thread 4 notify
thread 1 run
thread 1 wait
thread 4 notify
thread 2 run
thread 2 wait
thread 4 notify
thread 3 run
thread 3 wait
thread 4 notify
thread 1 run
thread 1 wait
thread 4 notify
thread 2 run
thread 2 wait
thread 4 notify
thread 3 run
thread 3 wait
*/