

#include <iostream>
#include "conio.h"

using namespace std;

/*
Index
Balanced paranthesis problem
Monk's love for food
*/


/*

balanced parentheses problem.

You have a bracket sequence made up of opening '(' and closing ')' parentheses. You must check if this bracket sequence is balanced.

A bracket sequence is considered balanced if for every prefix of the sequence, the number of opening brackets is greater than or equal to the number of closing brackets, and the total number of opening brackets is equal to the number of closing brackets.

You can check this using stack. Let's see how.

You can maintain a stack where you store a parenthesis. Whenever, you come across an opening parenthesis, push
it in the stack. However, whenever you come across a closing parenthesis, pop a parenthesis from the stack.
*/

/*
int top;
void  check(char str[], int n, char stack[])
{
	for (int i = 0; i < n; i++)
	{
		if (str[i] == '(')
		{
			top = top + 1;
			stack[top] = '(';
		}
		if (str[i] == ')')
			{
				if (top == -1)
				{
					top = top - 1;
					break;
				}
				else
				{
					top = top - 1;
				}
			}
	}
	if (top == -1)
		cout << "String is balanced!" << endl;
	else
		cout << "String is unbalanced!" << endl;
}

int main()
{
	//balanced parenthesis string.
	char str[] = { '(' , 'a' , ' + ', '(', 'b ' , ' - ' , ' c' ,')' , ') ' };

	// unbalanced string . 
	char str1[] = { '(' , '(' , 'a' , ' + ' , ' b' , ')' };
	char stack[15];
	top = -1;
	check(str, 9, stack);      //Passing balanced string   
	top = -1;
	check(str1, 5, stack);    //Passing unbalanced string

	_getch();
	return 0;

}

*/


/*

Monk's Love for Food

Our monk loves food.Hence, he took up position of a manager at Sagar, a restaurant that serves people with delicious food packages.It is a very famous place and people are always queuing up to have one of those packages.Each package has a cost associated with it.The packages are kept as a pile.The job of a manager is very difficult.He needs to handle two types of queries :

1) Customer Query :
When a customer demands a package, the food package on the top of the pile is given and the customer is charged according to the cost of the package.This reduces the height of the pile by 1.
In case the pile is empty, the customer goes away empty - handed.

2) Chef Query :
The chef prepares a food package and adds it on top of the pile.And reports the cost of the package to the Manager.
Help him manage the process.

Input :
	First line contains an integer Q, the number of queries.Q lines follow.
	A Type - 1 (Customer)Query, is indicated by a single integer 1 in the line.
	A Type - 2 (Chef)Query, is indicated by two space separated integers 2 and C(cost of the package prepared) .

	Output :
	For each Type - 1 Query, output the price that customer has to pay i.e.cost of the package given to the customer in a new line.If the pile is empty, print "No Food" (without the quotes).
*/

/*
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

int main()
{
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
	return 0;
}
*/

/*
int main()
{
	Stack orderStack;
	int noOfQueries;
	cin >> noOfQueries;
	int queryType, cost;

	while (noOfQueries-- >0)
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
	return 0;
}
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

}

*/