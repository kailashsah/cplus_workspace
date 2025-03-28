import <iostream>;
using namespace std;
/*
	A span<T> is:

	1. A very lightweight abstraction of a contiguous sequence of values of type T somewhere in memory.
	2. Basically a struct { T * ptr; std::size_t length; } with a bunch of convenience methods.
	3. A non-owning type (i.e. a "reference-type" rather than a "value type"): It never allocates nor deallocates anything and does not keep smart pointers alive.(like a weak pointer)
	
	4. Use span<T> (respectively, span<const T>) instead of a free-standing T* (respectively const T*) when the allocated length or size also matter. So, replace functions like:
			void read_into(int* buffer, size_t buffer_size);
		with:
			void read_into(span<int> buffer);
*/

import <span>;
import <algorithm>;
void run_span(std::span<int> span)
{
	for_each(span.begin(), span.end(),
		[](auto i) { cout << i << " "; }
	);

}

void run_span_2()
{
	constexpr int size = 3;
	int arr[size] = {1,2,3};
	
	//1.
	span<int> sp = arr;				// dynamic size span
	span<int, size> sp_1 = arr;		// fix size span
	//span <int, 4> sp_2 = arr;		//'initializing': cannot convert from 'int [3]' to 'std::span<int,4>'

	//2.
	int* arrp = new int[size]; // int pointer
	span<int> sp_2 = arr;
	//span<double> sp_3 = arr; // 'initializing': cannot convert from 'int [3]' to 'std::span<double,4294967295>'
}

import <vector>;

//int main()
//{
//	vector vec{1,2,3};
//	run_span(vec);
//
//	return 1;
//}
