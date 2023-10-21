#include <iostream>
using namespace std;
/*
	1. stringstream, ostringstream classes are stringBuilder class in c++.
	2. ostringstream is an output stream, i.e. one that you can only write to. stringstream is a stream that allows you to both read and write with the >> and << operators
    3. purpose - It is useful if we have lot of concatenations, at last we can take the final string like stringsteam.str().

*/
#include<sstream>
//1.
void run_ostringstream()
{
	ostringstream str1;
	string name = "Hazal";
	int age = 12;
	str1 << "The name is: " << name << endl;
	str1 << "The age is: " << age << endl;
	cout << str1.str() << endl;
}
//2.
void run_stringstream() {
    std::stringstream str1;
    std::string my_name = "Hamza";
    int my_age = 22;

    // Insert data into the string stream
    str1 << "My name is " << my_name << " and I am " << my_age << " years old.";

    // Get the string from the stringstream
    std::string final_result = str1.str();

    // Print the result
    std::cout << "The inserted string is :" << final_result << std::endl;

    // Clear the stringstream
    str1.str("");

    // Modify the string
    my_name = "Ali";
    my_age = 25;

    // Insert new data into the stringstream
    str1 << "My name is " << my_name << " and I am " << my_age << " years old.";

    // Get the modified string from the string stream
    final_result = str1.str();

    // Print the changed string
    std::cout << "The modified string is :" << final_result << std::endl;

}

//int main()
//{
//	run_ostringstream();
//  run_stringstream();
//	return 0;
//}
