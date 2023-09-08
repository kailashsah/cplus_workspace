#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
using namespace std;
/*
* Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.
 

Example 1:

Input: s = "()"
Output: true
Example 2:

Input: s = "()[]{}"
Output: true
Example 3:

Input: s = "(]"
Output: false
*/
#include <stack>
class Solution {
public:
    bool isValid(string s) {
        if (s.empty())
            return false;
        else if (s.length() < 2) // "]"
            return false;

        stack <char> st;
        char chtop;
        for (char ch : s) {

            if (ch == '[' || ch == '{' || ch == '(') {
                st.push(ch);
            }

            else if (ch == ']' || ch == '}' || ch == ')') {
                if (!st.empty())
                {
                    if (chtop = get_closing(st.top()); chtop == ch)
                        st.pop();
                    else
                        st.push(ch); // "(])"
                }
                else st.push(ch); // ")(){}"


            }


        }
        if (st.empty())
            return true;
        return false;
    }

    char get_closing(char ch) {
        if (ch == '[')
            return ']';
        else if (ch == '{')
            return '}';
        else if (ch == '(')
            return ')';
        else return 0;
    }
};
