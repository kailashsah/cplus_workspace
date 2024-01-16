#include <iostream>
using namespace std;

/*
	1. Use it to suppress compiler warnings of unused variables. Whether or not you choose to use this approach depends on the coding standards and practices of the team or organization you're working with.
	2. Suppresses warnings on unused entities.
	3. https://riptutorial.com/cplusplus/example/19126/--maybe-unused--
*/
#include <vector>
#include <algorithm>
void fun() {

	std::vector<int> v{ 0, 1, 2, 3 };
	std::cout << std::count_if(v.begin(), v.end(), []([[maybe_unused]] int i) {return true; }) << "\n"; // Compiles without a warning
}

/*
	//1. 
	namespace {
		[[maybe_unused]] std::string createWindowsConfigFilePath(const std::string& relativePath);
		// TODO: Reuse this on BSD, MAC ...
		[[maybe_unused]] std::string createLinuxConfigFilePath(const std::string& relativePath);
	}

	std::string createConfigFilePath(const std::string& relativePath) {
	#if OS == "WINDOWS"
		return createWindowsConfigFilePath(relativePath);
	#elif OS == "LINUX"
		return createLinuxConfigFilePath(relativePath);
	#else
	#error "OS is not yet supported"
	#endif
	}


	//2.
	[[maybe_unused]] auto mapInsertResult = configuration.emplace("LicenseInfo", stringifiedLicenseInfo);
	assert(mapInsertResult.second); // We only get called during startup, so we can't be in the map
*/