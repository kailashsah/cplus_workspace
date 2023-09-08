#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
using namespace std;
/*
3. Longest Substring Without Repeating Characters

Given a string s, find the length of the longest substring without repeating characters.
Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/
/*
*By using HashSet as a sliding window, checking if a character in the current can be done in O(1)O(1).

A sliding window is an abstract concept commonly used in array/string problems. A window is a range of elements in the array/string which usually defined by the start and end indices, i.e. [i, j)[i,j) (left-closed, right-open). A sliding window is a window "slides" its two boundaries to the certain direction. For example, if we slide [i, j)[i,j) to the right by 1 element, then it becomes [i+1, j+1)[i+1,j+1) (left-closed, right-open).

Back to our problem. We use HashSet to store the characters in current window [i, j)[i,j) (j = i j=i initially). Then we slide the index j to the right. If it is not in the HashSet, we slide jj further. Doing so until s[j] is already in the HashSet. At this point, we found the maximum size of substrings without duplicate characters start with index i. If we do this for all i, we get our answer.

*/
#include <set>
class Solution {
public:
    int lengthOfLongestSubstring(string s)    {
            unordered_map<char, int> chars;

            int left = 0;
            int right = 0;

            int res = 0;
            while (right < s.length()) {
                char r = s[right];
                chars[r]++;

                while (chars[r] > 1) {
                    char l = s[left];
                    chars[l]--;
                    left++;
                }

                res = max(res, right - left + 1);

                right++;
            }

            return res;
        }
    };
