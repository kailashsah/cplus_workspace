#include <iostream>
using namespace std;
/*
	1. Given an array arr[] of n integers, construct a Product Array prod[] (of the same size) such that prod[i] is equal to the product of all the elements of arr[] except arr[i].  
	2. https://www.geeksforgeeks.org/a-product-array-puzzle/ 

*/

void productArray(int arr[], int n)
{
	// Base case
	if (n == 1) {
		cout << 0;
		return;
	}
	/* Allocate memory for temporary arrays left[] and right[] */
	int* left = new int[sizeof(int) * n];
	int* right = new int[sizeof(int) * n];

	/* Allocate memory for the product array */
	int* prod = new int[sizeof(int) * n];

	int i, j;

	/* Left most element of left array is always 1 */
	left[0] = 1;

	/* Right most element of right array is always 1 */
	right[n - 1] = 1;

	cout << "Construct the left array" << endl;
	for (i = 1; i < n; i++)
	{
		left[i] = arr[i - 1] * left[i - 1];
		//cout << left[i] << ",";
	}
	cout << endl;
	
	// print left
	cout << endl;
	for (i = 0; i < n; i++)
		cout << left[i] << " ";
	cout << endl;

	cout << "Construct the right array" << endl;	
	for (j = n - 2; j >= 0; j--)
	{
		right[j] = arr[j + 1] * right[j + 1];
		
	}
	// print right
	cout << endl;	
	for (i = 0; i < n; i++)
		cout << right[i] << " ";

	cout << endl;
	/* Construct the product array using left[] and right[] */
	for (i = 0; i < n; i++)
		prod[i] = left[i] * right[i];

	cout << endl;
	/* print the constructed prod array */
	for (i = 0; i < n; i++)
		cout << prod[i] << " ";


	return;
}
/*
	output -- 
	The product array is { 10, 3, 5, 6, 2 } :
	Construct the left array
	10,30,150,900,

	1 10 30 150 900
	Construct the right array

	180 60 12 2 1

	180 600 360 300 900
*/
void run_array_product()
{
	int arr[] = { 10, 3, 5, 6, 2 };
	int n = sizeof(arr) / sizeof(arr[0]);
	cout << "The product array is { 10, 3, 5, 6, 2 } : \n";
	productArray(arr, n);

}

//int main()
//{
//	run_array_product();
//	return 0;
//}

