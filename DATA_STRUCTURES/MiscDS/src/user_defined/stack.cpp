

#include <iostream>
#include "conio.h"

using namespace std;

#include <stdio.h>
#define MAX 10
int stack[MAX];
int top = -1;
int elment;

void push(int data)
{

	top = top + 1;
	stack[top] = data;


}
void pop()
{
	printf("%d\n", stack[top]);

	top = top - 1;

}
void run_stack_as_array() {
	int q;
	int type, cost;
	scanf_s("%d", &q);
	while (q>0)
	{
		scanf_s("%d", &type);

		if (type == 1)
		{
			if (top != -1)
			{
				pop();
			}
			else
			{
				printf("No Food\n");

			}
		}
		if (type == 2)
		{
			scanf_s("%d", &cost);

			if (top != MAX - 1)
			{
				push(cost);
			}
		}

		q--;
	}
	_getch();
}

//.................................................

class Stack
{
private:
	int stackArray[100]; int top;
public:
	Stack() {
		top = -1;
	}
	int Pop() {
		return stackArray[top--];
	}
	void Push(int data) {
		stackArray[++top] = data;
	}
	int Peek() {
		return stackArray[top];
	}
	bool IsEmpty()
	{
		if (top == -1)
			return 1;
		else
			return 0;
	}

};

void run_stack() {
	Stack orderStack;
	int noOfQueries;
	cin >> noOfQueries;
	int queryType, cost;

	while (noOfQueries-- > 0)
	{
		cin >> queryType;
		if (queryType == 1)
		{

			if (orderStack.IsEmpty())
				cout << "No Food" << endl;
			else
				cout << orderStack.Pop();
		}
		else if (queryType == 2)
		{

			cin >> cost;
			orderStack.Push(cost);
		}

	}
}

//int main()
//{
//	run_stack_as_array();
//	run_stack();
//	return 0;
//}

