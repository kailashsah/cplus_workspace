#include <iostream>
using namespace std;


namespace pointers {
	
	void func3()
	{
		char* p = "Kailash";
		char* const abc = "abc"; // pointer to const value 
		//abc = p;  // compilation err
		*abc = 'a'; // compilation err

		strcpy(abc, "rajeev"); // compilation err
	}

	void func2()
	{
		char* p = "Kailash";


		const char* xyz = "xyz"; // const ponter to value 
		xyz = p;	// don't compile
		//*xyz = 'a'; // 
		//strcpy(xyz, "rajeev"); // compile, run fine

		cout << *xyz;

	}
	void func()
	{
		
		int* ptr1 = new int; //
		int* ptr2 = new int; //
		int* ptr3 = new int; //
		//ptr3 = ptr1 + ptr2;	 // compilation error (right)
		*ptr3 = 10;

		/*
		int* ptr;
		*ptr = 10; // uninitialized local variable 'ptr' used
		cout << *ptr; // compilation error (wrong)
		
		*/


	}

	int main()
	{
		cout << "inside pointers" << endl;

		//func();
		func2();
		return 0;
	}
}


/*

int main()
{
	pointers::main();
	getchar();
	return 0;
}
*/
