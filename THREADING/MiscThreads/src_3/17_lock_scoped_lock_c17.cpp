#include <iostream>
/*
	1. c++17. The class scoped_lock is a mutex wrapper that provides a convenient RAII-style mechanism for owning zero or more mutexes for the duration of a scoped block.

		When a scoped_lock object is created, it attempts to take ownership of the mutexes it is given. When control leaves the scope in which the scoped_lock object was created, the scoped_lock is destructed and the mutexes are released. If several mutexes are given, deadlock avoidance algorithm is used as if by std::lock().

	2. The existence of std::scoped_lock means that most of the cases where you would have used std::lock prior to c++17 can now be written using std::scoped_lock, with less potential for mistakes, which can only be a good thing!

	3. ex. 
		friend void swap(X& lhs, X& rhs)
		{
			if (&lhs == &rhs)
				return;
			std::scoped_lock guard(lhs.m, rhs.m);
			swap(lhs.some_detail, rhs.some_detail);
		}
*/

using namespace std;
#include <mutex> // scoped_lock

//2.
#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
using namespace std::chrono_literals;

struct Employee
{
	std::vector<std::string> lunch_partners;
	std::string id;
	std::mutex m;
	Employee(std::string id) : id(id) {}
	std::string partners() const
	{
		std::string ret = "Employee " + id + " has lunch partners: ";
		for (const auto& partner : lunch_partners)
			ret += partner + " ";
		return ret;
	}
};

void send_mail(Employee&, Employee&)
{
	// simulate a time-consuming messaging operation
	std::this_thread::sleep_for(1s);
}

void assign_lunch_partner(Employee& e1, Employee& e2)
{
	static std::mutex io_mutex;
	{
		std::lock_guard<std::mutex> lk(io_mutex);
		std::cout << e1.id << " and " << e2.id << " are waiting for locks" << std::endl;
	}

	{
		// use std::scoped_lock to acquire two locks without worrying about
		// other calls to assign_lunch_partner deadlocking us
		// and it also provides a convenient RAII-style mechanism

		std::scoped_lock lock(e1.m, e2.m);

		{
			std::lock_guard<std::mutex> lk(io_mutex);
			std::cout << e1.id << " and " << e2.id << " got locks" << std::endl;
		}
		e1.lunch_partners.push_back(e2.id);
		e2.lunch_partners.push_back(e1.id);
	}

	send_mail(e1, e2);
	send_mail(e2, e1);
}

void run_scoped_lock()
{
	mutex mtx;
	//1.
	scoped_lock{ mtx }; // c++17 // which constructs a prvalue object that is immediately destroyed) // not advised

	//2.
	Employee alice("Alice"), bob("Bob"), christina("Christina"), dave("Dave");

	// assign in parallel threads because mailing users about lunch assignments
	// takes a long time
	std::vector<std::thread> threads;
	threads.emplace_back(assign_lunch_partner, std::ref(alice), std::ref(bob));
	threads.emplace_back(assign_lunch_partner, std::ref(christina), std::ref(bob));
	threads.emplace_back(assign_lunch_partner, std::ref(christina), std::ref(alice));
	threads.emplace_back(assign_lunch_partner, std::ref(dave), std::ref(bob));

	for (auto& thread : threads)
		thread.join();
	std::cout << alice.partners() << '\n' << bob.partners() << '\n'
		<< christina.partners() << '\n' << dave.partners() << '\n';

	/*
		Alice and Bob are waiting for locks
		Alice and Bob got locks
		Christina and Bob are waiting for locks
		Christina and Alice are waiting for locks
		Dave and Bob are waiting for locks
		Dave and Bob got locks
		Christina and Alice got locks
		Christina and Bob got locks
		//
		Employee Alice has lunch partners: Bob Christina
		Employee Bob has lunch partners: Alice Dave Christina
		Employee Christina has lunch partners: Alice Bob
		Employee Dave has lunch partners: Bob
	*/
}


//int main()
//{
//    run_scoped_lock();
//    return 1;
//}

