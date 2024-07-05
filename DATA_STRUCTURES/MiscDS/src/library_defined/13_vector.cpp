#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
/*
	1. capactiy() -
		Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.

		This capacity is not necessarily equal to the vector size. It can be equal or greater, with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
		The theoretical limit on the size of a vector is given by member "max_size".

*/

//
void fill_array();
void run_unique_on_vector();
void vector_2D_array();
void run_vector_insert();
void run_vector_erase();
void vector_for_each_one();
void vector_size();
void vector_swap();
void run_ways_to_copy_vectors();
//
void fill_array() {
	vector<int> vec(100, 0);
	
	//1.
	for_each(vec.begin(), vec.end(), [](auto a) { cout << a << " "; }); cout << endl; // print
	for_each(vec.begin(), vec.end(), [i = 0](auto& a) mutable { i++; a = i; return a; }); cout << endl; // fill

	//2. random numbers  -- fill 1 to 100;
	cout << endl << "random numbers  -- fill 1 to 100() : " << endl;
	vec.resize(300);
	srand(time(nullptr));
	for_each(vec.begin(), vec.end(), [](auto& a) {a = 1 + rand() % 99; ; return a; });
	sort(vec.begin(), vec.end());
	for_each(vec.begin(), vec.end(), [](auto a) { cout << a << " "; }); cout << endl;// print

}

void run_unique_on_vector() {
	vector<int> vec(100, 0);

	//3. std::unique() is used to remove duplicates of any element present consecutively in a range[first, last)
	cout << endl << "unique() : " << endl;
	//3.1
	auto last = unique(vec.begin(), vec.end(), [=](auto l, auto r) -> bool {
		if (l == r)
			return true;// to remove elements
		else
			return false;
		});

	//3.2
	//auto last = unique(vec.begin(), vec.end());
	int unique_elements = std::distance(vec.begin(), last);// last = final elements in vector
	cout << "unique_elements are  " << unique_elements << endl;

	vec.erase(last, vec.end());
	for_each(vec.begin(), vec.end(), [](auto a) { cout << a << " "; });
	cout << endl;

	//4.
	cout << endl << "_Random_shuffle1() : " << endl;
	vector<int> vec2(100, 0);
	iota(vec2.begin(), vec2.end(), 1);
	auto l = [](auto a) mutable {return rand() % a; };;
	//It randomly rearrange elements in range [first, last). The function swaps the value of each element with some other randomly picked element.
	_Random_shuffle1(vec2.begin(), vec2.end(), l);
	for_each(vec2.begin(), vec2.end(), [](auto a) { cout << a << " "; });
	cout << "count is " << vec2.size() << endl;
	//iota();
}
//.................................................

void vector_2D_array() {
	vector<vector<int>> vec(2);
	vec[0].push_back(1);
	vec[0].push_back(2);
	vec[1].push_back(3);
	vec[1].push_back(4);
	cout << "row" << vec.size();
	cout << " col" << vec[0].size();
	cout << endl;
	for (auto row : vec)
	{
		cout << row[0] << " " << row[1];
		cout << endl;
	}
}
//.................................................
void run_vector_insert() {
	
	vector<int> veci = { 1,2,5,2,4,5 };
	//veci.push_back(5);
	//veci.pop_back();
	veci.insert(veci.begin(), { 55, 66, 77 });
	veci.at(3);
	veci.emplace_back(88);
	/*
		push_back("foo") constructs a temporary string from the string literal, and then moves that string into the container, whereas my_vec. emplace_back("foo") just constructs the string directly in the container, avoiding the extra move
	*/
}
void run_vector_erase()
{
	/*
		1. The destructor is called on the objects, but the memory remains allocated. No, memory are not freed. In C++11, you can use the "shrink_to_fit()" method for force the vector to free memory
		
		2. .resize(0) and .clear() don't release or reallocate allocated memory, they just resize vector to zero size, leaving capacity same.

			If we need to clear with freeing (releasing) memory following works:

			Try it online!

			v = std::vector<T>();
			It calls && overload of = operator, which does moving, similar behaviour as with swap() solution.
		
		3. clear() - The vector's memory is not guaranteed to be cleared. You cannot safely access the elements after a clear. To make sure the memory is deallocated Scott Meyers advised to do this:

			vector<myStruct>().swap( vecs ); --> empty vector swap

	*/
	std::string cs = "hello";
	vector<int> veci = { 1,2,5,2,4,5 };

	//1. iterate &  erase -- if multiple 5 is present
	for (auto it = veci.begin(); it != veci.end(); ) {
		it = find(it, veci.end(), 5);

		if (it != veci.end())
		{
			cout << "found:" << it - veci.begin() << endl; // taking out position
			it = veci.erase(it);
			//it++;
		}
		else
			break; // no more 5 is found
	}

	//2.  iterate &  erase - erase if 2 is found
	for (auto it = veci.begin(); it < veci.end();)
	{
		if (*it == 2)
		{
			it = veci.erase(it); // return itr for next valid element
		}
		else
			it++;
	}

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
void vector_for_each_one()
{
	cout << endl << "vector_for_each_one() : " << endl;

	vector<int> v_int = { 1,2,3,6,5 };
	//1.
	for_each(v_int.begin(), v_int.end(), print); cout << endl;
	//2.
	for_each(v_int.begin(), v_int.end(), [](int& a) { cout << " " << a; });
	cout << endl;
}

void vector_for_each_two() {
	cout << endl << "vector_for_each_two() : " << endl;

	std::vector<double> v{ 1.0, 2.2, 4.0, 5.5, 7.2 };
	double r = 4.0;
	// add 4 to each elements
	std::for_each(v.begin(), v.end(), [&](double& v) {
		v += r;
		});

	std::for_each(v.begin(), v.end(), [](double v) { std::cout << v << " "; });
	cout << endl;

}
class Person {};
void vector_size() {
	cout << endl << "vector_size() : " << endl;

	vector<int> vec;
	cout << " vec.max_size()" << vec.max_size() << endl; // 1.073.741.823
	vector <Person> v_per;
	cout << sizeof(Person) << endl; // 1 byte
	cout << " v_per.max_size()" << v_per.max_size() << endl; //2.147.483.647 -> 2GB
	cout << endl;

}

void vector_swap() {
	cout << endl << "vector_swap : " << endl;

	// swap in vectors
	vector<int> n{ 1,2,3 };
	vector<int> p;
	cout << "n size: " << n.size() << endl;
	n.swap(p);
	cout << n.size() << endl; // 0
	cout << p.size() << endl; // 3
	for_each(p.begin(), p.end(), [](const int i) { cout << i; }); // 123
	cout << endl;

}
void run_ways_to_copy_vectors() {
	// https://www.tutorialspoint.com/ways-to-copy-a-vector-in-cplusplus
	//copy(v1.begin(), v1.end(), back_inserter(v2));
	//v2.assign(v1.begin(), v1.end());
	//v2 = v1;
	//v2.push_back(v1[i]);
	//vector<int> v2(v1);
}
void run_vector()
{
	fill_array();
	vector_2D_array();
	run_vector_insert();
	vector_for_each_one();
	vector_for_each_two();
	vector_size();
	vector_swap();
}

//int main()
//{
//	run_vector();
//	return 0;
//}
