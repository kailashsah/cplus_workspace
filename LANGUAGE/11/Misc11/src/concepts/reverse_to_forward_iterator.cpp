#include <iostream>
using namespace std;

/*
	1. You could write a helper function. One particularity of reverse_iterator is that base() gives a forward iterator that is next from the value that the reverse iterator dereferences to. This is because a reverse iterator physically points to the element after the one it logically points to. So to have the forward iterator to the same item as your reverse_iterator, you'll need to decrement the result of base() by one, or you could increment the reverse iterator first, then take the .base() of that.

*/

//result is undefined if passed container.rend()
template <class ReverseIterator>
typename ReverseIterator::iterator_type make_forward(ReverseIterator rit)
{
	try {
		cout << "*rit: " << *rit << endl;
		cout << "rit.base(): " << *(rit.base()) << endl;

		return --(rit.base()); // move result of .base() back by one.
		
		// alternatively
		// return (++rit).base() ;
		// or
		// return (rit+1).base().
	}
	catch (...) {
		throw;
	}
}

#include <vector>
void run_reverse_iterator()
{
	std::vector<int> vec{ 1, 2, 3 };
	try {
		std::vector<int>::reverse_iterator rit = vec.rbegin();

		//1.
		//rit + 2; // crash while accessing *rit.base()

		//2.
		rit++;

		std::vector<int>::iterator fit = make_forward(rit);
		std::cout << "fwd itr : " << *fit << ' ' << "rev itr: " << *rit << '\n';
		/*
			*rit: 2
			rit.base(): 3
			fwd itr : 2 rev itr: 2
		*/
	}
	catch (exception e) {
		cout << e.what() << endl; // iterator won't throw any exceptions. it crashes like unhandled exception
	}
	catch (...) {
		cout << "exception" << endl;
	}
}

//int main()
//{
//	run_reverse_iterator();
//	return 0;
//}
