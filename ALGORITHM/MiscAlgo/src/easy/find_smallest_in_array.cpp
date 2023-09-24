#include <iostream>
using namespace std;

/*
	Binary search
	if array is sorted. 
*/

int find_samllest(int arr[], int first, int last, int num)
{

	int mid = (first + last) / 2;
	if (mid == last || mid == first)
		return num;

	if (arr[mid] == num)
		return num;

	if (arr[mid] > num)
		num = find_samllest(arr, first, mid, num);
	else if (arr[mid] < num)
		num = find_samllest(arr, mid + 1, last, num);


	return num;
}

void run_find_smallest_in_arr()
{
	//int arr[] = {4,5, 1, 2, 3};
	int arr[] = { 1,2, 3, 4, 5 };
	cout << find_samllest(arr, 0, 4, 4) << endl;
}

//int main()
//{
//	run_find_smallest_in_arr();
//	return 0;
//}