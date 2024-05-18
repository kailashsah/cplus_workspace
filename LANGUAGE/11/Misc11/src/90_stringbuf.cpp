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

void run_read_line_by_line() {

	string text = "12\n34\n56\n67\n89";

	//1. Using stringstreams
	istringstream iss(text);
	string line;
	while (getline(iss, line)) {
		cout << line << '\n';
	}

	//2. iterator approach
	string::iterator line_start, line_end;
	line_start = text.begin();

	while (line_start != text.end()) {
		line_end = find(line_start, text.end(), '\n');
		
		cout << string(line_start, line_end) << '\n';
		if (line_end == text.end())
			break;

		line_start = line_end + 1;
	}
}

//int main()
//{
//	//run_stringbuf();
//	run_read_line_by_line();
//	return 0;	
//}
