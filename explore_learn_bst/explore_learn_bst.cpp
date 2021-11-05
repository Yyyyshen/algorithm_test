// explore_learn_bst.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>

//
//leetcode-explore-learn-binary-search-tree
//

using namespace std;

//
//概念
// 二叉树的特殊形式
// 每个节点值必须大于等于左子树任何值
// 每个节点值必须小于等于右子树任何值
//

//
//验证二叉搜索树
// 
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
class Solution1_1 {
public:
	void order(TreeNode* root, vector<int>& vec) {
		if (root == nullptr) return;
		order(root->left, vec);
		vec.push_back(root->val);
		order(root->right, vec);
	}
	bool isValidBST(TreeNode* root) {
		if (root == nullptr) return false;
		vector<int> vec_nums;
		order(root, vec_nums);
		int size = vec_nums.size();
		for (int i = 0; i < size - 1; ++i)
		{
			if (vec_nums[i] > vec_nums[i + 1]) return false;
		}
		return true;
	}
};
// 
//迭代器
class BSTIterator {
private:
	vector<int> m_nums;
	int cur = 0;
public:
	BSTIterator(TreeNode* root) {
		inOrder(root);
	}

	int next() {
		if (!hasNext()) return -1;
		return m_nums[cur++];
	}

	bool hasNext() {
		if (cur >= m_nums.size()) return false;
		return true;
	}

	void inOrder(TreeNode* root)
	{
		if (root == nullptr) return;
		inOrder(root->left);
		m_nums.push_back(root->val);
		inOrder(root->right);
	}
};
// 
//

//
//BST操作
// 
// 在BST中搜索
class Solution2_1 {
public:
	//迭代
	TreeNode* searchBST(TreeNode* root, int val) {
		if (root == nullptr) return nullptr;
		TreeNode* ret = root;
		while (ret)
		{
			int node_val = ret->val;
			if (node_val == val) return ret;
			if (node_val > val)
			{
				ret = ret->left;
			}
			else {
				ret = ret->right;
			}
		}
		return ret;
	}
	//递归
	TreeNode* searchBST2(TreeNode* root, int val)
	{
		if (root == nullptr)
			return nullptr;

		if (root != nullptr && root->val == val)
			return root;

		if (val < root->val && root->left != nullptr)
			return searchBST2(root->left, val);

		if (val > root->val && root->right != nullptr)
			return searchBST2(root->right, val);

		return nullptr;
	}
};
// 
// 插入操作
//	首要是寻找合适的位置
//	先根据新值和当前树每个节点关系搜索，直到找到一个外部节点，添加新值
class Solution2_2 {
public:
	TreeNode* insertIntoBST(TreeNode* root, int val) {
		if (root == nullptr)
			return new TreeNode(val);
		TreeNode* pre_loc = root, * insert_loc = root;
		while (insert_loc)
		{
			int cur_val = insert_loc->val;
			if (cur_val == val) return root;
			pre_loc = insert_loc;
			if (cur_val > val) insert_loc = insert_loc->left;
			if (cur_val < val) insert_loc = insert_loc->right;
		}
		if (val > pre_loc->val) pre_loc->right = new TreeNode(val);
		if (val < pre_loc->val) pre_loc->left = new TreeNode(val);
		return root;
	}
	//递归
	TreeNode* insertIntoBST2(TreeNode* root, int val) {
		if (root == nullptr)
			return new TreeNode(val);
		if (root->val > val)
			root->left = insertIntoBST2(root->left, val);
		if (root->val < val)
			root->right = insertIntoBST2(root->right, val);
		return root;
	}
};
// 
// 删除操作
//	如果没有子节点，直接删除
//	一个子节点，则用子节点代替
//	含多个子节点，用有序后继节点或前驱节点替换后删除
class Solution2_3 {
public:
	TreeNode* deleteNode(TreeNode* root, int key) {
		if (root == nullptr) return nullptr;
		if (root->val > key)
			root->left = deleteNode(root->left, key);
		else if (root->val < key)
			root->right = deleteNode(root->right, key);
		else
		{
			if (root->left == nullptr && root->right == nullptr)
			{
				delete root;
				return nullptr;
			}
			else if (root->left == nullptr)
			{
				TreeNode* node = root;
				root = root->right;
				delete node;
			}
			else if (root->right == nullptr)
			{
				TreeNode* node = root;
				root = root->left;
				delete node;
			}
			else
			{
				TreeNode* temp = root->right;
				while (temp->left) {
					temp = temp->left;
				}
				root->val = temp->val;
				root->right = deleteNode(root->right, temp->val);
			}
		}
		return root;
	}
};
// 
//

int main()
{
	std::cout << "Hello World!\n";
}
