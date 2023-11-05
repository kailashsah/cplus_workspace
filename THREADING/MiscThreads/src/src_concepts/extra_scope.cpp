#include <iostream>
using namespace std;

/*
	1. writing code in brace within functions.
		{
			...
		}
	
	2. In situations when your program does not take advantage of the nested scope created by curly braces, because it does declare any new variables in that scope, the compiler does not insert any additional code to handle the new scope.
		In general, adding a nested scope may change the timing of work to be done, while the total amount of work would remain the same.
	
	3. there would be no penalty for introducing local variables with trivial destructors into a nested scope.

	4. However, adding unnecessary scope may decrease readability of your code. In this case, readability is strictly subjective, so if you like the additional "scope", you can use it penalty-free.
	
	6. The extra scopes may speed things up. (However, the effect is so slight that you should not bother!)

		You see, within a function, the compiler has full control over all the variables the function uses. It will not push some extra variables on the stack where you declare them, and pop them off when they go out of scope. Instead, it will create a stack frame with sufficient space to hold all the local variables that you need. Your compiler is generally smart enough to reuse the space within this stack frame: When one int goes out of scope before another int gets declared, that second int may reuse the slot of the first in the stack frame.

		So, when you reduce the scopes of your local variables, you allow the compiler to reuse more slots in the stack frame. This reduces the overall size of your stack, and the distances by which the stack grows/shrinks. This in turn leads to better cache usage, and thus to better performance.

		Nevertheless, the impact of this effect is slight, so you should generally ignore it and just write the most readable code you can.
*/



