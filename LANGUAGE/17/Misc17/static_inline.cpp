#include <iostream>

struct S {

	S() : id{ count++ }
	{
	}

	~S()
	{
		count--;
	}
	int id;
	static inline int count{ 0 }; // declare and initialize count to 0 within the class, c++17

	/*
	  without inline it gives error -
	 'S::count': a static data member with an in - class initializer must have non - volatile const integral type or be specified as 'inline'	Misc17	C : \1_data\office\proj\1_csharp_prac\1_REPO\cplus\cplus_workspace\LANGUAGE\17\Misc17\Misc17.cpp	17
	*/
};