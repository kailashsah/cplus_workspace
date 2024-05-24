// C++ program to implement the
// deep copy
#include <iostream>
using namespace std;

#define SAFE_DELETE(x) if(x) {void** y = (void**)&x; delete x; *y = NULL;}

// Box Class
class box {
private:
	int length;
	int* breadth;
	int height;

public:
	// Constructor
	box()
	{
		cout << "ctor" << endl;
		breadth = new int;
	}

	// Function to set the dimensions
	// of the Box
	void set_dimension(int len, int brea,
		int heig)
	{
		length = len;
		*breadth = brea;
		height = heig;
	}

	// Function to show the dimensions
	// of the Box
	void show_data()
	{
		cout << " Length = " << length
			<< "\n Breadth = " << *breadth
			<< "\n Height = " << height
			<< endl;
	}

	// Parameterized Constructors for
	// for implementing deep copy
	box(box& sample) // copy ctor
	{
		length = sample.length;
		//1.
		breadth = new int; // fix .. allocate memory, box second = first; -> wouldnot call the ctor (IMP)

		//2.
		//breadth = sample.breadth; // crash at destructor
		
		//fix
		*breadth = *(sample.breadth);
		height = sample.height;
	}

	// Destructors
	~box()
	{
		cout << "dtor" << endl;
		if (breadth)
		{
			try {
				//1.
				SAFE_DELETE(breadth);

				//2.
				//delete breadth;
				//breadth = nullptr;
				//note-
				//both are same in this scenario
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
		}

	}
};

void run_shallowcopy() {
	// Object of class first
	box first;

	// Set the dimensions
	first.set_dimension(12, 14, 16);

	// Display the dimensions
	first.show_data();

	// When the data will be copied then
	// all the resources will also get
	// allocated to the new object
	box second = first;

	// Display the dimensions
	second.show_data();
}


//int main()
//{
//	run_shallowcopy();
//	return 0;
//}