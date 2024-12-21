// practice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <array>
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

    array<int, 2>  arr_of_two;

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

    cout << "priority_queue" << endl;
    //priority_queue<int> pq;
    priority_queue<int, vector<int>, less<int>> pq; // max heap
    pq.push(2);
    pq.push(1);
    for (int i = 0; pq.size(); i++) {
        cout << pq.top() << endl;
        pq.pop();
    }

}


int main()
{
    std::cout << "starts ...\n";
    ds();
}

