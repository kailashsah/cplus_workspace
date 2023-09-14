#include <iostream>

using namespace std;

struct Node
{
	int i;
	Node* left;
	Node* right;

};

Node* newNode(int i)
{
	Node* p = new Node;
	p->i = i;
	p->left = nullptr;
	p->right = nullptr;
	return p;

}

#include <queue>
int GetSize(Node* root)
{
	int count = 0;
	queue<Node*> que;
	que.push(root);
	while (!que.empty())
	{
		Node* tmp = que.front();
		if (tmp->left)
			que.emplace(tmp->left);
		if (tmp->right)
			que.emplace(tmp->right);
		que.pop();
		count++;
	}
	return count;
}

int checkHalves(Node* node, int sum, int& ans)
{
	int l = 0, r = 0;
	if (node == nullptr)
		return 0;

	if (node->left)
	{
		l = checkHalves(node->left, sum, ans);
		if (l * 2 == sum)
			ans++;
	}
	if (node->right)
	{
		r = checkHalves(node->right, sum, ans);
		if (r * 2 == sum)
			ans++;

	}

	return node->i + l + r;
}

int find_sum(Node* node)
{
	if (node == nullptr)
		return 0;

	return node->i + find_sum(node->left) + find_sum(node->right);

}
Node* insertforSize()
{
	Node* root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);

	root->left->left = newNode(4);
	root->left->right = newNode(5);
	return root;
}

Node* insertHalfTree()
{
	Node* root = newNode(1);
	root->left = newNode(-1);
	root->right = newNode(-1);


	root->right->right = newNode(1);
	return root;
}
//int main()
//{
//	//Node* root = insertforSize();
//	Node* root = insertHalfTree();
//	cout << "tree size " << GetSize(root) << endl;
//	cout << "tree sum " << find_sum(root);
//	int ans = 0;
//	checkHalves(root, find_sum(root), ans);
//	cout << "tree possible " << ans << endl;
//	
//	return 0;
//}