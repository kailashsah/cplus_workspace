
import <iostream>;
using namespace std;

class mylist;
// class mylist:: iterator_list;
class mylist {

public:
	class iterator_list;
	typedef iterator_list iteratorr;
	iterator_list begin();
	iteratorr end();
};

class mylist::iterator_list {

	int x;
	iteratorr& abc(const iterator_list& x);
public:
	iterator_list();
};

typedef mylist::iterator_list iteratorr;  // note - it's defined after being used
//mylist::iterator_list::iterator_list(){}
iteratorr::iterator_list() {}

iteratorr mylist::begin() {
	return iteratorr();
}

iteratorr& iteratorr::abc(const iterator_list& x)
// mylist::iterator_list&  iteratorr::abc(const iterator_list& x) // OK
// mylist::iterator_list&  mylist::iterator_list::abc(const iterator_list& x) //OK
{
	cout << x.x;
	return *this;
}

