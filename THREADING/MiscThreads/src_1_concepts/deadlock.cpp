#include <iostream>
using namespace std;

/*
	1. A deadlock is a situation where a set of processes are blocked because each process is holding a resource and waiting for another resource acquired by some other process

*/
#include <mutex>
#include <syncstream> // osyncstream
void print(string log) {
    //1.
    //cout << log << endl;

    //2.
    osyncstream ost{ cout };
    ost << log << endl;
}

void run_deadlock()
{
    // for fix - see section "lock.cpp" -> std::lock(foo, bar); 
    std::mutex m1;
    std::mutex m2;

    auto f1 = [&m1, &m2]() {
        print("thread 1 called ");
        std::lock_guard<std::mutex> lg1(m1);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::lock_guard<std::mutex> lg2(m2);
        print("thread 1 finished ");
    };

    auto f2 = [&m1, &m2]() {
        print("thread 2 called ");
        std::lock_guard<std::mutex> lg1(m2); // if same order of mutex kept like m1 then m2 -> then it won't cause deadlock
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::lock_guard<std::mutex> lg2(m1);
        print("thread 2 finished ");
    };

    std::thread thread1([&f1, &f2]() {
        f1();
        });

    std::thread thread2([&f1, &f2]() {
        f2();
        });
    thread1.join();
    thread2.join();
}

//void main()
//{
//    run_deadlock();
//}

/*
    thread 1 called thread 2 called
    prints  "cout", even "endl" is not captured in once interupped by other thread.

*/