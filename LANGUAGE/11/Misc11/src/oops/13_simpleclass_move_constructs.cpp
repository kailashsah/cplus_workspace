#include <iostream>
using namespace std;
/*
	1. demo for move copy ctor & move assignment operator
*/

class MoveDemo {
	int* mem = new int(2);
public:
	MoveDemo() {
		cout << "constructor\n";
	}
	~MoveDemo() {
		cout << "destructor\n";
	}
	MoveDemo(const MoveDemo& obj) {
		cout << "copy constructor\n";
		delete mem;
		mem = new int(*(obj.mem));

	}

	MoveDemo& operator=(const MoveDemo& obj)
	{
		cout << "assignment op \n";
		if (this != &obj)
		{
			delete mem;
			mem = new int(*(obj.mem)); // deep copy
		}

		return *this;
	}

	MoveDemo(MoveDemo&& obj)
	{
		cout << "move copy \n";
		mem = obj.mem;
		obj.mem = nullptr;
	}

	MoveDemo& operator=(MoveDemo&& obj)
	{
		cout << "move assign \n";
		if (&obj != this)
		{
			delete mem;		// free existing resource
			mem = obj.mem;	// steal the ptr
			obj.mem = nullptr; // null out the resource
		}
		return *this;
	}



};
void runDemoMove()
{
	cout << "<<<< \n";
	{
		MoveDemo a;

		MoveDemo b = a; // copy
		b = a; // assign

	}
	cout << ">>>> \n";
	{
		MoveDemo a;
		// use std::move() to cast the source object to an rvalue reference.
		MoveDemo c = move(a);
		c = move(a);
	}
	/*
		starts ...
		<<<<
		constructor
		copy constructor
		assignment op
		destructor
		destructor
		>>>>
		constructor
		move copy
		move assign
		destructor
		destructor
	*/
}

//int main()
//{
//	std::cout << "starts ...\n";
//
//	runDemoMove();
//
//}
