#include <iostream>
using namespace std;

/*
	1. Atomic types ensure any read or write operation synchronizes as part of multi-thread operations, (i.e. using these types in std::thread).

		They work well on any type that is trivially copyable types which means it has at least one eligible copy constructor, move constructor, copy assignment operator, or move assignment operator and has non-deleted trivial destructor.

	2.  two atomic operations that can be used with std::atomic types,  are atomic load() and store() operations.
		Atomic types and operations provide a way of writing multi-threaded applications without using locks.

	3. atomic operations are free of data races. atomic operations, i.e. load, store, operator=, wait, exchange, is_lock_free.
		int *p = std::atomic_load(&ptr);
		std::atomic_store(&x, y); // x is written

	4. default memory order - T load( std::memory_order order = std::memory_order_seq_cst ) const noexcept;
		Using load with memory order specifies how memory accesses are to be ordered in atomic load operation. This memory order types are defined in atomic library, here are permitted memory orders for atomic load,

		memory_order_relaxed
		memory_order_consume
		memory_order_acquire
		memory_order_seq_cst

	5. I purposefully made a mistake that some threads access/modify the object with std::memory_order_relaxed, some with std::memory_order_release, std::memory_order_acquire, and std::memory_order_acq_rel and some with std::memory_order_seque_cst. Does C++ standard say anything about the expected benavior?

		x86-64 has very strong memory guarantees, so your stuff might be slower but it will (probably) still work

*/



