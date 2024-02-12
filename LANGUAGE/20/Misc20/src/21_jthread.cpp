#include <iostream>
using namespace std;

/*
	1. std::thread's destructor would terminate the program if you didn't join() or detach() it manually beforehand. This led to tons of bugs, as people would expect it to join on destruction.

	jthread fixes this; it joins on destruction by default (hence the name: "joining thread"). It also supports a mechanism to ask a thread to halt execution, though there is no enforcement of this.
*/

void run_jthread()
{

}

