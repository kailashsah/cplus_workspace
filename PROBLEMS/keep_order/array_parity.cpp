#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
void sortArrayByParity(vector<int> arr )
{
	int count =  arr.size();
	for (int i =0; i< count; i++)
	{
		if (arr[i] % 2 != 0)
		{
			swap(arr[i], arr[count-1] );
		}

	}

	for (int n : arr)
	{
		cout << n << setw(5);
	}


}

//int main()
//{
//	vector<int> arr = {2,1,4,5,6};
//	int count = arr.size();
//	for (int i = 0; i < count; i++)
//	{
//		cout << arr[i];
//		if(i != count-1)
//			cout << setw(5);
//	}
//	cout << endl; cout << flush;
//	sortArrayByParity(arr);
//	//cout << setw(10) << 'c';
//	return 0;
//}
//
