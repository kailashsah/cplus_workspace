

#include <stdio.h>
#include <iostream>

struct ST
{
	int a = 10;
};

/*
int main()
{

	struct ST stVar;

	union test
	{
		int i;
		int j;
	};

	union test var = { 10 };
	printf("%d,%d\n", var.i, var.j);
	return 0;
}*/

/*
int findExtra(int arr1[], int arr2[], int n)
{
	for (int i = 0; i<n; i++)
		if (arr1[i] != arr2[i])
			return i;

	return n;
}

// Driver code
int main()
{
	int arr1[] = { 2, 4, 6, 8, 10, 12, 13 };
	int arr2[] = { 2, 4, 6, 8, 10, 12 };
	int n = sizeof(arr2) / sizeof(arr2[0]);

	// Solve is passed both arrays
	std::cout << findExtra(arr1, arr2, n);
	return 0;
}
*/
/*
#include <stdlib.h>

/* This finction sets the values of *x and *y to nonr-epeating
elements in an array arr[] of size n
void get2NonRepeatingNos(int arr[], int n, int *x, int *y)
{
	int xor = arr[0]; /* Will hold xor of all elements 
	int set_bit_no;  /* Will have only single set bit of xor 
	int i;
	*x = 0;
	*y = 0;

	// Get the xor of all elements 
	for (i = 1; i < n; i++)
		xor ^= arr[i];

	// Get the rightmost set bit in set_bit_no 
	set_bit_no = xor & ~(xor-1);

	// Now divide elements in two sets by comparing rightmost set
	//bit of xor with bit at same position in each element. 
	for (i = 0; i < n; i++)
	{
		if (arr[i] & set_bit_no)
			*x = *x ^ arr[i]; //XOR of first set 
		else
			*y = *y ^ arr[i]; //XOR of second set
	}
}

// Driver program to test above function 
int main()
{
	int arr[] = { 2, 3, 7, 9, 11, 2, 3, 11 };
	int *x = (int *)malloc(sizeof(int));
	int *y = (int *)malloc(sizeof(int));
	get2NonRepeatingNos(arr, 8, x, y);
	printf("The non-repeating elements are %d and %d", *x, *y);
	getchar();
}
*/

/*
// explicit keyword
class Complex
{
private:
	double real;
	double imag;

public:
	// Default constructor
	explicit Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

	// A method to compare two Complex numbers
	bool operator== (Complex rhs) {
		return (real == rhs.real && imag == rhs.imag) ? true : false;
	}
};

int main()
{
	// a Complex object
	Complex com1(3.0, 0.0);

	if (com1 == (Complex)3.0)
		std:: cout << "Same";
	else
		std::cout << "Not Same";
	return 0;
}
*/