#include <iostream>
using namespace std;


// https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/ - valid road
/*
You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.



Example 1:

Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6
Example 2:

Input: lists = []
Output: []
Example 3:

Input: lists = [[]]
Output: []
*/
  //Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};
#include <vector>

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int lCount = lists.size();
        ListNode* dummy = new ListNode(0);
        ListNode* head = dummy;
       
        while (!isListCompleted(lists)) {
            int min{ 9999 };
            int list_index{};
            for (size_t i{}; i < lists.size(); ++i) {

                if (lists[i] != nullptr && lists[i]->val <= min) { // check condition
                    min = lists[i]->val;
                    list_index = i;
                }

            }
            if (min != 9999) {
                lists[list_index] = lists[list_index]
                    ? lists[list_index]->next : nullptr;

                dummy->next = new ListNode(min);
                dummy = dummy->next;
            }
        } // while

        return head->next;
    }

    bool isListCompleted(vector<ListNode*>& lists) {
        for (size_t i{}; i < lists.size(); ++i) {

            if (lists[i] != nullptr)
                return false;
        }

        return true;


    }
    void print(ListNode* list) {
        while (list != nullptr) {
            
            cout << list->val << " ";
            list = list ? list->next : nullptr;
        }

    }
};
//
class Solution2{
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.empty()) {
        return nullptr;
    }
    while (lists.size() > 1) {
        lists.push_back(mergeTwoLists(lists[0], lists[1]));
        lists.erase(lists.begin());
        lists.erase(lists.begin());
    }
    return lists.front();
}
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr) {
        return l2;
    }
    if (l2 == nullptr) {
        return l1;
    }
    if (l1->val <= l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    }
    else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}
};
void run_merge_k()
{ 
    //lists = [[1, 4, 5], [1, 3, 4], [2, 6]]
    ListNode* first = new ListNode(1);
    ListNode* headFirst = first;
    first->next = new ListNode(4);
    first->next->next = new ListNode(5);
    //
    ListNode* second = new ListNode(1);
    ListNode* headSecond = second;
    second->next = new ListNode(3);
    second->next->next = new ListNode(4);
    //
    ListNode* third = new ListNode(2);
    ListNode* headThird = third;
    third->next = new ListNode(6);
    //
    vector<ListNode*> lists = {headFirst, headSecond, headThird   };
    Solution obj;
    Solution2 obj2;
    ListNode* ret = obj2.mergeKLists(lists); // [1,1,2,3,4,4,5,6]
    //obj.print(headThird);
    obj.print(ret);
}

//int main()
//{
//    run_merge_k();
//}



