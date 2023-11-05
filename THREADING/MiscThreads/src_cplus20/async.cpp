#include <iostream>
using namespace std;

/*
	1. std::launch::async : the task is executed on a different thread, potentially by creatingand launching it first
		std::launch::deferred : the task is executed on the calling thread the first time its result is requested(lazy evaluation)
	
	2. promise<> - The class template std::promise provides a facility to store a value or an exception that is later acquired asynchronously via a std::future object created by the std::promise object. Note that the std::promise object is meant to be used only once.
		2.1.  Each promise is associated with a shared state, which contains some state information and a result which may be not yet evaluated, evaluated to a value (possibly void) or evaluated to an exception
	3. check section "is_thread_runnng"
*/
