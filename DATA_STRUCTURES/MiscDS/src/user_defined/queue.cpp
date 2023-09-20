

#include <stdio.h>
#include "conio.h"


int front = 0, rear = -1, que[100], size = 0;

void enqueue(int x)
{
	rear = rear + 1; // increment rear
	que[rear] = x;
	size = size + 1;
}

int dequeue()
{
	int elem;
	if (front > rear)
		elem = -22; // front cannot be greater than back
	else
	{
		// increment fron pointer, decrease size
		elem = que[front];
		front = front + 1;
		size = size - 1;
	}
	return elem;
}

void run_queue() {
	int i, n = 0, x, elem;
	char ch[100]; // enqueue/dequeue for 100 times
	scanf_s("%d", &n);
	for (i = 0; i < n; i++)
	{
		fflush(stdin);
		scanf_s(" %c", &ch[i]);

		if (ch[i] == 'E')
		{
			scanf_s("%d", &x);
			enqueue(x);
			printf("%d\n", size);
		}
		else if (ch[i] == 'D')
		{
			elem = dequeue();
			if (elem != -22)
				printf("%d %d\r\n", elem, size);
			else
				printf("-1 0\r\n");
		}
	}
	_getch();
}

//int main()
//{
//	run_queue();
//	return 0;
//}