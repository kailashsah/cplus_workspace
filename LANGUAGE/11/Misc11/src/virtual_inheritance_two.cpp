#include <iostream>
using namespace std;


class storable
{
public:
	storable() {}
	~storable() {}
	virtual void read() = 0;
	virtual void write() {}
};


class transmitter : public virtual storable
{
	void write() {}
};

class reciever : public virtual storable
{
public:
	//reciever() {}
	//virtual ~reciever() {}
	void write() {}
	void read() {}
};



void run_virtual_inheritance_two()
{
	// 1.
	//transmitter trans;
	/*
		object of abstract type is not allowed, 'void storable::read(void)' has no overrider.
		if this method is givne, void read() {} -- compiler is OK

	*/ 

	// 2.
	reciever rec;
}

//int main()
//{
//	run_virtual_inheritance_two();
//	return 0;	
//}
