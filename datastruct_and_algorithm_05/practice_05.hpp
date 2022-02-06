#pragma once

#include <iostream>
#include <queue>
using namespace std;

//LeetCode

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

};

//Invert Binary Tree（翻转二叉树）/problems/invert-binary-tree/
TreeNode* invertTree(TreeNode* root) {
	//队列层序遍历
	if (root == nullptr) return nullptr;
	queue<TreeNode*> q;
	q.push(root);
	TreeNode* tmp,*ttmp;
	while (!q.empty())
	{
		tmp = q.front();
		q.pop();
		ttmp = tmp->left;
		tmp->left = tmp->right;
		tmp->right = ttmp;
		if (tmp->left != nullptr) q.push(tmp->left);
		if (tmp->right != nullptr) q.push(tmp->right);
	}
	return root;

	//递归前序遍历
	if (root != nullptr)
	{
		TreeNode* tmp = root->left;
		root->left = root->right;
		root->right = tmp;
		invertTree(root->left);
		invertTree(root->right);
	}
	return root;
}

//Maximum Depth of Binary Tree（二叉树的最大深度）/problems/maximum-depth-of-binary-tree/
void maxDepth(TreeNode* root, int depth)
{
	if (root == nullptr) return;
	if (root->left == nullptr && root->right == nullptr) answer = max(answer, depth);//走到叶子节点，计算一次最大值
	maxDepth(root->left, depth + 1);
	maxDepth(root->right, depth + 1);
}
int answer = 0;
int maxDepth(TreeNode* root) {
	maxDepth(root, 1);
	return answer;

	//简洁
	if (root == nullptr) return 0;
	return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

//Validate Binary Search Tree（验证二叉查找树）/problems/validate-binary-search-tree/
void order(TreeNode* root, vector<int>& vec)
{
	if (root == nullptr) return;
	order(root->left, vec);
	vec.push_back(root->val);
	order(root->right, vec);
}
bool isValidBST(TreeNode* root)
{
	if (root == nullptr) return false;
	//中序遍历得到有序数组
	vector<int> nums;
	order(root, nums);
	//遍历一遍数组看是否有不符合顺序的
	for (int i = 0; i < nums.size() - 1; ++i)
		if (nums[i] >= nums[i + 1]) return false;
	return true;
}
//不使用额外空间的做法
bool checkvalid(TreeNode* root, TreeNode* small, TreeNode* big)
{
	if (!root) return true;

	if (small && (small->val >= root->val) ||
		big && (big->val <= root->val)) return false;

	bool leftd = checkvalid(root->left, small, root);//检查左子树
	bool rightd = checkvalid(root->right, root, big);//检查右子树

	return leftd && rightd;//左右检查都没问题
}

//Path Sum（路径总和）/problems/path-sum/
bool hasPathSum(TreeNode* root, int targetSum) {
	//前序遍历
	if (root == NULL) return false;

	//we reached here,i.e the root is not NULL, so we took the root value in our sum, and remaining targetSum is targetSum-root value.
	targetSum = targetSum - root->val;

	//if the current node is a leaf and its value is equal to the sum, we've found a path
	if (targetSum == 0 && root->left == NULL && root->right == NULL) return true;

	// recursively call to traverse the left and right sub-tree
	// return true if any of the two recursive call return true
	return hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum);
}