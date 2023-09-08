#include <iostream>
#include <list>
#include <iomanip>
#include <stack>

using namespace std;
namespace dfs_search {

	/*
	Complexity Analysis:
	Time complexity: O(V + E), where V is the number of vertices and E is the number of edges in the graph.
	Space Complexity: O(V).
	Since, an extra visited array is needed of size V.
	*/

	class Graph {

	public:
		Graph(int v);
		void addEdge(int v, int w);
		void dfs_recursive(int vertex, bool visited[]);
		void dfs_iterative_using_stack(int vertex, bool visited[]);
		void Graph::bfs_using_queue(int s);
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

	void Graph::dfs_recursive(int vertex, bool visited[]) {
		visited[vertex] = true;
		cout << vertex << setw(4);

		for (auto it = adj[vertex].begin(); it != adj[vertex].end(); it++) {
			if (visited[*it] == false)
				dfs_recursive(*it, visited);
		}

	}
	void Graph::dfs_iterative_using_stack(int vertex, bool visited[])
	{
		stack<int> dfs_stack;
		dfs_stack.push(vertex);
		while (!dfs_stack.empty())
		{
			vertex = dfs_stack.top();
			dfs_stack.pop();

			if (!visited[vertex])
			{
				visited[vertex] = true;
				cout << vertex << setw(4);
			}

			for (auto it = adj[vertex].begin(); it != adj[vertex].end(); it++) {
				if (visited[*it] == false)
					dfs_stack.push(*it);// dfs_traverse(*it, visited);
			}
		}
		

	}

	void Graph::bfs_using_queue(int s)
	{
		// initially none of the vertices is visited
		bool *visited = new bool[vertices];
		for (int i = 0; i < vertices; i++)
			visited[i] = false;

		// queue to hold BFS traversal sequence 
		list<int> queue;

		// Mark the current node as visited and enqueue it 
		visited[s] = true;
		queue.push_back(s);

		// iterator 'i' to get all adjacent vertices 
		list<int>::iterator i;

		while (!queue.empty())
		{
			// dequeue the vertex 
			s = queue.front();
			cout << s << " ";
			queue.pop_front();

			// get all adjacent vertices of popped vertex and process each if not already visited 
			for (i = adj[s].begin(); i != adj[s].end(); ++i)
			{
				if (!visited[*i])
				{
					visited[*i] = true;
					queue.push_back(*i);
				}
			}
		}
	}

	void driver_code_bfs_recursive()
	{	
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
		g.dfs_recursive(2, visited);  // output should be 2 0 1 3
	}

	void driver_code_bfs_iterative()
	{
		int size = 5;
		Graph gidfs(5);  //create graph 
		gidfs.addEdge(0, 1);
		gidfs.addEdge(0, 2);
		gidfs.addEdge(0, 3);
		gidfs.addEdge(1, 2);
		gidfs.addEdge(2, 4);
		gidfs.addEdge(3, 3);
		gidfs.addEdge(4, 4);

		bool *visited = new bool[size];
		for (int i = 0; i < size; i++)
			visited[i] = false;
		cout << "Output of Iterative Depth-first traversal:\n";
		gidfs.dfs_iterative_using_stack(0, visited);  // 0 3 2 4 1
		//gidfs.dfs_recursive(0, visited);   // 0 1 2 4 3 
	}

	void driver_code_dfs_using_queue()
	{
		// create a graph 
		Graph dg(5);
		dg.addEdge(0, 1);
		dg.addEdge(0, 2);
		dg.addEdge(0, 3);
		dg.addEdge(1, 2);
		dg.addEdge(2, 4);
		dg.addEdge(3, 3);
		dg.addEdge(4, 4);

		cout << "Breadth First Traversal for given graph (with 0 as starting node): " << endl;
		dg.bfs_using_queue(0);  // 0 1 2 3 4
	}

	int main() {

		//driver_code_bfs_recursive();
		//driver_code_bfs_iterative();

		driver_code_dfs_using_queue();
		return 0;
	}

}

/*
int main ()
{
	dfs_search::main();
	getchar();
	return 0;
}
*/



