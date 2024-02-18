#include <iostream>
using namespace std;
/*
	1. we can simulate the waitForMultipleObjects by passing the boolean value inside the thread function via shared_ptr<>

*/
#include <thread>
std::shared_ptr<bool> val1 = std::make_shared<bool>(0);
std::shared_ptr<bool> val2 = std::make_shared<bool>(0);

void thread_fn(std::shared_ptr<bool> val) {
	*val = true;
	cout << "thread" << endl;
	return;
}

void run_wait_for_multiple_objects()
{
	*val1 = false;
	*val2 = false;
	std::thread tr1(thread_fn, val1);
	std::thread tr2(thread_fn, val2);

	tr1.detach();
	tr2.detach();

	while (!(*val1) || !(*val2)) {
		cout << "wait" << endl;
	};

	cout << "finished" << endl;
}

//int main() {
//
//	run_wait_for_multiple_objects();
//	return 0;
//}