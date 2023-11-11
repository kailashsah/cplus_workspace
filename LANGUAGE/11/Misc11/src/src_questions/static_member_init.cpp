#include <iostream>
using namespace std;
/*
	1. what happens when we remove default contstructor
	2. 
*/
class Rectt {
public:
	int a;
	int width;
	char* p;
public:
	//Rectt() = delete;		// (2)
	//Rectt(int){}			// (3)	

	/*
		1. if we only create "Rectt(int){}" parameterized ctor, code would not binds to default ctor, seems it got deleted by default
		2. So, it is required to have Rectt() first & then any ctor like Rectt(int)
		3. without any ctor defined, call of Rectt() binds fine.
	*/
};

class Static_ex {

public:
	static Rectt rect;
	static int a;
};
int Static_ex::a;
Rectt Static_ex::rect;		// (1) //rect will be default constructed 
							// 'Rectt::Rectt(void)': attempting to reference a deleted function

//Rectt Static_ex::rect =  Rectt(1); // (3) //OK

void run_static_ex() {
	Static_ex obj;
	cout << obj.rect.a << " " << obj.rect.width;
	cout << obj.a;
}

//int main()
//{
//	run_static_ex();
//	return 0;
//}
