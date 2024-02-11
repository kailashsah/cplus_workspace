#include <iostream>

#include <memory> // make_unique
#include <algorithm>
using namespace std;
#include <vector>

void uniqueptr()
{
	auto endll = [] { cout << endl << endl; };

	// 1. simple unique_ptr
	unique_ptr<int> pInt = make_unique<int>(4);
	cout << "Value in the unique ptr : " << *pInt << endl;   // 4
	cout << " *(pInt.get()) : " << *(pInt.get()); // 4 
	endll();

	// 2.	
	unique_ptr<int[]> arr_one{ new int[10] }; //ok

	// 3. ptr pointing to int array[] 
	unique_ptr<int[]> arr = make_unique<int[]>(10);			//ok
	cout << "Garbage value held by 10 as unique ptr array : ";
	for (int i{}; i < 10; ++i)
		cout << arr[i];
	endll(); // 0000000000-33686019 (garbage for 11th) 
	//copy(begin(*arr.get()), end(arr.get()), ostream_iterator<int>(cout)); // error .. see (5)
	

	// 4.
	//unique_ptr<int[10]> arr1 = make_unique<int [10]>(10);	// error
	

	// 5. print array into console
	int arr_two[10];
	cout << "output from int arr_two[10] ";
	copy(begin(arr_two), end(arr_two), ostream_iterator<int>(cout));
	endll();

	// 6. print vector to console
	vector<int> vec = { 1,2,3 };
	cout << "output from vector<int> vec = { 1,2,3 } : ";
	copy(begin(vec), end(vec), ostream_iterator<int>(cout));
	endll(); // 123
}
//.................................................
void unique_ptr_buffer() {

	cout << endl << "unique_ptr_buffer() : " << endl;
	uint32_t size = 20;

	//1.
	unique_ptr<char> char_buff(new char[size]); // char pointer
	strcpy(char_buff.get(), "I am unique ptr ");
	cout << char_buff; // I am unique ptr
	cout << endl;

	//2.
	unique_ptr<char[]> c_ptr;			// I did mistake for '[]'
	c_ptr = make_unique<char[]>(size); // I did mistake for '[]'

	//2.1
	//unique_ptr<char[]> c_ptr = make_unique<char[]>(size+100); // I did mistake for '[]'
	strcpy_s(c_ptr.get(), size, "I am make_un");
	cout << c_ptr; // I am make_un
}

void run_uniqueptr() {
	uniqueptr();
	unique_ptr_buffer();
}

//int main()
//{
//	run_uniqueptr();
//	return 0;
//}
