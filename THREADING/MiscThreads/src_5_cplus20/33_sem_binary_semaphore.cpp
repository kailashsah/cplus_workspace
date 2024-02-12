#include <iostream>
using namespace std;

/*
	1. std::binary_semaphore

*/
#include <iostream>
#include <semaphore>
#include <thread>
#include <vector>

std::vector<int> myVec{};

//std::counting_semaphore<1> prepareSignal(0);              // (1)
std::binary_semaphore prepareSignal(0);

void prepareWork() {

    myVec.insert(myVec.end(), { 0, 1, 0, 3 });
    std::cout << "Sender: Data prepared." << '\n';
    prepareSignal.release();                              // (2)
}

void completeWork() {

    std::cout << "Waiter: Waiting for data." << '\n';
    prepareSignal.acquire();                              // (3)
    myVec[2] = 2;
    std::cout << "Waiter: Complete the work." << '\n';
    for (auto i : myVec) std::cout << i << " ";
    std::cout << '\n';

}
void run_binary_semaphore() {
  std::cout << '\n';

    std::thread t1(prepareWork);
    std::thread t2(completeWork);

    t1.join();
    t2.join();

    std::cout << '\n';
}
/*
    1. The std::counting_semaphore prepareSignal (1) can have the values 0 or 1. The concrete example initializes it with 0 (line 1). This means that the call prepareSignal.release() sets the value to 1 (line 2) and unblocks the call prepareSignal.acquire() (line 3)
*/

//int main() {
//
//    run_binary_semaphore();
//
//}

/*
    Sender: Data prepared.
    Waiter: Waiting for data.
    Waiter: Complete the work.
    0 1 2 3

*/