#include <iostream>
#include <string>
using namespace std;
#include <sstream> //getline(),  

void string_split() {

	string str = "first 21 second 21 third ";
	cout << endl << "string_split() for '2' in : " << str << endl;
	//1.
	stringstream ss(str);
	string strr;
	cout << "using getline() " << endl;
	while (getline(ss, strr, '2')) // '2' is delimiter
	{
		cout << strr << " ";
	}

	//2.
	cout << endl;
	cout << "using strtok() " << endl;
	char* token = strtok(const_cast<char*>(str.data()), "2");
	while (token != nullptr) {
		cout << token << " ";
		token = strtok(0, "2");

	}

	cout << endl;
}


void findin_string() {
	string str = "I 2 m 2 r";
	string tofind = "2";
	uint32_t pos = 0;// = str.find(tofind);
	uint32_t cpos = 0;
	string sstr;
	while ((pos = str.find(tofind, pos)) != string::npos) {
		sstr = str.substr(cpos, pos - cpos);
		cout << sstr << " ";
		pos += tofind.length();
		cpos = pos;
	}

	//erase
	//std::erase(str, ' '); // erase() c++20
	cout << endl;
}
//.................................................

void find_substr_str() {

	string str = "first 21 second 21 third ";
	cout << endl << "find_substr_str() for '21' in : " << str << endl;
	uint32_t pos = 0;
	uint32_t  lpos = 0; //last position
	string tofind = "21";
	while ((pos = str.find(tofind, pos)) != string::npos) {
		string ss = str.substr(lpos, pos - lpos);
		cout << ss << " ";
		pos += tofind.length();
		lpos = pos;
	}
	if (lpos < str.length())
		cout << str.substr(lpos, str.length() - lpos);

	cout << endl;
}
//.................................................
void string_remove_space()
{
	cout << endl << "string_remove_space()" << endl;

	std::string str1 = "Text with some   spaces \0";

	//1.
	auto noSpaceEnd = std::remove(str1.begin(), str1.end(), ' '); // <algorithm>

	cout << "noSpace iterator value " << *noSpaceEnd << endl; //noSpaceEnd  - iterator postion till the end is all are set to removal, but not removed till we call erase();	
	cout << "after remove() is called " << str1 << " " << str1.size() << endl;;

	// erasing all spaces
	str1.erase(noSpaceEnd, str1.end());
	cout << "after erase() is called " << str1 << " " << str1.size() << endl;;

	//2.
	// The spaces are removed from the string only logically.
	// Note, we use view, the original string is still not shrunk:
	cout << std::string_view(str1.begin(), noSpaceEnd) << " size: " << str1.size() << '\n'; // C++20
	cout << endl;
}

void run_string()
{
	string_remove_space();
	find_substr_str();
	string_split();
	//
}

//int main()
//{
//	run_string();
//	return 0;
//}

/*
	output -
		string_remove_space()
		noSpace iterator value p
		after remove() is called Textwithsomespacespaces  24
		after erase() is called Textwithsomespaces 18
		Textwithsomespaces size: 18 //std::string_view(str1.begin(), noSpaceEnd)


		find_substr_str() for '21' in : first 21 second 21 third
		first   second   third

		string_split() for '2' in : first 21 second 21 third
		using getline()
		first  1 second  1 third
		using strtok()
		first  1 second  1 third
*/
