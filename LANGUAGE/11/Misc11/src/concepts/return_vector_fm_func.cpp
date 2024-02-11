#include <iostream>
using namespace std;

/*
	1. Note the presence and position of & in the parameter. It means vtr is a referenced vector, and not a copy of the argument to be sent. Note the presence and position of & in the return type. It means that the reference of a vector will be returned by the function. Note that the inside statement, “return vtr;” does not have &.

	2.

*/
#include <vector>
//1.
vector<string>& fn(vector<string>& vtr) {

	return vtr; // OK
}

//2. 
vector<string>& fn_v2(vector<string> vtr) { // without reference version

	return vtr; // warning C4172: returning address of local variable or temporary: vtr
	// *v[i] prints garbage chars
	// not advised
}
//3.
vector<string>& fn_v3() {
	vector<string> vtr = { "a", "b", "c" };
	return vtr; // warning C4172: returning address of local variable or temporary: vtr
	// print blanks.
	// not advised
}



void run_return_vector_fm_func()
{
	vector<string> store = { "bread", "meat", "rice", "tomato sauce", "Cheese" };
	//1.
	vector<string>* v = &fn(store); // prints the elements inside it // OK .. taking address of return & assigning in ptr
	
	//3.
	{
		cout << "reference version" << endl;
		vector<string>& v_ref = fn(store); // prints the elements inside it // OK
		for (unsigned int i = 0; i < v_ref.size(); i++)
			cout << v_ref[i] << ", ";
	}
	//2.
	//v = &fn_v3(); // runtime issue // Not OK

	for (unsigned int i = 0; i < v->size(); i++)
		cout << (*v)[i] << ", "; // or other way, v->at(i);

	cout << endl;

}

//int main()
//{
//	run_return_vector_fm_func();
//	return 0;
//}
