#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

map <char, list<char>> adj;
map <char, bool> visited_org;
map <char, bool> visited;
//
void addEdge(char a, char b) {
    adj[a].push_back(b);
}
//
void traverse(char v) {
    if (visited[v])
        return;

    visited[v] = true;
    list<char>::iterator itr, itr1;
    for (itr = adj[v].begin(); itr != adj[v].end(); ++itr) {
        if (!visited[*itr])
            traverse(*itr);
        for (itr1 = adj[*itr].begin(); itr1 != adj[v].end(); ++itr1)
            traverse(*itr1);
    }
}
//
bool checkAllVisited() {
    bool allflagged = true;
    for (auto ele : visited) {
        cout << ele.first;
        if (!ele.second) {

            return false;
        }

    }//for
    cout << endl;
    return true;
}
//
vector< vector <char>> node_inputs;
void fill_node_inputs(string line) {
    string token;
    stringstream ss(line);
    vector <char> inputs;
    while (getline(ss, token, ',')) {
        inputs.push_back(token[0]); // it is char
    }
    node_inputs.push_back(inputs);
}
//
void run_bp_question() {
    string line;
    while (getline(cin, line)) {
        //cout << line << endl;
        // create the graph
        // addEdge (a, b); // --> create adj, represents directed graph
        if (line.find("->") != string::npos) {
            char a = line[0];
            char b = line[3];
            addEdge(a, b);
            visited_org[a] = false;
            visited_org[b] = false;
            //cout << a<<b;
        }
        else if (line.find(",") != string::npos) {
            fill_node_inputs(line);
        }
    }

    // for node inputs to check (e.g.  a,q,w) 
    //call traversal(a), traversal(q), traversal(w)
    for (auto itr = node_inputs.begin(); itr != node_inputs.end(); ++itr) {
        auto input_one_set = *itr;
        visited = visited_org;
        for (auto ele : input_one_set) {

            traverse(ele);
        }

        // check all visited (second param 'bool') becomes true
        // if all elements of visited set to true return true else false
        if (checkAllVisited())
            cout << "True" << endl;
        else
            cout << "False" << endl;

        visited.clear();

    }//for
}
//
//int main() {
//    run_bp_question();
//
//    return 0;
//}


