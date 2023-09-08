#include <iostream>
using namespace std;

// https://www.geeksforgeeks.org/depth-first-traversal-dfs-on-a-2d-array/
const int ROW = 3, COL = 3;

void some_func(int arr1[][3]) // valid
{

}

int isValid(int row, int col, int visited[][COL]) {

	if (row >= ROW || col >= COL || row < 0 || col < 0)
		return false;

	if (visited[row][col])
		return false;

	return true;
}
#include <stack>
int dirx[] = { -1, 1, 0, 0 }; // todo
int diry[] = { 0, 0, 1, -1 };
void dfs(int row, int col, int arr[][COL], int visited[][COL]) {

	//if (!isValid(row, col, visited))
		//return;

	stack<pair<int, int>> st;
	st.push(make_pair(row, col));

	while (!st.empty()) {

		pair<int, int> dim = st.top();
		st.pop();
		int r = dim.first;
		int c = dim.second;
		if (!isValid(r, c, visited))
			continue;
		//if (visited[r][c]) continue;

		cout << arr[r][c] << " ";
		visited[r][c] = true;


		for (int i{}; i < 4; ++i) {
			int x = r + dirx[i];
			int y = c + diry[i];
			st.push({ x, y });
		}
	}

}

int dfs_array()
{
	int arr[][3] = {
		{-1, 2, 3},
		{0, 9, 8},
		{1, 0, 1}
	}; // arr': missing subscript

	int visited[ROW][COL];
	memset(visited, 0, sizeof(visited));
	dfs(0, 0, arr, visited);  //-1 2 3 8 9 0 1 0 1 -> it may result different depends upon direction array

	return 1;
}
void run_dfs()
{
	dfs_array();
}

//int main()
//{
//	run_dfs();
//}



