#include <iostream>
using namespace std;

/*
	1. stringbuf 

	2. provides a dynamic and mutable buffer for text processing operations.
	3. The `str()` method is then used to retrieve the updated string buffer.

*/

#include <sstream>
void run_stringbuf()
{
	std::string str = "string given to stringbuf ctor. ex1 ";
	std::stringbuf buf(str);

	std::cout << buf.str() << std::endl;

	{
		// Appending text to a StringBuffer
		// 
		std::stringbuf buf1;	// empty buffer
		std::ostream os(&buf1); // associate stream buffer to stream
		os << "ex";
		os << "2";
		 
		std::cout << buf1.str() << std::endl; //ex2
	}

}


//int main()
//{
//	run_stringbuf();
//	return 0;	
//}
