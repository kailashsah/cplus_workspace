
#include <iostream>
#include <string>

using namespace std;

namespace string_rev {

	void  swap_me(char& left, char& right)
	{
		char temp = right;
		right = left;
		left = temp;
	}

	string reverse_string(string str)
	{
		int length = str.length();
		for (int i = 0; i < length / 2; i++)
		{
			swap_me(str[i], str[length - i - 1]);
			//swap(str[i], str[length - i - 1]); // defined in utility
		}
		return str;
	}


	int main()
	{
		string str = "12345678";
		cout << reverse_string(str);
		return 0;
	}

	/*int main()
	{
	string_rev::main();

	}*/
}