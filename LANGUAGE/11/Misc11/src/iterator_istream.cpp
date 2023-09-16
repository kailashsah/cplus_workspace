#include <iostream>
using namespace std;

#include <sstream> // istream_iterator

void run_input_stream_iterator()
{
	istringstream str{ "1 2 4" };
	auto itr = istream_iterator<int>(str);
	
	for (; itr != istream_iterator<int>(); ++itr)
	{
		cout << *itr;  
	}
	/*
		output - 124
	*/
}


//int main()
//{
//	run_input_stream_iterator();
//	return 0;	
//}
