#include <iostream>
using namespace std;

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