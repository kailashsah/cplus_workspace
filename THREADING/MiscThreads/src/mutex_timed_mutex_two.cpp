#include <iostream>
using namespace std;

/*
    1. 
*/
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <sstream>
void run_timed_mutex_v2();
//
std::mutex cout_mutex; // control access to std::cout
std::timed_mutex t_mutex;

void job(int id)
{
    using Ms = std::chrono::milliseconds;
    std::ostringstream stream;

    for (int i = 0; i < 3; ++i) { // 3 times try to get the lock by single thread
        if (t_mutex.try_lock_for(Ms(100))) {
            stream << "success ";
            std::this_thread::sleep_for(Ms(100));
            t_mutex.unlock();
        }
        else {
            stream << "failed ";
        }
        std::this_thread::sleep_for(Ms(100)); //  using Ms = std::chrono::milliseconds;
    }

    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "[" << id << "] " << stream.str() << "\n";
}

void run_timed_mutex_v2() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(job, i);
    }

    for (auto& i : threads) {
        i.join();
    }
    /*
        [1] failed success failed
        [2] failed failed success
        [0] success success success
        [3] success failed success
    */
}

//int main()
//{
//    run_timed_mutex_v2();
//}

