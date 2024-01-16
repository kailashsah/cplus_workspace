

#include <iostream>
#include "conio.h"
using namespace std;
/*
	1. Two ways of doing it
		using array
		using class
*/

#include <stdio.h>
//................................................. as array

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
enum class type_of_op {PUSH , POP};
void run_stack_as_array() {
	int q;
	type_of_op push_or_pop;
	int  cost;
	
	scanf_s("%d", &q); // q = time want to run loop
	while (q > 0)
	{
		scanf_s("%d", &push_or_pop); // was int earlier .. I changed for readability

		if (push_or_pop == type_of_op::POP) // pop
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
		if (push_or_pop == type_of_op::PUSH) // push
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

//................................................. as class

class Stack
{
private:
	int stackArray[100]; 
	int top;

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

void run_stack_customized() {
	Stack orderStack;
	int noOfQueries;
	cin >> noOfQueries;
	int queryType, cost;

	while (noOfQueries-- > 0)
	{
		cin >> queryType;
		if (queryType == 1) // pop
		{

			if (orderStack.IsEmpty())
				cout << "No Food" << endl;
			else
				cout << orderStack.Pop();
		}
		else if (queryType == 2) // push
		{

			cin >> cost;
			orderStack.Push(cost);
		}

	}
}

//int main()
//{
//	run_stack_as_array();
//	run_stack_customized();
//	return 0;
//}

