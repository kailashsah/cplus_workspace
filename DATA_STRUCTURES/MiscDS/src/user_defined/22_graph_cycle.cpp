// detect cycle in a graph

#include<iostream>
#include <list>
using namespace std;
/*
	1. Graph DS - https://medium.com/@vinay.vashist2003/graphs-data-structure-in-c-ab7b4205f41a

	2. depth first traversal
	3. breadth first traversal
*/
class Graph
{
	int V;    // No. of vertices
	bool isCyclicUtil(int v, bool visited[], bool* rs);  // used by isCyclic()
public:
	list<int>* adj;    // Pointer to an array containing adjacency lists

	Graph(int V);   // Constructor
	void addEdge(int v, int w);   // to add an edge to graph
	bool isCyclic_caller();    // returns true if there is a cycle in this graph
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
}

// This function is a variation of DFSUtil() in 
// https://www.geeksforgeeks.org/archives/18212
bool Graph::isCyclicUtil(int v, bool visited[], bool* recStack)
{
	if (visited[v] == false)
	{
		// Mark the current node as visited and part of recursion stack
		visited[v] = true;
		recStack[v] = true;

		// Recur for all the vertices adjacent to this vertex
		list<int>::iterator i;
		for (i = adj[v].begin(); i != adj[v].end(); ++i)
		{
			if (!visited[*i] && isCyclicUtil(*i, visited, recStack))
				return true;
			else if (recStack[*i])
				return true;
		}

	}
	recStack[v] = false;  // remove the vertex from recursion stack
	return false;
}

// Returns true if the graph contains a cycle, else false.
// This function is a variation of DFS() in 
// https://www.geeksforgeeks.org/archives/18212
bool Graph::isCyclic_caller()
{
	// Mark all the vertices as not visited and not part of recursion
	// stack
	bool* visited = new bool[V];
	bool* recStack = new bool[V];
	for (int i = 0; i < V; i++)
	{
		visited[i] = false;
		recStack[i] = false;
	}

	// Call the recursive helper function to detect cycle in different
	// DFS trees
	for (int i = 0; i < V; i++)
		if (!visited[i] && isCyclicUtil(i, visited, recStack))
			return true;

	return false;
}
//......................DFS traversal
#include <vector>
#include <unordered_map>
void dfs(vector<int>& answer, unordered_map<int, bool>& visited, int node, list<int>* adj) {
	visited[node] = true;
	answer.push_back(node);

	for (auto item : adj[node]) {
		if (!visited[item])
			dfs(answer, visited, item, adj);
	}
}
vector<int> dfs_of_graph_caller(list<int>* adj) {	
	cout << "depth first traversal" << endl;

	vector<int> answer;
	unordered_map<int, bool> visited;

	for (auto item : *adj) {
		if (!visited[item])
			dfs(answer, visited, item, adj);
	}
	return answer;
}
//......................DFS traversal <end>

//......................BFS traversal
#include <queue>
void bfs(vector<int>& answer, unordered_map<int, bool>& visited, int node, list<int>* adj) {
	visited[node] = true;
	queue<int> que; //use queue ds here
	que.push(node);
	answer.push_back(node); // whenever there is push in que, there shuld be push in answer vector also.

	while (!que.empty()) {
		int node_front = que.front();
		que.pop();

		for (auto neighbour : adj[node_front]) {
			if (!visited[neighbour]) {
				visited[neighbour] = true;
				que.push(neighbour);
				answer.push_back(neighbour);
			}
		}

	}
}

vector<int> bfs_of_graph_caller(list<int>* adj) {
	cout << "breadth first traversal" << endl;
	vector<int> answer;
	unordered_map<int, bool> visited;

	for (auto node : *adj) {
		if (!visited[node])
			bfs(answer, visited, node, adj);
	}
	return answer;
}
//......................BFS traversal <end>

void graph_cyclecpp()
{
	// Create a graph given in the above diagram
	const int vertices = 4;
	Graph g(vertices);
	g.addEdge(0, 1);
	//g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
   // g.addEdge(2, 3);
   // g.addEdge(3, 3);

	//1.
	if (g.isCyclic_caller())
		cout << "Graph contains cycle" << endl;
	else
		cout << "Graph doesn't contain cycle" << endl;

	//2.
	vector<int> result_nodes = dfs_of_graph_caller(g.adj);	
	copy(result_nodes.begin(), result_nodes.end(), ostream_iterator<int>(cout, " ")); // 1 2
	cout << endl;

	//3.	
	vector<int> result = bfs_of_graph_caller(g.adj);
	copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

//int main()
//{
//	graph_cyclecpp();
//	return 0;
//}