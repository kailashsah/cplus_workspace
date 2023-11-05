#include <iostream>
using namespace std;

/*
	1.
*/
#include <iostream>
#include <fstream>
#include <thread>
#include <syncstream>
/*
	1. It provides a mechanism to synchronize threads writing to the same stream. its a thread-safe version of std::ostream.

	2. It provides the guarantee that all output made to the same final destination buffer (std::cout in the examples above) will be free of data races and will not be interleaved or garbled(distorted) in any way, as long as every write to that final destination buffer is made through (possibly different) instances of std::basic_osyncstream.

	3. Writing to a log file or to std::cout from different threads, atomically. it uses single mutex to the std::basic_syncbuf.

	4. osyncstream is a specialization of the form basic_osyncstream<char>, is derived from std::basic_ostream and will typically have just one 'extra' member, of the std::basic_syncbuf class
*/

void worker(const std::size_t startValue, const std::size_t stopValue, std::ostream& os)
{
	for (auto idx{ startValue }; idx < stopValue; ++idx)
	{
		std::osyncstream out{ os };
		out << "thread: " << std::this_thread::get_id() << "; work: " << idx << '\n';
	}
}

void runThreads(std::ostream& os)
{
	std::jthread t1{ worker, 10000, 20000, std::ref(os) };
	std::jthread t2{ worker, 20000, 30000, std::ref(os) };
}

//1.
void run_osyncstream_one()
{
	std::ofstream file{ "out.txt" };
	runThreads(file);
}

//2.
void run_osyncstream_two() {
	{
		std::osyncstream synced_out(std::cout); // synchronized wrapper for std::cout
		synced_out << "Hello, ";
		synced_out << "World!";
		synced_out << std::endl; // flush is noted, but not yet performed
		synced_out << "and more!\n";
	} // characters are transferred and std::cout is flushed.
}

//int main()
//{
//	run_osyncstream_one();
//	run_osyncstream_two();
//	return 1;
//}