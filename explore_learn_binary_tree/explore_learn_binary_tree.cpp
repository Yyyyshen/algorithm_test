// explore_learn_binary_tree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <queue>

//
//leetcode-explore-learn-binary-tree
//

using namespace std;

//
//遍历方式
// 前序、中序、后序
// 前中后指的是根遍历的顺序，分别是 根左右 、 左根右 、 左右根
// 
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
// 前序遍历
class Solution1_1 {
public:
	void pre_trace(TreeNode* root, vector<int>& vec)
	{
		if (root != nullptr)
		{
			vec.push_back(root->val);  //递归最简单的方法，三行代码，前中后序即是把处理根这句放在前中后三个位置
			pre_trace(root->left, vec);
			pre_trace(root->right, vec);
		}
	}
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> ret;
		pre_trace(root, ret);
		return ret;
	}
};
// 中序遍历
class Solution1_2 {
public:
	void in_trace(TreeNode* root, vector<int>& vec)
	{
		if (root != nullptr)
		{
			in_trace(root->left, vec);
			vec.push_back(root->val);
			in_trace(root->right, vec);
		}
	}
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> ret;
		in_trace(root, ret);
		return ret;
	}
};
// 后序遍历
class Solution1_3 {
public:
	void post_trace(TreeNode* root, vector<int>& vec)
	{
		if (root == nullptr)
			return;
		post_trace(root->left, vec);
		post_trace(root->right, vec);
		vec.push_back(root->val);
	}
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> ret;
		post_trace(root, ret);
		return ret;
	}
};
//  
// 
// 层序遍历，广度优先遍历
class Solution1_4 {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> ret;
		if (!root) return ret;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty())
		{
			int layer_size = q.size();
			ret.push_back(vector<int>());
			for (int i = 0; i < layer_size; ++i)
			{
				auto node = q.front();
				q.pop();
				ret.back().push_back(node->val);
				if (node->left) q.push(node->left);
				if (node->right) q.push(node->right);
			}
		}
		return ret;
	}
};
// 
//

//
//递归解决树问题
// 
// 自上而下（类似于前序遍历）
// 1. return specific value for null node
// 2. update the answer if needed                      // answer <-- params
// 3. left_ans = top_down(root.left, left_params)      // left_params <-- root.val, params
// 4. right_ans = top_down(root.right, right_params)   // right_params <-- root.val, params
// 5. return the answer if needed
int answer;//例如求树深度
void maximum_depth(TreeNode* root, int depth) {
	if (!root) return;//1. return if root is null
	if (!root->left && !root->right)
		answer = max(answer, depth); //2. if root is a leaf node :
	maximum_depth(root->left, depth + 1);
	maximum_depth(root->right, depth + 1);
}
// 
// 自下而上（类似于后序遍历）
// 1. return specific value for null node
// 2. left_ans = bottom_up(root.left)      // call function recursively for left child
// 3. right_ans = bottom_up(root.right)    // call function recursively for right child
// 4. return answers                       // answer <-- left_ans, right_ans, root.val
// 再看树深度
int max_depth(TreeNode* root)
{
	if (!root) return 0;
	int left_depth = max_depth(root->left);
	int right_depth = max_depth(root->right);
	return max(left_depth, right_depth) + 1;
}
// 
// 判断二叉树是否中心对称
class Solution2_2 {
public:
	bool isSymmetric(TreeNode* root) {
		
	}
};
// 
//


int main()
{
	std::cout << "Hello World!\n";
}
