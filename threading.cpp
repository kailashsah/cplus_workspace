#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <thread>
//#include <thr/threads.h>
//#define _GLIBCXX_HAS_GTHREADS
#include <mutex>

using namespace std;


namespace threading {

	void print123()
	{

		for (int i=0; i< 5; i++)
		{
			cout << i << setw(4);
		}
			cout << endl;

	}

	mutex m;

	void print(int n, const std::string &str) {
		m.lock();
		std::string msg = std::to_string(n) + " : " + str;
		std::cout << msg << std::endl;
		m.unlock();
	}

	int main() {
		
		std::vector<std::string> s = {
			"Educative.blog",
			"Educative",
			"courses",
			"are great"
		};
		std::vector<std::thread> threads;

		for (int i = 0; i < s.size(); i++) {
			threads.push_back( thread(print, i, s[i]) );
			
		}

		for (auto &th : threads) {
			th.join();
		}
		return 0;
	}
}

/*

int main ()
{
	threading::main();
	getchar();
	return 0;
}
*/


