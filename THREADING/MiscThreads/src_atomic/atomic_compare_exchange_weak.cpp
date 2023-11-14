#include <iostream>
using namespace std;

/*
	1. Spurious Failure
		This is due to spurious failure on some platforms where a sequence of instructions (instead of one as on x86) are used to implement it. On such platforms, context switch, reloading of the same address (or cache line) by another thread, etc. can fail the primitive. It’s spurious as it’s not the value of the object (not equal to expected) that fails the operation. Instead, it’s kind of timing issue. On the contrary, the strong version conceptually wraps this around and tries in case of any spurious failure.

	2. Why Bother to Use compare_exchange_weak() and Write the Loop Ourselves? Why Not Compare_exchange_strong()?
		When a compare-and-exchange is in a loop, the weak version will yield better performance on some platforms.

		On x86 (at least currently). the weak and strong version are essentially the same because they both boil down to the single instruction cmpxchg. On some other platforms where compare_exchange_XXX() isn’t implemented atomically (here meaning no single hardware primitive exists), the weak version inside the loop may win the battle because the strong one will have to handle the spurious failures and retry accordingly.

	3. When only compare_exchange_weak() need to be used inside a loop. C++11 also says:

		When a weak compare-and-exchange would require a loop and a strong one would not, the strong one is preferable.

	4. At best, it’s reinventing the wheels and perform the same as compare_exchange_strong().

	5.
		expected = current.load();
		do desired = function(expected);
		while (!current.compare_exchange_weak(expected, desired));
		https://www.codeproject.com/Articles/808305/Understand-std-atomic-compare-exchange-weak-in-Cpl


*/
void run_compare_exchange_weak();
void run_weak_was_error_earlier();
//
// atomic::compare_exchange_weak example:
#include <iostream>       // std::cout
#include <atomic>         // std::atomic
#include <thread>         // std::thread
#include <vector>         // std::vector

// a simple global linked list:
struct Node { int value; Node* next; };
std::atomic<Node*> list_head(nullptr);

void append(int val) {     // append an element to the list
	Node* oldHead = list_head;
	Node* newNode = new Node{ val,oldHead };// put the current value of head into new_node->next

	// what follows is equivalent to: list_head = newNode, but in a thread-safe way:
	// now make new_node the new head, but if the head
	// is no longer what's stored in new_node->next
	// (some other thread must have inserted a node just now)
	// then put that new head into new_node->next and try again
	while (!list_head.compare_exchange_weak(oldHead, newNode))
		newNode->next = oldHead;
}

void run_compare_exchange_weak() {
	// spawn 10 threads to fill the linked list:
	std::vector<std::thread> threads;
	for (int i = 0; i < 10; ++i) {
		threads.push_back(std::thread(append, i));
	}
	for (auto& th : threads)
		th.join();

	// print contents:
	for (Node* it = list_head; it != nullptr; it = it->next)
		std::cout << ' ' << it->value;
	std::cout << '\n';

	// cleanup:
	Node* it;
	while (it = list_head) {
		list_head = it->next;
		delete it;
	}
}

void run_weak_was_error_earlier() {

	// Note: the above use is not thread-safe in at least 
	// GCC prior to 4.8.3 (bug 60272), clang prior to 2014-05-05 (bug 18899)
	// MSVC prior to 2014-03-17 (bug 819819). The following is a workaround:
	//      node<T>* old_head = head.load(std::memory_order_relaxed);
	//      do
	//      {
	//          new_node->next = old_head;
	//      }
	//      while (!head.compare_exchange_weak(old_head, new_node,
	//                                         std::memory_order_release,
	//  
}

//int main()
//{
//
//	run_compare_exchange_weak();
//	return 0;
//}

/*
	Possible output (the order may be different):
	9 8 7 6 5 4 3 2 1 0

*/

