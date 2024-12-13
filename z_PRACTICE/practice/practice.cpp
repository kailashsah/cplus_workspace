// practice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>

//#include <linked_list>
#include <forward_list>
#include <stack>
#include <queue>
using namespace std;
class Person {};
void ds()
{
    vector<int> v;
    v.push_back(1);
    v.emplace_back(1);
    for_each(v.begin(), v.end(), [](auto i) { cout << i << endl;  });

    set<string> s;
    unordered_set<string> uos;
    map<int, string> om;
    unordered_map <int, string> uom;
    list <string> sl;
    //linked_list<string> ll; // no linked_list
    forward_list <int> fl;
    
    // adaptors
    stack<string> st;
    queue<Person> que;


}


int main()
{
    std::cout << "starts ...\n";
    ds();
}

