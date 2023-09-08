#include <iostream>
using namespace std;

//https://leetcode.com/problems/symmetric-tree/
/*
Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).
Input: root = [1,2,2,3,4,4,3]
Output: true
Input: root = [1,2,2,null,3,null,3]
Output: false

*/

// Two solutions 
//bool isSymmetric(TreeNode* root) - > recursion
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
	
};

size_t len(TreeNode* node) {
	if (node == nullptr)
		return 0;
	
	return 1 + len(node->left) + len(node->right);
}

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr)
            return true;
        return areSym(root->left, root->right);

    }

    bool areSym(TreeNode* one, TreeNode* two) {
        if (one == nullptr && two == nullptr) return true;
        if (len(one) != len(two)) return false;
        if (one->val != two->val) return false;

        if (one == nullptr && two != nullptr) return false;
        if (one != nullptr && two == nullptr) return false;

        return areSym(one->left, two->right)
            && areSym(one->right, two->left);

    }

    size_t len(TreeNode* one) {
        if (one == nullptr) return 0;
        return len(one->left) + len(one->right) + 1;

    }
	bool isSymmetricByQueue(TreeNode* root) {
		if (root == nullptr)
			return true;
		return areSym(root->left, root->right);

	}
};
void run_tree() {
	// Test 1
	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->left->left = new TreeNode(3);
	root->left->right = new TreeNode(4);
	//
	root->right = new TreeNode(2);

	cout << "length of tree is : "<< len(root) << endl; // 5
	// ...........................................
	
	// Test 2
	//Input: root = [1, 2, 2, 3, 4, 4, 3]
	//Output : true

	TreeNode* root_s = new TreeNode(1);
	root_s->left = new TreeNode(2);
	root_s->left->left = new TreeNode(3);
	root_s->left->right = new TreeNode(4);
	//
	root_s->right = new TreeNode(2);
	root_s->right->left = new TreeNode(4);
	root_s->right-> right = new TreeNode(3);
	Solution obj;
	cout << std::boolalpha;
	cout << "is tree symmetric (boolalpha is set), right ans is true: ";
	cout << obj.isSymmetric(root_s)<< endl;

	//Input: root = [1, 2, 2, null, 3, null, 3]
	//Output : false
	// 
	TreeNode* root_ss = new TreeNode(1);
	root_ss->left = new TreeNode(2);
	root_ss->left->left = new TreeNode(0);
	root_ss->left->right = new TreeNode(3);
	//
	root_ss->right = new TreeNode(2);
	root_ss->right->left = new TreeNode();
	root_ss->right->right = new TreeNode(3);
	Solution obj_ss;
	cout << std::boolalpha;
	cout << "is tree symmetric (boolalpha is set), right ans is false: ";
	cout << obj_ss.isSymmetric(root_ss) << endl;
	// ...........................................
}

//int main()
//{
//	run_tree();
//}

