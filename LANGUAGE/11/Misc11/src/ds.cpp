
//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <array>
#include <list>
#include <string>
//#include <string_view>

using namespace std;

// cheatsheet - https://gist.github.com/satwikkansal/c959e89161cc60db16b412233177feab 
//
// insert, delete by value, delete by position, find, 
void string_impl();
void map_impl();
void set_impl();
void vec_impl();
void array_impl();

int volatile_func(void)
{
	int a1 = 40;
	const volatile int* b1 = &a1;
	cout << "typeid of b1 " << typeid(b1).name() << '\n';
	int* c1 = const_cast <int*> (b1); // const_cast  also removes the volatile from variable
	cout << "typeid of c1 " << typeid(c1).name() << '\n';
	return 0;
}

int fun(int* ptr)
{
	*ptr = *ptr + 10;
	return (*ptr);
}
/*
int fun(int* ptr)
{
	return (*ptr + 10);
}*/



int fuc_caller(void)
{
	const int val = 10;
	const int* ptr = &val;
	int* ptr1 = const_cast <int*>(ptr);
	cout << fun(ptr1);
	cout << endl;
	return 0;
}
int find_samllest(int arr[], int first, int last,   int num)
{
	
	int mid = (first + last )/ 2;
	if (mid == last || mid == first)
		return num;

	if (arr[mid] == num)
		return num;

	if (arr[mid] > num)
		num = find_samllest(arr, first, mid, num);
	else if (arr[mid] < num)
		num = find_samllest(arr, mid+1, last, num);
	 

	return num;
}
void find_smallest_in_arr_driver_code()
{
	//int arr[] = {4,5, 1, 2, 3};
	int arr[] = { 1,2, 3, 4, 5 };
	cout << find_samllest(arr, 0 , 4, 4) << endl;
}

void string_impl()
{
	std::string str1 = "Text with some   spaces \0";

	auto noSpaceEnd = std::remove(str1.begin(), str1.end(), ' ');

	cout << "noSpace " << *noSpaceEnd << endl;

	// The spaces are removed from the string only logically.
	// Note, we use view, the original string is still not shrunk:
	//cout << std::string_view(str1.begin(), noSpaceEnd) << " size: " << str1.size() << '\n';
	cout << str1 << " " << str1.size() << endl;;
	str1.erase(noSpaceEnd, str1.end());
	cout << str1 << " " << str1.size() << endl;;
}
void list_impl()
{
	list<int> li;
	li.push_back(5);
	li.push_back(2);
	for (auto n : li)
		cout << n << endl;

	auto it = find(li.begin(), li.end(), 5);
	li.erase(it);

	for (auto n : li)
		cout << n << endl;
}
void array_impl()
{
	// regular array
	int arr[] = {9,8,3,4,5,6};
	int size = sizeof(arr) / sizeof(arr[0]);
	sort(arr, arr + size, less<int>()); // ascending order
	for (auto n : arr)
		cout << n << endl;
	
	cout << "stl array " << endl;
	array <int, 5> sta = { 7,6,5,4,5 };
	for (auto n : sta)
		cout << n << endl;
	cout << sta.at(3)<< endl;

	cout << "data() " << sta.data()[0] << endl; // item at first position
	auto pos = find(sta.begin(), sta.end(), 4); // find item
	remove(sta.begin(), sta.end(), 5); // remove first occurrence of item  5
	//cout << *pos;
	for (auto n : sta)
		cout << n << endl;
	


}

void map_impl()
{
	unordered_map <int, string> mapi;
	
	mapi.insert(pair<int, string>(5, "five"));
	mapi.insert(make_pair(5, "five"));
	mapi.insert(pair<int, string>(1, "one"));

	//std::qsort(mapi.begin(), mapi.end());
	//sort(mapi.begin(), mapi.end(), mapi.size(), greater<int> () );
	//sort(mapi.begin(), mapi.end());
	for (auto n : mapi)
	{
		cout << n.first << ":" << n.second << endl;
	}
	
	for (auto it = mapi.begin(); it != mapi.end();)
	{
		it = mapi.find(5);
		if (it != mapi.end())
			it = mapi.erase(it);
		
	}

	for (auto n : mapi)
	{
		cout << n.first << ":" << n.second << endl;
	}


}

void map_impl_sqbracket()
{
	unordered_map <int, int> mapi;

	mapi.insert(pair<int, int>(5, 5));
	mapi.insert(pair<int, int>(6, 6));
	mapi.insert(pair<int, int>(6, 6));
	if (mapi[5] == 5)
		cout << mapi[5]; // 5
}

void set_impl()
{
	//unordered_multiset <int> setm;
	unordered_multiset<int> set_unorder;
	multiset <int> setm;
	set_unorder.insert(1);
	set_unorder.insert(4);
	set_unorder.insert(5);
	set_unorder.insert(5);
	set_unorder.insert(3);
	set_unorder.insert(3);
	set_unorder.insert(2);
	auto it  = set_unorder.find(5);
	cout << *it << endl;
	cout << "size" << set_unorder.size() << endl;

	// remove all occurrences of item 5
	for (auto it = set_unorder.begin(); it != set_unorder.end(); ) {
		it = set_unorder.find(5);

		if (it != set_unorder.end())
		{
			//cout << "found:" << it - seti.begin() << endl;
			it = set_unorder.erase(it);
		}
	}

	//seti.erase(5);
	for (auto n : set_unorder)
	{
		cout << n << endl;
	}

}

void vec_impl()
{

	std::string cs = "hello";
	vector<int> veci = { 1,2,5,2,4,5 };
	//veci.push_back(5);
	//veci.pop_back();
	veci.insert(veci.begin(), { 55, 66, 77 });
	veci.at(3);
	veci.emplace_back(88);
	
	// iterate &  erase
	for (auto it = veci.begin(); it != veci.end(); ) {
		it = find(it, veci.end(), 5);
		
		if (it != veci.end())
		{
			cout << "found:" << it - veci.begin() << endl;
			it = veci.erase(it);
			//it++;
		}
	}

	// erase if 2 is found
	/*for (auto it = veci.begin(); it < veci.end();)
	{

		if (*it == 2)
		{
			it = veci.erase(it);
			
		}
		else
			it++;


	}*/

	// print
	for (auto n : veci) {
		cout << n << "\n";
	}

	cout << cs << endl;


}
void print(int a)
{
	// used in vector_for_each()
	cout << " " << a;
}
void vector_for_each()
{
	vector<int> v_int = { 1,2,3,6,5 };
	for_each(v_int.begin(), v_int.end(), print);
	for_each(v_int.begin(), v_int.end(), [](int& a) { cout << " " << a; });
}

// curiously recurring template pattern
class Dimension {
public:
	Dimension(int _X, int _Y)
	{
		mX = _X;
		mY = _Y;
	}

private:
	int mX, mY;
};

template <class T>
class Image {
public:
	void Draw()
	{
		cout << "base::Draw() called" << endl;
		// Dispatch call to exact type
		static_cast<T*>(this)->Draw();
	}
	Dimension GetDimensionInPixels()
	{
		// Dispatch call to exact type
		static_cast<T*>(this)->GetDimensionInPixels();
	}

protected:
	int dimensionX, dimensionY;
};

// For Tiff Images
class TiffImage : public Image<TiffImage> {
public:
	void Draw()
	{
		// Uncomment this to check method dispatch
		 cout << "TiffImage::Draw() called" << endl;
	}
	Dimension GetDimensionInPixels()
	{
		return Dimension(dimensionX, dimensionY);
	}

	// driver code
	//Image<TiffImage>* pImage = new TiffImage;
	//pImage->Draw();
};

constexpr int fib(int n)
{
	return (n <= 1) ?n: fib(n - 2) + fib(n - 1);

	// driver code
	//cout << fib(5);
}
void productArray(int arr[], int n)
{

	// Base case
	if (n == 1) {
		cout << 0;
		return;
	}
	/* Allocate memory for temporary arrays left[] and right[] */
	int* left = new int[sizeof(int) * n];
	int* right = new int[sizeof(int) * n];

	/* Allocate memory for the product array */
	int* prod = new int[sizeof(int) * n];

	int i, j;

	/* Left most element of left array is always 1 */
	left[0] = 1;

	/* Right most element of right array is always 1 */
	right[n - 1] = 1;

	/* Construct the left array */
	for (i = 1; i < n; i++)
	{
		left[i] = arr[i - 1] * left[i - 1];
		cout << left[i] << ",";
	}
	cout << endl;
	/* Construct the right array */
	for (j = n - 2; j >= 0; j--)
	{
		right[j] = arr[j + 1] * right[j + 1];
		cout << right[j] << ",";
	}

	cout << endl;
	/* Construct the product array using left[] and right[] */
	for (i = 0; i < n; i++)
		prod[i] = left[i] * right[i];

	cout << endl;
	/* print the constructed prod array */
	for (i = 0; i < n; i++)
		cout << prod[i] << " ";


	return;

	// driver code

	/*int arr[] = {10, 3, 5, 6, 2};
int n = sizeof(arr) / sizeof(arr[0]);
cout << "The product array is: \n";
productArray(arr, n);
*/
}
/*template <>
inline  bool is_ctrl<bool> = true;
*/
struct S{
	int a = 0;
	int& get()
	{
		return a;
	}
};
void move_constructor()
{
	struct B {
		string val_;
		B(string&& val) : val_(std::move(val)) {
			// val_ = std::move(val);
			cout << "move ctor called " << val_ << endl;
		}
		~B() {
			cout << val_ << endl;
		}
	};
	string a;
	B b_a(string("a")); // these all call move constructor
	auto b2 = B("b1");
	auto b0 = B("b0");
	auto* b1 = new B("b2");
}

void pointers_rvalue()
{
	S s;
	int& a = s.get();
	s.get()++;
	cout << a << endl;
	
	cout << "rvalue";
	int x{};
	cout << x << endl;
	int& ref1{ x };
	cout << ref1 << endl;
	ref1 = 1;
	cout << x << endl;
	cout << ref1 << endl;
	//int& ref2{ 5 }; // connot conver int to int&
	const int& ref3{ 5 };
	x = 3;
	cout << ref3 << endl;

	 int&& ref5{ 5 };

}



void run()
{ 
	
	//move_constructor();
	//pointers();
	
	/*Dimension* pDimension = new Dimension(1, 2);
	Dimension dime(1,2);
	*/
		
	
	//volatile_func();
	//fuc_caller();
	
	//find_smallest_in_arr_driver_code();
	
	//string_impl();
	//array_impl();
	map_impl_sqbracket();
	//map_impl();
	//set_impl();
	//list_impl();
	//vec_impl();

	cout << "<end>";
	
	//int i;
	//cin >> i;
}

// int main()
//{
//	run();
//	//return 0; not required, return 0 is provided automatically 
//}

