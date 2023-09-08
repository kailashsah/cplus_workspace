#include <iostream>
using namespace std;

// https://leetcode.com/problems/median-of-two-sorted-arrays/submissions/ 

#include <vector>

class Solution {
public:
    double findMedianSortedArrays(vector<int>& num1, vector<int>& num2) {
        size_t pos1{};
        size_t pos2{};
        vector<int> merged;
        while (pos1 < num1.size() || pos2 < num2.size()) {

            if (pos1 < num1.size() && pos2 < num2.size()) {
                if (num1[pos1] < num2[pos2])
                {
                    merged.push_back(num1[pos1]);
                    pos1++;
                }
                else
                {
                    merged.push_back(num2[pos2]);
                    pos2++;
                }

            }

            else if (pos1 < num1.size()) {
                merged.push_back(num1[pos1]);
                ++pos1;
            }
            else if (pos2 < num2.size()) {
                merged.push_back(num2[pos2]);
                ++pos2;
            }
            // else
            // {
            //     break;
            // }


        }
        int mid = merged.size() / 2;
        if (merged.size() % 2 != 0)//odd
            return merged[mid];
        else {
            return (double)(merged[mid-1] + merged[mid]) / 2;
        }


    }
};

void run_arr_median()
{
    Solution s;
    vector<int> one{ 1, 2 };
    vector<int> two{ 3, 4 };
    cout << s.findMedianSortedArrays(one, two); // 2.5
}

//int main()
//{
//    run_arr_median();
//}



