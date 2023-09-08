#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
using namespace std;
/*
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, 2 is written as II in Roman numeral, just two ones added together. 12 is written as XII, which is simply X + II. The number 27 is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9.
X can be placed before L (50) and C (100) to make 40 and 90.
C can be placed before D (500) and M (1000) to make 400 and 900.
Given a roman numeral, convert it to an integer.



Example 1:

Input: s = "III"
Output: 3
Explanation: III = 3.
Example 2:

Input: s = "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.
Example 3:

Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

*/
class Solution {
public:
    int romanToInt(string s) {
        int sum{ 0 };
        for (int i = s.length() - 1; i > -1; --i)
        {

            int v = GetValue(s[i]);

            if (v == 5 || v == 10)  // V = 5, X = 10 
            {
                int m = i < 1 ? -1 : GetValue(s[i - 1]);
                if (m == 1) {
                    sum += (v - m);
                    --i; // move left
                }
                else {
                    sum += v;
                }
            }
            //
            else if (v == 50 || v == 100) // L = 50, C = 100
            {
                int m = i < 1 ? 0 : GetValue(s[i - 1]);
                if (m == 10) {
                    sum += (v - m);
                    --i; // move left
                }
                else {
                    sum += v;
                }
            }
            //
            else if (v == 500 || v == 1000) // D = 500, M = 1000 
            {
                int m = i < 1 ? 0: GetValue(s[i - 1]);
                if (m == 100) {
                    sum += (v - m);
                    --i;  // move left
                }
                else {
                    sum += v;
                }
            }
            //
            else
                sum += v;


        }
        return sum;

    }
    int GetValue(char ch) {

        switch (ch) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;


        }
        return 0;
    }

    int romanToInt_second(string str) {
        map<char, int> m;
        m.insert({ 'I', 1 });
        m.insert({ 'V', 5 });
        m.insert({ 'X', 10 });
        m.insert({ 'L', 50 });
        m.insert({ 'C', 100 });
        m.insert({ 'D', 500 });
        m.insert({ 'M', 1000 });
        int sum = 0;
        for (int i = 0; i < str.length(); i++)
        {
            /*If present value is less than next value,
              subtract present from next value and add the
              resultant to the sum variable.*/
            if (m[str[i]] < m[str[i + 1]])
            {
                sum += m[str[i + 1]] - m[str[i]];
                i++;
                continue;
            }
            sum += m[str[i]];
        }
        return sum;
    }
};
