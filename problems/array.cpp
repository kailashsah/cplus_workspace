
#include<iostream>
#include "conio.h"

using namespace std;

/*
Given a 2D array A, your task is to convert all rows to columns and columns to rows.

Input:
First line contains 2 space separated integers, N - total rows, M - total columns.
Each of the next N lines will contain M space separated integers.

Output:
Print M lines each containing N space separated integers. 

*/

/*
int main()
{
	int Arr1[100][100], Arr2[100][100];
	unsigned int R, C, r, c, i, j;

	cin >> R;
	cin >> C;

	r = C;
	c = R;

	for (i = 0; i<R; i++)
	{
		for (j = 0; j<C; j++)
			cin >> Arr1[i][j];
	}

	for (i = 0; i<r; i++)
	{
		for (j = 0; j<c; j++)
			Arr2[i][j] = Arr1[j][i];
	}

	for (i = 0; i<r; i++)
	{
		for (j = 0; j<c; j++)
			cout << Arr2[i][j] << " ";
		cout << "\n";
	}

	_getch();
}

*/