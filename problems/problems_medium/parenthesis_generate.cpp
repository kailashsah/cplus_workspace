#include <iostream>
using namespace std;

// https://leetcode.com/problems/generate-parentheses/
/*Generate Parentheses
Medium

15595

600

Add to List

Share
Given n pairs of parentheses, write a function to generate all combinations of well - formed parentheses.



Example 1:

Input: n = 3
Output : ["((()))", "(()())", "(())()", "()(())", "()()()"]
Example 2 :

    Input : n = 1
    Output : ["()"]
  */
#include <vector> 
class Solution {
public:

    void helper(vector<string>& v, int n, int oc, int cc, string s) {
        //base case
        if (oc == n && cc == n) {
            v.push_back(s);
            return;
        }

        if (oc < n) {
            helper(v, n, oc + 1, cc, s + "(");
        }

        if (cc < oc) {
            helper(v, n, oc, cc + 1, s + ")");
        }

    }


    vector<string> generateParenthesis(int n) {

        vector<string> v;
        int oc = 0, cc = 0;
        helper(v, n, oc, cc, "");
        return v;
    }
};

void run_gen_paren()
{
    Solution obj;
    auto strings = obj.generateParenthesis(2);
    for (auto s : strings)
        cout << s << endl;
}

//int main()
//{
//	run_gen_paren();
//}
//


