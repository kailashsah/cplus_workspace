#include <iostream>
using namespace std;

/*
	1. Objects are stored in a stack during static initialization and have an automatic storage duration, i.e., the object will be destroyed automatically at the end of the scope, 
	2. but during dynamic initialization, objects are stored in a heap and we must manually delete the object after use.

*/
class TryStaticBase
{
	int x;
public:
	TryStaticBase() { x = 4; }
	int getX() { return x; }
};

class B
{
	static TryStaticBase obj1;  // 
public:
	static void start(); // could be with/without static
};

/*
*	If I removed this, it issues unresolved symbol
*/
TryStaticBase B::obj1; // init static var

void B::start()
{
	int x = obj1.getX();
	cout << x;
}


void run_static_object()
{
	B objB;
	objB.start();
	//
}


//int main()
//{
//	run_static_object();
//	return 0;	
//}
