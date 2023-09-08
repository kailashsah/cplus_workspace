#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
using namespace std;
/*
* You are given the heads of two sorted linked lists list1 and list2.

Merge the two lists in a one sorted list. The list should be made by splicing together the nodes of the first two lists.

Return the head of the merged linked list.

 Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]
Example 2:

Input: list1 = [], list2 = []
Output: []
Example 3:

Input: list1 = [], list2 = [0]
Output: [0]
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    
};
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* result = new ListNode(0);
        ListNode* dummyHead = result;
        ListNode* l1 = list1;
        ListNode* l2 = list2;
        int const MAX_NUM = -9999;
        while (l1 != nullptr || l2 != nullptr) {

            int x = l1 ? l1->val : MAX_NUM;
            int y = l2 ? l2->val : MAX_NUM;

            if (x != MAX_NUM && y == MAX_NUM)
            {
                result->next = new ListNode(x);
                result = result->next;
                l1 = l1 ? l1->next : nullptr;
            }

            else if (x == MAX_NUM && y != MAX_NUM) {
                result->next = new ListNode(y);
                result = result->next;
                l2 = l2 ? l2->next : nullptr;
            }
            else if (x < y) {
                result->next = new ListNode(x);
                result = result->next;
                l1 = l1 ? l1->next : nullptr;
            }
            else {
                result->next = new ListNode(y);
                result = result->next;
                l2 = l2 ? l2->next : nullptr;
            }
        }
        return dummyHead->next;
    }
};
