#include <iostream>
using namespace std;

// url https://www.geeksforgeeks.org/topological-sorting/ 
/*

*/

#include <vector>
#include <list>
#include <queue>
void topological_sort(int vertices, vector<vector<int>>& input)
{
	// 1. create indegree vector count (for all vertex)
	// 2. loop indeg,get items whose count is zero
	// 3. while leaf_que is not empty
	vector<int> indeg(vertices, 0);
	list<int>* adj = new list<int>[vertices];
	for (size_t i{}; i < input.size(); ++i) {
		int u = input[i][0];
		int v = input[i][1];
		//adj[i].push_back(input[i][1]);
		adj[u].push_back(v);
		indeg[v]++;
	}
	
	queue<int> leaf_que;
	for (int i{}; i < indeg.size(); ++i) {
		if (indeg[i] == 0)
			leaf_que.push(i);

	}
	while (!leaf_que.empty()) {
		// take out from que
		// iterate the adj of front item
		// decrement the indeg by 1
		// if indegree 0, push to queue again
		int front = leaf_que.front();
		leaf_que.pop();
		cout << front << " ";
		for (auto m : adj[front]) { // m-> member of adjacency
			indeg[m]--;
			if (indeg[m] == 0) {
				leaf_que.push(m);
			}
		}
		
	}

}

void run_graph() {
	// ...........................................
	// this is suitable of array
	vector<vector<int>> in_vec = {
		{1,2},{3,4},{5,6}
	}; // can't be used as a adjacency list
	for (int i{}; i < in_vec.size(); ++i) {
		cout << in_vec[i][1] << " ";
	}
	cout << endl;
	// ...........................................
	//create adjacency list
	if (0) {
		vector<vector<int>> in_vec2 = {
			{1,2},{3,4},{5,6}
		};
		list<int>* adj = new list<int>[in_vec2.size()];
		for (size_t i{}; i < in_vec2.size(); ++i) {

			adj[i].push_back(in_vec2[i][1]);
		}
	}
	// ...........................................
	// topological sort
	vector<vector<int>> in_vec2 = {
			{5,2},{5,0},{4,0},{4,1}, {2,3},{3,1}
	};
	int vertices{ 6 };
	topological_sort( vertices, in_vec2); // 4 5 2 0 3 1
	// ...........................................

}

//int main()
//{
//	run_graph();
//}

