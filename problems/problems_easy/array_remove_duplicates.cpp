#include <iostream>
using namespace std;

//https://leetcode.com/problems/remove-duplicates-from-sorted-array/submissions/
/*
Example 1:

Input: nums = [1,1,2]
Output: 2, nums = [1,2,_]
Explanation: Your function should return k = 2, with the first two elements of nums being 1 and 2 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).
Example 2:

Input: nums = [0,0,1,1,1,2,2,3,3,4]
Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
Explanation: Your function should return k = 5, with the first five elements of nums being 0, 1, 2, 3, and 4 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).
*/
#include <set>
#include <vector>

class Solution {
public:
	
	int removeDuplicates(vector<int>& nums) {
		set<int> ints;
		for (auto i : nums) {
			ints.insert(i);
		}
		set<int>::iterator itr = ints.begin();
		for (int i{}; i < ints.size(), itr != ints.end(); ++i, ++itr) {
			nums[i] = *itr;
		}
		return ints.size();

	}


	// faster solution
	int removeDuplicates_second(vector<int>& nums) {

		int retEle{};
		int pos{};
		int pEle{ -1111 };
		for (auto itr = nums.begin(); itr != nums.end(); ++itr) {
			if (*itr == pEle)
				continue;
			else
			{
				if (nums[pos] != *itr)
					nums[pos] = *itr;
				++pos; ++retEle;
				pEle = *itr;

			}
		}
		return retEle;

	}


};

void run_dup() {
	Solution s;
	vector<int> nums = { 1, 1, 2 };
	cout << s.removeDuplicates_second(nums); // return unique elem count

}

//int main()
//{
//	run_dup();
//}
