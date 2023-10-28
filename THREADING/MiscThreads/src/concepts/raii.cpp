#include <iostream>
using namespace std;

/*
	1.  RAII (Resource acquisition is initialization) pattern, Another name for this technique is SBRM, short for Scope-Bound Resource Management.


	2. When you want to lock a mutex, you create a local variable of type std::unique_lock passing the mutex as parameter. When the unique_lock is constructed it will lock the mutex, and it gets destructed it will unlock the mutex. More importantly: If a exceptions is thrown, the std::unique_lock destructor will be called and so the mutex will be unlocked.

	3. Examples from the C++ standard library that use RAII are std::string and std::vector.

		Consider this piece of code:

		void fn(const std::string& str)
		{
			std::vector<char> vec;
			for (auto c : str)
				vec.push_back(c);
			// do something
		}
		when you create a vector and you push elements to it, you don't care about allocating and deallocating such elements. The vector uses new to allocate space for its elements on the heap, and delete to free that space. You as a user of vector you don't care about the implementation details and will trust vector not to leak. In this case, the vector is the handle object of its elements.

		Other examples from the standard library that use RAII are std::shared_ptr, std::unique_ptr, and std::lock_guard.

		

*/



