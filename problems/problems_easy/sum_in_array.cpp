#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
using namespace std;
//1. Two sum
//2. Add Two Numbers 
/*
* Two sum -  Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
* 
Your input
[2, 7, 11, 15]
9
Output
[0, 1]
Expected
[0, 1]
*/
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // unordered_set<int> sett;
        unordered_map<int, int> mapp;
        vector<int> vec_result;
        for (auto itr = nums.begin(); itr != nums.end(); ++itr) {
            int temp = target - *itr;
            if (mapp.find(temp) != mapp.end()) {
                vec_result.push_back(mapp[temp]);  // get one index from map 
                vec_result.push_back(itr - nums.begin());  // another one from current iteration

                break;
            }
            mapp.insert(pair<int, int>(*itr, itr - nums.begin()));

        }
        return vec_result;


    }
};

/* Add Two Numbers


Add to List - You are given two non - empty linked lists representing two non - negative integers.The digits are stored in reverse order, and each of their nodes contains a single digit.Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.


Your input
[2,4,3]
[5,6,4]
Output
[7,0,8]
Expected
[7,0,8]

M note - here carry over goes to right
*/

 //Definition for singly-linked list.
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution_tree {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* result = nullptr; // used to return
        ListNode* temp = nullptr;
        ListNode* tail = nullptr;
        int carry = 0;
        while (true)
        {
            int one = 0, two = 0;
            if (l1)
                one = l1->val;
            if (l2)
                two = l2->val;
            int sum = one + two + carry;
            carry = 0;
            if (sum > 9)
            {
                carry = 1;
                int val = (10 - sum);
                temp = new ListNode(val);
            }
            else
                temp = new ListNode(sum, nullptr);

            if (result == nullptr) {
                result = temp;
                tail = result;

            }
            else {
                tail->next = temp;
                tail = tail->next;
            }


            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;

            if (l1 == nullptr && l2 == nullptr)
                break;

        }
        return result;
    }
public:
    ListNode * addTwoNumbers_correct(ListNode * l1, ListNode * l2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* curr = dummyHead;
        int carry = 0;
        while (l1 != NULL || l2 != NULL || carry != 0) {
            int x = l1 ? l1->val : 0;
            int y = l2 ? l2->val : 0;
            int sum = carry + x + y;
            carry = sum / 10;
            curr->next = new ListNode(sum % 10);
            curr = curr->next;
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }
        return dummyHead->next;
    }

};