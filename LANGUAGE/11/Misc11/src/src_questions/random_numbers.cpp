#include <iostream>
using namespace std;

void random_numbers();
void random_number_2();
//
#include <vector>
#include <random> // uniform_int_distribution, random_device

void random_numbers(void)
{
	using u32 = uint_least32_t;
	using engine = std::mt19937;
	std::random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(1, 10);

	//for (int repetition = 0; repetition < 100; ++repetition)
	//	std::cout << distribute(generator) << " "; //std::endl;
	vector<int> vec(99);
	generate(vec.begin(), vec.end(), [=]() mutable {return distribute(generator); });
	sort(vec.begin(), vec.end());
	for (auto i : vec) {
		cout << i << " ";
	}
}


#include <algorithm>
int ran(int min, int max)
{
	std::random_device r;
	std::mt19937 gen(r());
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}
int myrandom(int i) { return std::rand() % i; }
void random_number_2()
{
	const int fill_size = 10;
	const int min = 1;        // min random number
	const int max = 100;      // max random number

	std::vector<int> vec;
	while (vec.size() != fill_size) {
		vec.emplace_back(ran(min, max)); // create new random number
		std::sort(begin(vec), end(vec)); // sort before call to unique
		auto last = std::unique(begin(vec), end(vec));
		vec.erase(last, end(vec));       // erase duplicates
	}

	//random_shuffle(begin(vec), end(vec)); // mix up the sequence
	//random_shuffle(vec.begin(), vec.end(), myrandom);
	_Random_shuffle1(vec.begin(), vec.end(), myrandom);
	for (const auto& i : vec)                  // and display elements
		std::cout << i << " ";
}



//int main()
//{
//	random_numbers();
//	random_number_2();
//	return 0;
//}
