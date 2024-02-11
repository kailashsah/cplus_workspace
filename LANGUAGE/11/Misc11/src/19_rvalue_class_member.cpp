#include <iostream>
#include <iomanip>
using namespace std;
/*
	1. Demonstrate how to call move ctor & move assignment
	2. 

*/
class EmptyClass
{
	int i;
	int y;
public:
	EmptyClass() { cout << "default ctor " << endl << endl; };
	EmptyClass(int i) {
		cout << "ctor 1 param (EmptyClass(int i))" << endl << endl;
	}
	EmptyClass(int i, int y) : i{ i } {
		cout << "ctor 2 param (EmptyClass(int i, int y))" << endl << endl;
	}

	EmptyClass(const EmptyClass&) {
		cout << "copy ctor (EmptyClass(const EmptyClass&))" << endl << endl;
	}

	EmptyClass(EmptyClass&&) {
		cout << "move ctor (EmptyClass(EmptyClass&&))" << endl << endl; // setfill('@')
	}

	EmptyClass& operator=(EmptyClass&&) {

		cout << "move assignment (EmptyClass& operator=(EmptyClass&&))" << endl << endl;
		return *this;
	}
	EmptyClass& operator=(const EmptyClass&) {

		cout << "assignment (EmptyClass& operator=(const EmptyClass&))" << endl << endl;
		return *this;
	}
	EmptyClass(initializer_list<int>) {
		cout << "initializer list (EmptyClass(initializer_list<int>))" << endl << endl;
	}

};

void run_class_members()
{
	const int width = 45;
	//setiosflags(ios::left);
	//setw(width);
	cout << right << setw(width) << "EmptyClass objOne;	";// 'left' for -> left aligned else default right aligned
	EmptyClass objOne;			// EmptyClass() 

	cout << setw(width) << "EmptyClass objTwo(1);	";
	EmptyClass objTwo(1);		// EmptyClass(int i)

	cout << setw(width) << "EmptyClass objThree(1, 2);	";
	EmptyClass objThree(1, 2);	// EmptyClass(int i, int y)

	cout << setw(width) << "EmptyClass objFour(objThree)	";
	EmptyClass objFour(objThree);// EmptyClass(const EmptyClass&)

	cout << setw(width) << "EmptyClass objMove = std::move(objFour);	";
	EmptyClass objMove = std::move(objFour); // EmptyClass(EmptyClass&&)  (IMP)  move ctor

	cout << setw(width) << "EmptyClass objFive = objFour;	";
	EmptyClass objFive = objFour; // EmptyClass(const EmptyClass&) // copy ctor

	cout << setw(width) << "objFive = objFour;	";
	objFive = objFour; // EmptyClass& operator=(const EmptyClass&)

	cout << setw(width) << "objFive = move(objFour);	";
	objFive = move(objFour); // EmptyClass& operator=(EmptyClass&&) (IMP) // move assignment

	cout << setw(width) << "EmptyClass objSix{ 1,2 }; ";
	EmptyClass objSix{ 1,2,4,5 }; // EmptyClass(initializer_list<int>)

}

//int main()
//{
//	run_class_members();
//	return 0;
//}
