
#include <stdio.h>
#include "conio.h"

namespace queue_demo {

	int f = 0, r = -1, q[100], size = 0;

	void enqueue(int x) {
		r = r + 1;
		q[r] = x;
		size = size + 1;
	}

	int dequeue() {
		int elem;
		if (f > r)
			elem = -22;
		else {
			elem = q[f];
			f = f + 1;
			size = size - 1;
		}
		return elem;
	}

	int main() {
		int i, n = 0, x, elem;
		char ch[100];
		scanf("%d", &n);
		for (i = 0; i < n; i++) {
			fflush(stdin);
			scanf(" %c", &ch[i]);
			if (ch[i] == 'E') {
				scanf("%d", &x);
				enqueue(x);
				printf("%d\n", size);
			} else if (ch[i] == 'D') {
				elem = dequeue();
				if (elem != -22)
					printf("%d %d\r\n", elem, size);
				else
					printf("-1 0\r\n");
			}
		}
		_getch();
		return 0;
	}

}
/*

int main ()
{
	queue_demo::main();
	return 0;
}
*/
