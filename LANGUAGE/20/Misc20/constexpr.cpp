#include <iostream>

using namespace std;

constexpr int addOne(int n)
{
	return [n] { return n + 1; }();
}
