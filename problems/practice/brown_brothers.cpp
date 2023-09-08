#include<iostream>
using namespace std;

//#1. Create a linked list of 10 random integers, then reverse it.Print list after creationand after reversing it.

//#2. Design a Pair class (maps an integer to an integer, float or string), and a Row class which contains multiple Pairs.
//.................................................

//1. linked list 10 random numbers
struct Node {
	int data;
	struct Node* next;
	Node() :data{ 0 }, next{ nullptr } {}
};

void print_linked_list(struct Node* head) {
	while (head != NULL) {
		cout << head->data << " ";
		head = head->next;
	}
}

void print_linked_list_rev(struct Node* head) {
	if (head == NULL)
		return;

	print_linked_list_rev(head->next);
	cout << head->data << " ";
}
int run_linked_list() {

	srand(time(nullptr)); 
	Node* head = new Node;
	Node* list = head;
	head->next = nullptr;
	head->data = rand() % 10 + 1;
	for (int i{}; i < 10; i++)
	{
		Node* newNode = new Node;
		newNode->data = rand() % 50 + 1;
		head->next = newNode;
		head = head->next;
		
	}

	print_linked_list_rev(list);
	cout << endl;
	print_linked_list(list);
	return 0;
}
//.................................................
//#2. Design a Pair class (maps an integer to an integer, float or string), and a Row class which contains multiple Pairs.
#include <vector>
#include <algorithm>
template <typename T1, typename T2>
struct pairr {
	T1 first;
	T2 second;
	pairr() {};
	pairr(const T1& x, const T2& y) { 
		first = x; 
		second = y;
	};
	template<typename A, typename B> pairr(const pair<A, B>& p) {
		first = p.first;
		second = p.second;
	}
	// we have few more methods in pair class, but I'm keeping this very basic
};

void run_create_pair() {
	
	// checking the ctors
	pairr <int, int> p(1, 0);
	pairr <int, int> b(p);
	
	cout<<  b.first << " " << b.second ;
	// creating rows of pairs .. I could also do in loops that may appear decent
	vector <vector<pairr<int, int>> > rows = {
		{pairr<int,int>(1,2), pairr<int,int>(3,4)},
		{pairr<int,int>(5,6), pairr<int,int>(7,8)},
	};

	// print rows
	cout << endl << "print table of pairs" << endl;
	for(auto row: rows) {
		for (auto item : row) {
			cout << "(" << item.first << "," << item.second << ")";
		}
		cout << endl;
	}
}
//.................................................

//int main()
//{
//	//#2. Design a Pair class
//	//run_create_pair();  
//	// 
//	//#1. Create a linked list
//	//run_linked_list();
//
//	return 0;
//}
