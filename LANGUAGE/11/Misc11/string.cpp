#include <iostream>
#include <string>
using namespace std;


#include <sstream>
void string_split() {
	string str = "first 21 second 21 third ";
	stringstream ss(str);
	string strr;
	while (getline(ss, strr, '2')) {
		cout << strr << " ";
	}

	cout << endl;
	char* token = strtok(const_cast<char*>(str.data()), "21");
	while (token != nullptr) {
		cout << token << " ";
		token = strtok(0, "21");

	}
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

void find_str_str() {
	string str = "first 21 second 21 third ";
	uint32_t pos = 0;
	uint32_t  lpos = 0;
	string tofind = "21";
	while ((pos = str.find(tofind, pos)) != string::npos) {
		string ss = str.substr(lpos, pos - lpos);
		cout << ss << " ";
		pos += tofind.length();
		lpos = pos;
	}
	if (lpos < str.length())
		cout << str.substr(lpos, str.length() - lpos);

}
//.................................................
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