#include <iostream>
#include <list>
#include <iomanip>

using namespace std;
namespace dfs_search {

	/*Complexity Analysis:
	Time complexity: O(V + E), where V is the number of vertices and E is the number of edges in the graph.
	Space Complexity: O(V).
	Since, an extra visited array is needed of size V.*/

	class Graph {

	public:
		Graph(int v);
		void addEdge(int v, int w);
		void dfs_traverse(int vertex, bool visited[]);

	private:
		int vertices = 0;
		list<int> *adj;

	};

	Graph::Graph(int v) {
		vertices = v;
		adj = new list<int> [vertices];
	}

	void Graph::addEdge(int v, int w) {
		adj[v].push_back(w);
	}

	void Graph::dfs_traverse(int vertex, bool visited[]) {
		visited[vertex] = true;
		cout << vertex << setw(4);

		for (auto it = adj[vertex].begin(); it != adj[vertex].end(); it++) {
			if (visited[*it] == false)
				dfs_traverse(*it, visited);
		}

	}
	int main() {

		int size = 4;
		Graph g(size);
		bool *visited = new bool[size];
		for (int i = 0; i < size; i++)
			visited[i] = false;

		g.addEdge(0, 1);
		g.addEdge(0, 2);
		g.addEdge(1, 2);
		g.addEdge(2, 0);
		g.addEdge(2, 3);
		g.addEdge(3, 3);
		g.dfs_traverse(2, visited);  // output should be 2 0 1 3

		return 0;
	}

}

/*
int main ()
{
	dfs_search::main();
	return 0;
}
*/

