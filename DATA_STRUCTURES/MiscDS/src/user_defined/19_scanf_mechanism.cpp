#include<iostream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//I had put the main Function Below this function.
//d for asking string,f is pointer to the string pointer
void GetStr(const char* d, char** f)
{
	printf("%s", d);
	for (int i = 0; 1; i++)
	{
		if (i)//I.e if i!=0
			*f = (char*)realloc((*f), i + 1);
		else
			*f = (char*)malloc(i + 1);
		(*f)[i] = getchar();
		if ((*f)[i] == '\n')
		{
			(*f)[i] = '\0';
			break;
		}
	}
}

void read_string()
{
	cout << endl << "read_string() : " << endl;

	// read indefinite characters from console.
	char* s = NULL;
	GetStr("Enter string : ", &s);
	printf("Your String:- %s \nAnd It's length:- %lu\n", s, (strlen(s)));
	//printf("Your String:- %s \n", *s);
	free(s);
}


//int main()
//{
//	read_string();
//	return 0;
//}