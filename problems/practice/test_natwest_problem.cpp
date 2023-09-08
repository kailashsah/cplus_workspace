#include <iostream>
#include <vector>
using namespace std;

//.................................................
// special array
#include <chrono> // duration_cast <>, high_resolution_clock
using namespace std::chrono;

uint32_t reverse_num(uint32_t num);
uint32_t reverse_num_str(uint32_t num); // costly by 500 microseconds
uint32_t reversDigits(uint32_t num, uint32_t reset );
uint32_t revv(uint32_t n);


int is_special_one(const char* inputarr[], int size) {
	//this_thread::sleep_for(milliseconds(2000));
	uint32_t count_return{};
	uint32_t rev{};
	for (uint32_t i{}; i < size; ++i) {
		uint32_t num = atoi(inputarr[i]);

		for (uint32_t j{ 1 }; j < num; ++j) {
			// 1.
			rev = reverse_num(j);
			// 2.
			//rev = reverse_num_str(j);
			//3.
			//rev = reversDigits(j, 1);
			// 4.
			//rev = revv(j);

			//if (j == rev) 
			{
				if (j + rev == num) {
					//cout << "one num is " << j << endl;
					count_return++;
					break;
				}
			}
		}
	}
	return count_return;
}
#include <unordered_set>
#include <unordered_map>
int is_special_set(const char* inputarr [], int size) {
	//this_thread::sleep_for(milliseconds(2000));
	uint32_t count_return{};
	uint32_t rev{};
	unordered_set<uint32_t> checked; // use of set

	for (uint32_t i{}; i < size; ++i) {
		uint32_t num = atoi(inputarr[i]);
		
	
		
		for (uint32_t j{ 1 }; j<num ; ++j) {
			// 1.
			//rev = reverse_num(j);
			// 2.
			//rev = reverse_num_str(j);
			//3.
			if (checked.find(j) == checked.end())
			{
				rev = reversDigits(j, 1);
				// 4.
				//rev = revv(j);

				//if (j == rev) 
				{
					if (j + rev == num) {
						//cout << "one num is " << j << endl;
						count_return++;
						break;
					}
					checked.insert(j);
					checked.insert(rev);
				}
			}
		}
	}
	return count_return;
}
int is_special_three(const char* inputarr[], int size) {
	//this_thread::sleep_for(milliseconds(2000));
	uint32_t count_return{};
	uint32_t rev{};
	unordered_map<uint32_t, uint32_t> checked; // use of map

	for (uint32_t i{}; i < size; ++i) {
		uint32_t num = atoi(inputarr[i]);

		

		for (uint32_t j{ 1 }; j < num; ++j) {
			// 1.
			//rev = reverse_num(j);
			// 2.
			//rev = reverse_num_str(j);
			//3.
			//if (checked.find(j) == checked.end())
			if (checked.count(j) == 0)
			{
				if (j < 10)
					rev = j;
				else {
					rev = reversDigits(j, 1);
					//rev = reverse_num(j);
					// 4.
					//rev = revv(j);

					checked.insert(make_pair(j, rev));
					checked.insert(make_pair(rev, j));

				}
				
			}
			else
				rev = checked.at(j);
				
			if (j + rev == num) {
				//cout << "one num is " << j << endl;
				count_return++;
				break;
			}
			
		}
	}
	return count_return;
}
int is_special_vector(const char* inputarr[], int size) {
	//this_thread::sleep_for(milliseconds(2000));
	uint32_t count_return{};
	uint32_t rev{};
	//unordered_map<uint32_t, uint32_t> checked; // use of map
	vector<uint32_t> checked(9999999);

	for (uint32_t i{}; i < size; ++i) {
		uint32_t num = atoi(inputarr[i]);



		for (uint32_t j{ 1 }; j < num; ++j) {
			// 1.
			//rev = reverse_num(j);
			// 2.
			//rev = reverse_num_str(j);
			//3.
			//if (checked.find(j) == checked.end())
			if (checked[j] == 0) // not found
			{
				if (j < 10)
					rev = j;
				else {
					rev = reversDigits(j, 1);
					//rev = reverse_num(j);
					// 4.
					//rev = revv(j);

					checked[j] = rev;
					checked[rev] = j;
					//checked.insert(make_pair(j, rev));
					//checked.insert(make_pair(rev, j));

				}

			}
			else
			{
				rev = checked[j];
			}

			if (j + rev == num) {
				//cout << "one num is " << j << endl;
				count_return++;
				break;
			}

		}
	}
	return count_return;
}

uint32_t reversDigits(uint32_t num, uint32_t reset = 0)
{
	
	 static uint32_t rev_num = 0;
	 static uint32_t base_pos = 1;
	if (reset == 1)
	{
		rev_num = 0;
		base_pos = 1;
	}
	
	if (num > 0)
	{
		reversDigits(num / 10);
		rev_num += (num % 10) * base_pos;
		base_pos *= 10;
	}
	return rev_num;
}

uint32_t ans = 0;
uint32_t revv(uint32_t n)
{
	// wrong solution - failed to reverse
	ans = (ans + (n % 10)) * 10; // using recursive function to reverse a number;
	if (n > 9)
		return revv(n / 10);
}
uint32_t reverse_num_str(uint32_t num) {

	if (num < 0)
		return num;

	stringstream ss;
	ss << num;
	//string str(ss); // error, no ctor 
	
	string str = ss.str();// imp

	reverse(str.begin(),str.end());
	return atol(str.c_str());
}
int reverse_num_str_2(int num)
{
	// converting number to string
	string strin = to_string(num);

	// reversing the string
	reverse(strin.begin(), strin.end());

	// converting string to integer
	num = stoi(strin);

	// returning integer
	return num;
}
uint32_t reverse_num(uint32_t num) {

	// this method is too fast.

	if (num < 10)
		return num;
	uint32_t rem = 0;
	uint32_t reverse{ };
	while (num > 0) {
		rem = num % 10;
		reverse = reverse * 10 + rem;
		num /= 10;
	}
	return reverse;
}
void run_main_natwest_problem() {

	// 1. check reverse
	// 
	//cout << reverse_num(445) << endl;
	//cout << reversDigits(4456) << endl;
	
	//int n = 5 % 10;
	//cout << n << endl; // 5
	//return; // disconnnection
	
	// 2.
	
	//const char* p[2] = {"22", "121"}; // ans 2
	//const char* p[4] = { "22", "121", "12", "3" }; // ans 3
	//const char* p[8] = { "22", "121", "12", "3",  "22", "121", "12", "3" }; // ans 6
	const char* p[9] = { "22", "121", "12", "3",  "22", "121", "12", "3", "999999"}; // no = 9, ans 6
	uint32_t size = 9;
	uint32_t loop = 15;
	while (loop > 0) {
		//1.
		auto start = high_resolution_clock::now();
		uint32_t num_reverse_sum = is_special_one(p, size);
		cout << "num who is sum of reversible numbers : " << num_reverse_sum << endl;
		auto end = high_resolution_clock::now();
		auto duration_one = duration_cast<microseconds> (end - start);
		
		//2.
		start = high_resolution_clock::now();
		num_reverse_sum = is_special_vector(p, size); // here is the change (vector)
		num_reverse_sum = is_special_set(p, size); // here is the change (set)
		//num_reverse_sum = is_special_three(p, size); // here is the change (map)
		cout << "num who is sum of reversible numbers : " << num_reverse_sum << endl;
		end = high_resolution_clock::now();
		auto duration_two = duration_cast<microseconds> (end - start);

		//auto duration1 = duration_cast< milliseconds > (end - start);
		auto duration1 = duration_cast<microseconds> (end - start);
		cout << "time spent: " << duration_one << ":" << duration_two << endl;
		loop--;
	}

}


//int main()
//{
//	
//	//run_chrono_library();
//	run_main_natwest_problem();
//	//return 0;
//}
//
void run_chrono_library() {
	high_resolution_clock::time_point start = high_resolution_clock::now(); // chrono librart
	this_thread::sleep_for(milliseconds(3000));
	high_resolution_clock::time_point end = high_resolution_clock::now();
	chrono::duration time_span = duration_cast<milliseconds> (end - start);
	cout << time_span << endl; // 3003ms // time_spane.count() -> 3007
}
