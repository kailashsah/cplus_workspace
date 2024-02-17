#include <iostream>
using namespace std;

/*
    1.  shared_lock<> - Locks the associated mutex in shared mode by calling m.lock_shared().
    2.  2. std::shared_mutex mux_ - 
        
        a) if shared_lock <mutex> - gives error 'unlock_shared': is not a member of 'std::mutex' .. bcoz mutex is used instead of shared_mutex
        b) use shared_lock<shared_mutex> or any variant of shared mutexes.
*/
void run_shared_lock_two();
//
#include <chrono>
#include <iostream>
#include <shared_mutex>
#include <syncstream>
#include <thread>

//1.
//std::shared_timed_mutex m;
//2.
std::shared_mutex m;
int g_i = 10;

void read_shared_var(int id)
{
    // both the threads get access to the integer i
    //1. 
    //std::shared_lock<std::shared_timed_mutex> slk(m);
    //2.
    std::shared_lock<std::shared_mutex> slk(m); // OK
    const int ii = g_i; // reads global i

    std::osyncstream(std::cout) << '#' << id << " read i as " << ii << "...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::osyncstream(std::cout) << '#' << id << " woke up..." << std::endl;
}

void run_shared_lock_two() {
    std::thread r1{ read_shared_var, 1 };
    std::thread r2{ read_shared_var, 2 };

    r1.join();
    r2.join();
    /*
        #1 read i as 10...
        #2 read i as 10...
        #1 woke up...
        #2 woke up...
    */
}

//int main()
//{
//    run_shared_lock_two();
//}