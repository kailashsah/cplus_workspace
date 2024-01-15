#include <iostream>
#include <vector>
#include <queue>

using namespace std;
/*
	1. Stack uses an encapsulated object of either vector or deque (by default) or list (sequential container class) as its underlying container, providing a specific set of member functions to access its elements. 

*/

#include <stack>
void run_stack() {
    stack<int> stack;
    stack.push(21);// The values pushed in the stack should be of the same data which is written during declaration of stack
    stack.push(22);
    stack.push(24);
    stack.push(25);
    int num = 0;
    stack.push(num);

    stack.top(); 

    stack.pop();
    stack.pop();
    stack.pop();

    while (!stack.empty()) {
        cout << stack.top() << " ";
        stack.pop();
    }

}


//int main()
//{
//	run_stack();
//	return 0;
//}

