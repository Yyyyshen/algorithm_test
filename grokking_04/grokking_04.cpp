// grokking_04.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//
//树的广度优先搜索 BFS
//
//树的深度优先搜索 DFS
//

//=======================================================================

//
//BFS
//

//例：二叉树层级遍历
//整个遍历一遍，时间复杂度 O(N)，额外使用一个队列辅助，空间复杂度 O(N)
class TreeNode {
public:
	int val = 0;
	TreeNode* left;
	TreeNode* right;
	TreeNode* next;

	TreeNode(int x) {
		val = x;
		left = right = next = nullptr;
	}

	// tree traversal using 'next' pointer
	virtual void printTree() {
		TreeNode* current = this;
		cout << "Traversal using 'next' pointer: ";
		while (current != nullptr) {
			cout << current->val << " ";
			current = current->next;
		}
	}
};
class LevelOrderTraversal {
public:
	using node_pair = pair<TreeNode*, int>;
	static vector<vector<int>> traverse(TreeNode* root) {
#if 0
		vector<vector<int>> result;
		if (root == nullptr) return result;
		queue<node_pair> q;
		q.push({ root,0 });
		while (!q.empty())
		{
			auto tmp = q.front();
			q.pop();
			if (tmp.second + 1 > result.size())
				result.push_back({ tmp.first->val });
			else
				result[tmp.second].push_back(tmp.first->val);
			if (tmp.first->left != nullptr)
				q.push({ tmp.first->left,tmp.second + 1 });
			if (tmp.first->right != nullptr)
				q.push({ tmp.first->right,tmp.second + 1 });
		}
		return result;
#endif
		//另一个思路
		//层级概念还可以用队列长度来辅助计算
		vector<vector<int>> result;//按层级倒叙记录的话，就使用deque，每次push_front即可
		if (root == nullptr) return result;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty())
		{
			int cur_level_len = q.size();
			vector<int> cur_level;
			//每次处理完当前层所有节点，就可以不记录层级
			for (int i = 0; i < cur_level_len; ++i)
			{
				TreeNode* tmp = q.front();
				q.pop();
				cur_level.push_back(tmp->val);
				if (tmp->left != nullptr)
					q.push(tmp->left);
				if (tmp->right != nullptr)
					q.push(tmp->right);
			}
			result.push_back(cur_level);
		}
		return result;
	}
};

//例：二叉树之字形层级遍历（一层从左往右，下一层从右往左）
class ZigzagTraversal {
public:
	static vector<vector<int>> traverse(TreeNode* root) {
		vector<vector<int>> result;
		if (root == nullptr) return result;
		bool flag = true;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty())
		{
			int cur_level_size = q.size();
			//层大小已知，所以插入顺序可以用索引计算
			vector<int> cur_level(cur_level_size);
			for (int i = 0; i < cur_level_size; ++i)
			{
				TreeNode* tmp = q.front();
				q.pop();
				if (flag)
					cur_level[i] = tmp->val;
				else
					cur_level[cur_level_size - 1 - i] = tmp->val;
				if (tmp->left != nullptr)
					q.push(tmp->left);
				if (tmp->right != nullptr)
					q.push(tmp->right);
			}
			flag = !flag;
			result.push_back(cur_level);
		}
		return result;
	}
};

//例：求二叉树最小深度
class MinimumBinaryTreeDepth {
public:
	static int findDepth(TreeNode* root) {
		int minimumTreeDepth = 0;
		if (root == nullptr) return minimumTreeDepth;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty())
		{
			++minimumTreeDepth;
			int cur_level_size = q.size();
			for (int i = 0; i < cur_level_size; ++i)
			{
				TreeNode* tmp = q.front();
				q.pop();
				//是叶子节点就返回
				if (tmp->left == nullptr && tmp->right == nullptr)
					return minimumTreeDepth;
				if (tmp->left != nullptr)
					q.push(tmp->left);
				if (tmp->right != nullptr)
					q.push(tmp->right);
			}
		}
		return minimumTreeDepth;
	}
};

//例：给定二叉树和一个节点，找到层级遍历顺序中，给定节点的下一个节点
class LevelOrderSuccessor {
public:
	static TreeNode* findSuccessor(TreeNode* root, int key) {
		if (root == nullptr) return root;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty())
		{
			TreeNode* tmp = q.front();
			q.pop();
			if (tmp->left != nullptr)
				q.push(tmp->left);
			if (tmp->right != nullptr)
				q.push(tmp->right);
			if (tmp->val == key)
				break;
		}
		return q.empty() ? nullptr : q.front();
	}
};

//例：给定二叉树，把每层节点串联（每层最后一个应指向空节点）
class ConnectLevelOrderSiblings {
public:
	static void connect(TreeNode* root) {
		if (root == nullptr) return;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty())
		{
			int cur_level_size = q.size();
			TreeNode* prev = nullptr;
			for (int i = 0; i < cur_level_size; ++i)
			{
				TreeNode* tmp = q.front();
				q.pop();
				if (prev != nullptr)
					prev->next = tmp;
				prev = tmp;
				if (tmp->left != nullptr)
					q.push(tmp->left);
				if (tmp->right != nullptr)
					q.push(tmp->right);
			}
		}
	}
};

//
//总结
// 树或者图涉及到逐级（层）顺序遍历时
// 一般使用队列跟踪本层所有节点
// 每次处理中，队列长度即一层内节点数量
// 之后每次处理一个节点（出队）时
// 将其所有子节点入队
// 直到队列为空
//

//练习：按层级链接二叉树所有节点
class ConnectAllSiblings {
public:
	static void connect(TreeNode* root) {
		if (root == nullptr) return;
		queue<TreeNode*> q;
		q.push(root);
		TreeNode* prev = nullptr, * cur = nullptr;
		while (!q.empty())
		{
			cur = q.front();
			q.pop();
			if (prev != nullptr)
				prev->next = cur;
			prev = cur;
			if (cur->left != nullptr)
				q.push(cur->left);
			if (cur->right != nullptr)
				q.push(cur->right);
		}
	}
};

//练习：求二叉树右视图（右视图：每层最右边的节点）
class RightViewTree {
public:
	static vector<TreeNode*> traverse(TreeNode* root) {
		vector<TreeNode*> result;
		if (root == nullptr) return result;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty())
		{
			int cur_len_len = q.size();
			for (int i = 0; i < cur_len_len; ++i)
			{
				TreeNode* tmp = q.front();
				q.pop();
				//若求左视图，则判断改为 i == 0 即可
				if (i == cur_len_len - 1)
					result.push_back(tmp);
				if (tmp->left != nullptr)
					q.push(tmp->left);
				if (tmp->right != nullptr)
					q.push(tmp->right);
			}
		}
		return result;
	}
};

//=======================================================================

//
//DFS
//

//例：

//
//总结
// 
//

//练习：

int main()
{
	std::cout << "Hello World!\n";
}