#include<iostream>


using namespace std;
// create tree traversal
// graph traversal
// create min heap
// shared_ptr
// binary search
// Function pointer
// read string, convert in objects
// 
//.................................................
// create tree traversal
class node;
class node {
public:
	node(int a): data(a), right(nullptr), left(nullptr){}
	int data;
	node* left;
	node* right;
};
void print_preorder(node* root = nullptr);
void print_BFS(node* root);
void run_tree_practice() {
	// DFS
	node* root = new node(2);
	root->left = new node(1);
	root->right = new node(3);
	cout << endl;
	print_preorder(root);
	cout << endl;
	print_BFS(root);
}

#include <queue>
void print_BFS(node* root) {
	// BFS
	queue<node*> q;
	q.push(root);
	while (!q.empty()) {
		node* temp = q.front();
		q.pop();
		if(temp)
			cout << temp->data << " ";
		if (temp->left)
			q.push(temp->left);
		if (temp->right)
			q.push(temp->right);

	}
}
void print_preorder(node* root) {
	// DFS
	// preorder - root, left, right 
	if (root)
	{
		cout << root->data << " ";
		print_preorder(root->left);
		print_preorder(root->right);
	}

}
// end - create tree traversal


//.................................................
// graph traversal

#include <map>
#include <list>
class graph {
public:
	map<int, list<int> > adj;
	map<int, bool> visited;
	void add_edge(int v, int w) {
		adj[v].push_back(w);
	}
	void bfs_util() {
		// for disconnected graph
		for (auto ele: adj) {
			if (!visited[ele.first])
				bfs(ele.first);
		}
	}
	void bfs(int v) {
		//int l;
		//const int vertices = const_cast<int&>(l = adj.size());
		//bool* visitedd = new bool [l] {0}; // another way of creating array

		if (visited[v])
			return;

		visited[v] = true;
		cout << v << " ";
		list<int>::iterator itr;
		for (itr = adj[v].begin(); itr != adj[v].end(); ++itr) {
			if (!visited[*itr])
				bfs(*itr);
		}

	}

};
void run_graph_practice() {
	graph g;
	g.add_edge(1,2);
	g.add_edge(1,3);
	g.add_edge(2, 4);
	g.add_edge(5, 6); // disconnected part
	g.bfs_util();// 
}
// end - graph traversal
//.................................................

// create min heap
#include <queue>
void run_min_heap() {

	std::priority_queue<int, vector<int>, greater<int>> minheap;
	//priority_queue<int> minheap;  // --> maxHeap
	minheap.push(5);
	minheap.push(6);
	minheap.push(1);
	while (!minheap.empty()) {
		cout << minheap.top() << ", ";
		minheap.pop();
	}

}
//.................................................

// shared_ptr
using uint = unsigned int;
template <typename T>
class sptr {
public:
	string name;
	T* ptr;
	uint* ref;
public:
	sptr(string s) : name(s), ptr(nullptr), ref(nullptr) {}
	sptr(string s, T* sptrr, uint* reff) : name(s), ptr(sptrr), ref(reff) {}
	//
	~sptr() {
		cleanup();
		print("dtor");
	}
	void cleanup() {
		if (ref != nullptr) {
			(*ref)--;
			if (*ref == 0) {
				print("ref reaches to zero");

				delete ptr;
				delete ref;
			}
		}
	}
	// copy ctor
	sptr(const sptr& p) {
		ptr = p.ptr;
		ref = p.ref;
		ref++;
	}

	// move copy ctor
	sptr(sptr&& p) {
		cleanup();
		this->ptr = p.ptr;
		this->ref = p.ref;
		*(this->ref)++;
	}

	// template assignment
	template <typename U>
	sptr& operator=(sptr<U>& p) {
		if ((*this).ptr == reinterpret_cast<T*>(p.ptr))
		{
			print("same obj");
			return *this;
		}
		cleanup();
		ptr = reinterpret_cast<T*>(p.ptr);
		ref = p.ref;
		(*ref)++;
	}
	// assignment
	//sptr& operator=(sptr& p) // ok, this also works fine
	void operator=(sptr& p) {
		if (this == &p) {
			print("same obj");
			//return *this; // ok, this also works fine
		}

		/*if ((*this).ptr == p.ptr)
		{
			cout << "same obj" << endl;
			return *this;
		}*/
		cleanup();
		ptr = p.ptr;
		ref = p.ref;
		(*ref)++;
	}
	//
	void print(string s) {
		cout << name << "--> " << s << endl;
	}
	// move assignment
	sptr& operator=(sptr&& p) {
		if (this == &p) {
			print("same obj");
			return *this;
		}
		this->ptr = p.ptr;
		this->ref = p.ref;
		*(this->ref)++;
	}
	T* operator->() {
		print("arrow op ");
		return ptr;
	}
	T& operator *() {
		print(" dereference op ");
		return *ptr;
	}

	// end of class
};
struct res {
	int u ;
	res* r;
};
void run_shared_ptr34() {

	// assignment of two different datatype shared_ptr
	sptr<char> sptr_ch("sptr_ch", new char('a'), new uint(1));
	sptr<int> sptr_int("sptr_int");
	sptr_int = sptr_ch; // char assignment into int  sptr& operator=( sptr<U>& p)
	
	// regular data type check
	sptr<int> p("p", new int(2), new uint(1));
	sptr<int> two("two");
	two = p;
	cout << *p << endl; // call to dereference op
	cout << *(&p)->ptr << endl; // prints 2
	cout << "ref : " <<  * p.ref << endl;
	//
	// arrow operator
	res* r = new res;
	r->r = new res;	
	//sptr<int>* three = new sptr<int>("three", new int(2), new uint(1));
	sptr<res> three("three", r, new uint(1));
	three.print("");
	//cout << three.ptr->r->u; // this wouldn't call arrow op
	cout << three->u; // this called the arrow op

	cout << endl;
	cout << endl;
}
// end - shared_ptr
//.................................................

// binary search
uint32_t binary_search(uint32_t (&p)[4], uint32_t key ,  uint32_t low , uint32_t high) {
	uint32_t index {999};
	//size_t size = sizeof(p) / sizeof(uint32_t); // not req
	uint32_t mid = (low + high) / 2;
	if (p[mid] == key)
		return mid;
	if (p[mid] < key ) {
		return binary_search(p, key, mid + 1, high);
	}
	if (p[mid] > key)
		return binary_search(p, key, low, mid -1);
	return index;
}
void run_binary_search() {
	// binary search applicable on sorted array
	uint32_t arr[] = {10, 15, 18, 20 };
	cout << "binary search : " << binary_search(arr, 20, 0, 3) + 1 ;
}
// end - binary search
//.................................................

// Function pointer
template <typename T>
using ptr = T*;

uint32_t add(uint32_t a, uint32_t b) {
	return a + b;
}
using fp = uint32_t (*)(uint32_t, uint32_t);
typedef uint32_t (*funp)(uint32_t, uint32_t);
void run_function_pointer() {
	// below is equal to the int pointer
	ptr<int> p = new int;
	*p = 9;
	cout << *p << endl;
	//
	fp f1 = add;
	funp f = &add; // add is also accepatable
	cout << f1(4, 5) << endl;
	cout << f(4,5);
}
// end - Function pointer
//.................................................

// read string, convert in objects 
#include <sstream>
void run_stringstream() {
	string s = "google GGOL 25             amazon         AMZ        600    ";
	stringstream ss ( s );
	//cout << getline(ss);
	string input;
	while (ss >> input) {
		cout << input << " "; //google GGOL 25 amazon AMZ 600
	}


}

void run_str_conversion() {
	// str to float
	string str;
	//str = "102.12345678";
	str = "1021234567.123456789";
	float f = strtof(str.c_str(), nullptr);
	cout << "str to float : " << str << " : " << f << endl;

	//
	str = "1.123456789";
	//str = "123456789.123456789";
	double d = strtod(str.c_str(), nullptr);
	cout << "str to double : " << str << " : " << d << endl;
	//
	str.empty();
	string str1 = "10.923456789";
	long l = strtol(str1.c_str(), nullptr, 10);
	cout << "str to long : " <<  str1 << " : " <<l << endl;
	
	

}
// end - read string, convert in objects
//.................................................

// singleton class
#include <mutex>
class Foo {
public:
	static Foo* Instance();
private:
	Foo() { init(); }
	void init() { cout << "init done." << endl; } // your init cache function.
	static atomic<Foo*> pinstance;
	static mutex m_;
};

atomic<Foo*> Foo::pinstance{ nullptr };
std::mutex Foo::m_;

Foo* Foo::Instance() {
	if (pinstance == nullptr) {
		lock_guard<mutex> lock(m_);
		if (pinstance == nullptr) {
			pinstance = new Foo();
		}
	}
	return pinstance;
}

int run_singleton() {


	//Foo* foo1 = Foo::Instance();
	Foo* foo1{ Foo::Instance() };
	Foo* foo2 = Foo::Instance();
	return 0;
}
//.................................................
class A {
public:
	int a;
	virtual ~A() = default;
};
class B :public A {}; class D :public B {};

class C : public A {};

void run_check_polymorphic_class_casting() {
	A* base = new B; // -> upcast
	
	// 1.
	//C* derived = static_cast<C*>(new B); // siblings, 'static_cast': cannot convert from 'B *' to 'C *'
	
	// 2.
	// A* base = new B;
	//C* derived = static_cast<C*>(base); // ok, downcasting, ptr type conversion, no underlying check 
	//A* derived = static_cast<A*>(new C); // ok. upcasting
	C* derived = static_cast<C*>(new A); // ok. downcasting
	
	// 3.
	//C* derived = dynamic_cast<C*>(base); // return null -> downcasting (parent casting to child)
	//D* derived = dynamic_cast<D*>(new B); // return null, downcasting 
	//C* derived = dynamic_cast<C*>(new A); // return null, downcasting -> it could pass if underlying obj would be C type object

	// 4. const_cast
	//C* derived = const_cast<C*>(base); // cannot convert from 'A *' to 'C *'
	//C* derived = const_cast<C*>(new A); // cannot convert from 'A *' to 'C *' -> downcasting
	//A* derived = const_cast<C*>(new C); // ok -> upcasting
	
	cout << derived;
	
	
	
}
//.................................................
void pause_thread(int n)
{
	std::this_thread::sleep_for(std::chrono::seconds(n));
	std::cout << "pause of " << n << " seconds ended\n";
}

int run_join_thread()
{
	std::cout << "Spawning 3 threads...\n";
	std::thread t1(pause_thread, 6);
	std::thread t2(pause_thread, 2);
	std::thread t3(pause_thread, 1);
	std::cout << "Done spawning threads. Now waiting for them to join:\n";
	t1.join();
	if (t2.joinable()) {
		cout << "t2 joined" << endl;
		t2.join();
	}
	
	t3.join();
	t2.detach();

	std::cout << "All threads joined!\n";

	return 0;
}
//.................................................
void run_interview_question_oracle() {
	const char* str[] = { "AAAAA", "BBBBB", "CCCCC", "DDDDD" };
	const char** sptr[] = { str + 3, str + 2, str + 1, str }; // str[0] = "AAAAA"  str --> A  , sptr --> AAAA
	char*** pp;

	pp = (char***)sptr;
	++pp;
	printf("%s", **++pp + 2); // output BBB
}
//.................................................
// todo 
// intersectin of two linked list
struct Node { Node* next; };

Node* findIntersectionInLinkedList(Node* headA, Node* headB) {
	while (headA->next != nullptr || headB->next != nullptr) {
		if (headA->next == headB->next)
			return headA->next; // intersection found
		else if (headA->next->next == headB->next) {
			return headA->next->next;
		}
		else if (headA->next == headB->next->next) {
			return headB->next->next;
		}
		else
		{
			if (headA->next != nullptr)  headA = headA->next;
			if (headB->next != nullptr)  headB = headB->next;
		}
	} // end of while
}
//.................................................
void run_practice_1() {
	
	run_interview_question_oracle();

	//run_join_thread();

	//run_check_polymorphic_class_casting();
	//run_singleton();
	// 
	//run_str_conversion();
	// 
	//run_stringstream();
	// 
	//run_function_pointer();
	// 
	//run_binary_search();
	// 
	//run_shared_ptr34();
	// 
	//run_min_heap();
	// 
	//run_graph_practice(); // 1 2 4 3
	// 
	//run_tree_practice();
}
//.................................................

int main()
{
	run_practice_1();
	return 0;
}
