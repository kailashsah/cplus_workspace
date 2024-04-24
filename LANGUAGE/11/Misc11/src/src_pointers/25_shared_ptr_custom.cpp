#include <iostream>
using namespace std;

/*
	1. custom shared_ptr<> 
	2. reference- 
		https://codereview.stackexchange.com/questions/283909/implementation-of-a-shared-pointer-constructors-and-destructor
		https://pvs-studio.com/en/blog/terms/6515/ 

	3.


*/
#include <memory>

class A {

public:
	int x = 0;
	A()
	{

	}
};

template <class T>
class sharedptr {
public:
	T* sptr;
	uint16_t* refcount;

public:
	sharedptr() :sptr(nullptr), refcount(nullptr)
	{
		cout << "ctor" << endl;
	}
	sharedptr(T* ptr) : sptr(ptr), refcount(new uint16_t(1)) {
		cout << "customized ctor" << endl;
		//(*refcount)++;
	}
	~sharedptr() {
		cout << "dtor" << endl;
		cleanup();
	}
	sharedptr(const sharedptr& robj);
	sharedptr& operator =(const sharedptr& robj);
	sharedptr(sharedptr&& robj);
	sharedptr& operator = (sharedptr&& robj);
	void cleanup();
};

template<class T>
sharedptr<T>::sharedptr(const sharedptr& robj) {
	//if (this != &robj) {} // sharedptr<A> sptrC(sptrC); -> error says - sptrC is undefined
	cout << "copy ctor" << endl;
	sptr = robj.sptr;
	refcount = robj.refcount;
	if (robj.sptr != nullptr)
		*refcount++;

}

template <class T>
sharedptr<T>::sharedptr(sharedptr&& robj) {
	cout << "move ctor" << endl;
	sptr = robj.sptr;
	refcount = robj.refcount;

	robj.sptr = nullptr;
	robj.refcount = nullptr;

}

template <class T>
sharedptr<T>& sharedptr<T>::operator=(const sharedptr& robj) {
	cout << "assignment op" << endl;
	if (this != &robj) {
		cleanup();
		sptr = robj.sptr;
		refcount = robj.refcount;
		*refcount++;
	}
	return *this;
}

template <class T>
sharedptr<T>& sharedptr<T>::operator=(sharedptr&& robj) {
	cout << "move assignment op" << endl;
	if (robj.sptr != nullptr && this != &robj) {
		cleanup();
		sptr = robj.sptr;
		refcount = robj.refcount;

		robj.sptr = nullptr;
		robj.refcount = nullptr;
	}
	return *this;
}

template <class T>
void sharedptr<T>::cleanup() {
	if (refcount != nullptr) {
		(*refcount)--;
		if ((*refcount) < 1)
		{
			cout << "deleted internal buffer" << endl;
			delete sptr;
			delete refcount;
		}
	}
}

void run_shared_ptr_custom() {

	{
		sharedptr<A> sptr(new A());// ctor customized
		sharedptr<A> sptrA = new A;	// ctor customized
		sharedptr<A> sptrB;			// default ctor
		sharedptr<A> sptrD = sptrB; // copy ctor

		sptrD = move(sptr);			// move assignment
		sptrD = move(sptrA);
		sharedptr<A> sptrE = move(sptrD);// move ctor
	}


	//sharedptr<A> sptrC(sptrC);// error says - sptrC is undefined

}
/*
	customized ctor
	customized ctor
	ctor
	copy ctor
	move assignment op
	move assignment op
	deleted internal buffer
	move ctor
	dtor
	deleted internal buffer
	dtor
	dtor
	dtor
	dtor
	program ended
*/

void run_shared_ptr_native_ver() {

	shared_ptr<int> sptr = make_shared<int>(10);// <memory>

	shared_ptr<A> sptrA = make_shared<A>();
	sptrA->x = 10;

	shared_ptr<A> sptrB;
	sptrB = sptrA;
	cout << sptrB->x << endl;

	shared_ptr<A> sptrC = sptrB;
}

//int main()
//{
//	run_shared_ptr_custom();
//	//run_shared_ptr_native_ver();
//	cout << "program ended" << endl;
//
//}
