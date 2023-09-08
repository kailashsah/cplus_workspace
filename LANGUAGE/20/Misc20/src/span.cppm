import <iostream>;

using namespace std;

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
	
	span<int> sp = arr;				// dynamic size span
	span <int, size> sp_1 = arr;	// fix size span
	//span <int, 4> sp_2 = arr; //'initializing': cannot convert from 'int [3]' to 'std::span<int,4>'


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
