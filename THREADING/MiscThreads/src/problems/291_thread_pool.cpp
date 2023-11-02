#include <iostream>
using namespace std;

/*
	1.

*/

#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <mutex>          // std::mutex
#include <atomic>
#include <chrono>
//
void run_thread_pool();
//void c_trim::launch_threads();
//void c_trim::launch_threads_future()
//int c_trim::wait_first_future();
//int c_trim::wait_first();
//
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#pragma warning(disable:6387)//strout
#pragma warning(disable:26451)
//
using namespace std;
const bool FLAG_IMPRIME = false;
const int MAX_THREADS = 12;
//
mutex mtx;           // mutex for critical section
atomic <bool> th_end[MAX_THREADS];
atomic <int> total_threads_ran;
//
typedef std::chrono::high_resolution_clock t_clock; //SOLO EN WINDOWS
std::chrono::time_point<t_clock> start_time, stop_time;
char null_char;
//
void timer(const char* title = 0, int data_size = 1)
{
	stop_time = t_clock::now();
	double us = (double)chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
	if (title)
		printf("%s time = %7lgms = %7lg MOPs\n", title, (double)us * 1e-3, (double)data_size / us); 
	start_time = t_clock::now();
}

class c_trim
{
	char line[200];
	thread th[MAX_THREADS];
	double th_result[MAX_THREADS];
	int th_index;
	double milliseconds_commanded; // total wait done by 4000 threads
	void hilo(int hindex, int milliseconds, double& milliseconds2)
	{
		sprintf(line, "%i:%ia ", hindex, milliseconds); print_line(line);
		this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
		milliseconds2 = milliseconds * 1000;
		sprintf(line, "%i:%ib ", hindex, milliseconds); print_line(line);
		total_threads_ran++;
		th_end[hindex] = true; // signal thread has ended.
	}
	int wait_first();
	void print_line(char* str)
	{
		if (FLAG_IMPRIME) {
			mtx.lock();
			cout << str;
			mtx.unlock();
		}
	}

public:
	void launch_threads();

	vector <future<void>> futures;
	int wait_first_future();
	void launch_threads_future();//usa future
};

void c_trim::launch_threads()
{
	th_index = 0;
	total_threads_ran = 0;
	milliseconds_commanded = 0;
	double* timeout = new double[MAX_THREADS];
	int i;
	for (i = 0; i < MAX_THREADS; i++) //MAX_THREADS is 12
	{

		th_end[i] = true; // true means thread stopped.
		th_result[i] = timeout[i] = -1;
	}


	for (i = 0; i < 4000; i++)
	{
		// run total 4000 threads
		int milliseconds = 5 + (i % 10) * 2;
		{
			int j = wait_first();
			if (th[j].joinable())
			{
				th[j].join();
				th_result[j] = timeout[j];
			}
			milliseconds_commanded += milliseconds;
			th_end[j] = false; // re-init
			th[j] = thread(&c_trim::hilo, this, j, milliseconds, std::ref(timeout[j]));
			/*
				std::ref(timeout[j]) - show result is returned from the thread & stored in the th_result[], notice it is passed as reference .
			*/
		}
	}
	// wait for last 12 theads to end.
	for (int j = 0; j < MAX_THREADS; j++)
		if (th[j].joinable())
		{
			th[j].join();
			th_result[j] = timeout[j];
		}

	delete[] timeout;
	cout << endl << "Milliseconds commanded to wait=" << milliseconds_commanded << endl;
}

void c_trim::launch_threads_future()
{
	futures.clear();
	futures.resize(MAX_THREADS);

	total_threads_ran = 0;
	milliseconds_commanded = 0;
	double* timeout = new double[MAX_THREADS];
	int i;
	for (i = 0; i < MAX_THREADS; i++)
	{
		th_result[i] = timeout[i] = -1;
	}


	for (i = 0; i < 4000; i++)
	{
		int milliseconds = 5 + (i % 10) * 2;
		{
			int j;
			if (i < MAX_THREADS) j = i;
			else
			{
				j = wait_first_future();
				futures[j].get();
				th_result[j] = timeout[j];
			}
			milliseconds_commanded += milliseconds;
			futures[j] = std::async(std::launch::async, &c_trim::hilo, this, j, milliseconds, std::ref(timeout[j]));
		}
	}
	//Last MAX_THREADS:
	for (int j = 0; j < MAX_THREADS; j++)
	{
		futures[j].get();
		th_result[j] = timeout[j];
	}

	delete[] timeout;
	cout << endl << "Milliseconds commanded to wait=" << milliseconds_commanded << endl;
}

int c_trim::wait_first()
{
	int i;
	while (1)
		for (i = 0; i < MAX_THREADS; i++)
		{
			if (th_end[i] == true)
			{
				return i;
			}
		}
}

//Espera que acabe algun future y da su index
int c_trim::wait_first_future()
{
	int i;
	std::future_status status;
	while (1)
		for (i = 0; i < MAX_THREADS; i++)
		{
			status = futures[i].wait_for(0ms);
			if (status == std::future_status::ready)
				return i;
		}
}

void run_thread_pool() {
	c_trim trim;
	timer();
	trim.launch_threads();
	cout << endl;
	timer("4000 threads using THREAD + ATOMIC:", 4000);
	trim.launch_threads_future();
	cout << endl;
	timer("4000 threads using FUTURE:", 4000);
	cout << endl << "Total threads ran:" << total_threads_ran << endl;
	cout << "=== END ===\n"; (void)getchar();
}

//int main()
//{
//	run_thread_pool();
//}

/*
	Milliseconds commanded to wait=56000

	4000 threads using THREAD+ATOMIC: time = 9885.56ms = 0.000404631 MOPs

	Milliseconds commanded to wait=56000

	4000 tareas using FUTURE: time = 7909.84ms = 0.000505699 MOPs

	Tareas acabadas:4000
	=== END ===

*/