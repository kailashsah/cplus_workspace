#include "iostream" 
#include "unordered_map" 
#include <unordered_set>

using namespace std;

namespace array_remove_duplicates {

	void removeDups_set(int arr[], int n)
	{
		// Hash map which will store the 
		// elements which has appeared previously. 
		unordered_set<int> st;

		for (int i = 0; i < n; ++i) {

			// Print the element if it is not 
			// there in the hash map 
			if (st.find(arr[i]) == st.end()) {
				//cout << arr[i] << " ";
			}

			// Insert the element in the hash map 
			//mp[arr[i]] = true;
			st.insert(arr[i]);
		}
		for (auto item : st)
		{
			cout << item << " ";
		}

	}

	void removeDups_map(int arr[], int n)
	{
		// Hash map which will store the 
		// elements which has appeared previously. 
		unordered_map<int, bool> mp;

		for (int i = 0; i < n; ++i) {

			// Print the element if it is not 
			// there in the hash map 
			if (mp.find(arr[i]) == mp.end()) {
				//cout << arr[i] << " ";
			}

			// Insert the element in the hash map 
			mp[arr[i]] = true;
		}
		for (auto item : mp)
		{
			cout << item.first << " ";
		}
	}


	int main()
	{
		//int arr[] = { 1, 2, 5, 1, 7, 2, 4, 2 };
		int arr[] = { 4, 4, 0, 0, 1, 1, 1, 2, 2, 3, 3, 4 };  // output: [4, 0, 1, 2, 3]
		int n = sizeof(arr) / sizeof(arr[0]);
		
		//removeDups_map(arr, n);
		removeDups_set(arr, n);
		
		return 0;
	}
}

/*

int main()
{
	array_remove_duplicates::main();
	getchar();
	return 0;
}
*/