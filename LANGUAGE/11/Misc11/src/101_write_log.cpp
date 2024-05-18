#include <iostream>
using namespace std;


#include <string>
#include <fstream>
#include <exception>
#include <thread>


void WriteDebugLog(string str)
{

	try {
		ofstream out{ "Cef3BrowserLog.txt", ios_base::app };

		out.end;
		out << this_thread::get_id() << " " << str << "\n";
		out.close();
	}
	catch (exception& )
	{


	}
}

	//int main()
	//{
	//	run_version(); // c++98, always prints c++98 when changes to c++14 or c++17 
	//	return 0;	
	//}
