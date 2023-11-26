#include <iostream>
using namespace std;
/*
	1.

*/
void task_lambda();
void task_bind();
void task_thread();
//
#include <cmath>
#include <functional>
#include <future>
#include <iostream>
#include <thread>

// unique function to avoid disambiguating the std::pow overload set
int get_power(int x, int y) { return static_cast<int> ( std::pow(x, y) ); }

void task_lambda()
{
	std::packaged_task<int(int, int)> task([](int a, int b)
		{
			return static_cast<int>( std::pow(a, b) ); // reinterpret_cast<int> (double) -> compiler error showing conversion not possible
		});
	std::future<int> result = task.get_future();

	task(2, 9); // execution of task will take time here & hold for few momemts

	std::cout << "task_lambda:\t" << result.get() << '\n';
}

void task_bind()
{
	std::packaged_task<int()> task(std::bind(get_power, 2, 11));
	std::future<int> result = task.get_future();

	task();

	std::cout << "task_bind:\t" << result.get() << '\n';
}

void task_thread()
{
	std::packaged_task<int(int, int)> task(get_power);
	std::future<int> result = task.get_future();

	std::thread task_td(std::move(task), 2, 10);
	task_td.join();

	std::cout << "task_thread:\t" << result.get() << '\n';
}

void run_packaged_task_two() {
	task_lambda();
	task_bind();
	task_thread();
	/*
		task_lambda:    512
		task_bind:      2048
		task_thread:    1024
	*/
}

//void main()
//{
//	run_packaged_task_two();
//}