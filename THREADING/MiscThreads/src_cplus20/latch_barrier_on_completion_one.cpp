#include <iostream>
using namespace std;

/*
	1. arrive_and_wait() - Atomically decrements the expected count by 1, then blocks at the synchronization point for the current phase until the phase completion step of the current phase is run. Equivalent to wait(arrive())

	2. wait() - blocks at the synchronization point associated with arrival until the phase completion step of the synchronization point's phase is run.

	3. arrive(n=1) - Constructs an arrival_token object associated with the phase synchronization point for the current phase. Then, decrements the expected count by n.

		This function executes atomically. The call to this function strongly happens-before the start of the phase completion step for the current phase.
*/
void run_barrier_on_completion_one();
void run_barrier_on_completion_two();
//
#include <barrier>
#include <mutex>
#include <string>
#include <thread>
#include <syncstream>
#include <vector>
void run_barrier_on_completion_one()
{
	const auto workers = { "Anil", "Busara", "Carl" };



	auto on_completion = []() noexcept
	{
		string s = "finished1";
		this_thread::sleep_for(chrono::seconds(1));
		std::cout << s << endl;
	};

	std::barrier sync_point(std::ssize(workers), on_completion);

	auto work = [&](std::string name)
	{
		std::string product = "  " + name + " worked\n";
		std::osyncstream(std::cout) << product;  // ok, op<< call is atomic
		sync_point.arrive_and_wait(); // calls on_completion function

		product = "  " + name + " cleaned\n";
		std::osyncstream(std::cout) << product;
		sync_point.arrive_and_wait();
	};

	std::cout << "Starting...\n";
	std::vector<std::jthread> threads;
	threads.reserve(std::size(workers));
	for (auto const& worker : workers)
		threads.emplace_back(work, worker);
}
/*
	Starting...
	  Busara worked
	  Carl worked
	  Anil worked
	finished1
	  Carl cleaned
	  Busara cleaned
	  Anil cleaned
	finished1
*/
//...................................

#include <algorithm> // generate_n()
void run_barrier_on_completion_two() {
	// Barrier with a completion function that prints the phase information:
	std::barrier phase(4, [id = 1]() mutable noexcept {
		std::osyncstream(std::cout) << "Phase " << id << " complete.\n";
		id++;
	});

	std::vector<std::jthread> runners;
	std::generate_n(std::back_inserter(runners), 4, [&phase] {
		return std::jthread([&phase] {
			std::osyncstream(std::cout) << "Running phase 1 for thread " << std::this_thread::get_id() << "\n";
			std::this_thread::yield();
			phase.arrive_and_wait();

			std::osyncstream(std::cout) << "Running phase 2 for thread " << std::this_thread::get_id() << "\n";
			std::this_thread::yield();
			phase.arrive_and_wait();
			});
		});

	runners.clear();
	std::osyncstream(std::cout) << "\n";
	/*
		Running phase 1 for thread 5668
		Running phase 1 for thread 23584
		Running phase 1 for thread 41528
		Running phase 1 for thread 4700
		Phase 1 complete.
		Running phase 2 for thread 41528
		Running phase 2 for thread 23584
		Running phase 2 for thread 5668
		Running phase 2 for thread 4700
		Phase 2 complete.
	*/
}

//int main() {
//	//run_barrier_on_completion_one();
//	run_barrier_on_completion_two();
//}

