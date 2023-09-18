#include <iostream>
#include <vector>
#include <array>
using namespace std;


void run_fill()
{
	int arr[100];
	fill(begin(arr), end(arr), 3); // fill_n till specified lenght as n, fill goes till end
	copy(begin(arr), end(arr), ostream_iterator<int>(cout, " ")); // prints 3 3 3 ....
	cout << endl;
}

//int main()
//{
//	run_fill();
//	return 0;	
//}
