#include <iostream>
#include <map>
#include <algorithm>

using namespace std;
void run_multimap()
{
	std::multimap<const long, const std::string> colors;

	colors.insert({ 2, "red" });
	colors.insert({ 2, "orange" });
	colors.insert({ 3, "yellow" });
	colors.insert({ 4, "green" });
	colors.insert({ 4, "blue" });
	colors.insert({ 5, "violet" });


	//........................................... 2. find value 
	// error - requires : c++17 for structural bindings
	
	/*auto [begin, end] = colors.equal_range(4);
	for(auto & it : std::ranges::subrange(begin, end))
	{
		std::cout << "    " << it.second << std::endl;
	}*/
	
	//........................................... 3. equal_range()
	auto ran = colors.equal_range(4);	
	for (auto it = ran.first; it != ran.second; ++it) {
		cout << it->second << " "; // blue green
	}

	//........................................... 4. using for_each()
	for_each(
		ran.first,
		ran.second,
		[](std::multimap<const long, const std::string>::value_type& x) {
			std::cout << " " << x.second; 
		}
	);
}

//int main()
//{
//	run_multimap();
//	return 0;
//}
