#include <iostream>

using namespace std;

struct node
{
	int data;
	node* next;
};

class linked_list
{
private:
	node* head, * tail;
public:
	linked_list()
	{
		head = NULL;
		tail = NULL;
	}

	void add_node(int n)
	{
		node* tmp = new node;
		tmp->data = n;
		tmp->next = NULL;

		if (head == NULL)
		{
			head = tmp;
			tail = tmp;
		}
		else
		{
			tail->next = tmp;// for chaining/linking with previous element.
			//tail = tail->next;
			tail = tmp;

		}
	}
	void print(ostream& os = cout) const
	{
		node* tmp;
		tmp = head;
		while (tmp != NULL)
		{
			os << tmp->data;
			if (tmp->next == NULL)
				break; // reached last element. // for safer side.

			tmp = tmp->next;
		}

	}
	void display()
	{
		node* tmp;
		tmp = head;
		while (tmp != NULL)
		{
			cout << tmp->data << endl;
			tmp = tmp->next;
		}
	}
};

void run_linkedlist() {
	linked_list a;
	a.add_node(1);
	a.add_node(2);
	a.add_node(3);
	a.display(); // 1 2 3
	//a.print();
}

//int main()
//{
//	run_linkedlist();
//	return 0;
//}