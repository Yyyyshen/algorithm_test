﻿// grokking_04.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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
//两堆法
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

//例：给定二叉树和一个数值，判断是否有一条到叶子节点的路径使所有节点值之和为给定数值
class TreePathSum {
public:
	static bool hasPath(TreeNode* root, int sum) {
		//递归结束出口
		if (root == nullptr) return false;
		//若为叶子节点，且和为sum，返回true
		if (sum == root->val && root->left == nullptr && root->right == nullptr) return true;
		//分别遍历左右子树
		bool left = hasPath(root->left, sum - root->val);
		bool right = hasPath(root->right, sum - root->val);
		//有一条路径成功则可以返回true
		return left || right;
	}
};

//例：上题基础上，找出所有路径
class FindAllTreePaths {
public:
	static void path(TreeNode* root, int sum, vector<int>& cur, vector<vector<int>>& ret)
	{
		if (root == nullptr) return;
		cur.push_back(root->val);
		if (root->val == sum && root->left == nullptr && root->right == nullptr)
		{
			ret.push_back(cur);
		}
		else
		{
			path(root->left, sum - root->val, cur, ret);
			path(root->right, sum - root->val, cur, ret);
		}
		//每次操作完，要把已添加的节点值删除，返回上一层递归时才能保证参数正确
		cur.pop_back();
	}
	static vector<vector<int>> findPaths(TreeNode* root, int sum) {
		vector<vector<int>> allPaths;
		vector<int> cur;
		//时间复杂度O(N*N)，遍历所有节点消耗N，每到一个叶子节点，存了一遍路径，消耗N
		//空间复杂度O(N*logN)
		//同类型题，求所有路径/所有路径最大和 等
		path(root, sum, cur, allPaths);
		return allPaths;
	}
};

//例：给定二叉树，每个到叶子节点的路径连成一个数字，求所有路径数字的总和
class SumOfPathNumbers {
public:
	static void path(TreeNode* root, int number, int& total)
	{
		if (root == nullptr) return;
		number = 10 * number + root->val;
		if (root->left == nullptr && root->right == nullptr)
		{
			total += number;
			return;
		}
		path(root->left, number, total);
		path(root->right, number, total);
	}
	static int findSumOfPathNumbers(TreeNode* root) {
		int totalPathsSum = 0;
		path(root, 0, totalPathsSum);
		return totalPathsSum;

		//更简洁写法
		return findRootToLeafPathNumbers(root, 0);
	}
	static int findRootToLeafPathNumbers(TreeNode* root, int pathSum)
	{
		if (root == nullptr) return 0;
		pathSum = 10 * pathSum + root->val;
		if (root->left == nullptr && root->right == nullptr) return pathSum;
		return findRootToLeafPathNumbers(root->left, pathSum) +
			findRootToLeafPathNumbers(root->right, pathSum);
	}
};

//例：给定二叉树和一个序列，看树中是否有一条路径与序列相同
class PathWithGivenSequence {
public:
	static bool path(TreeNode* root, const vector<int>& seq, int level)
	{
		if (root == nullptr) return false;
		//层级大于序列大小或找到某一个数字不符合，则直接返回false
		if (level >= seq.size() || root->val != seq[level]) return false;
		//同时满足节点为叶子节点以及正好是序列最后一位时，才返回true
		if (root->left == nullptr && root->right == nullptr && level == seq.size() - 1) return true;
		//左右两边遍历，有一条符合就可以
		return path(root->left, seq, level + 1) || path(root->right, seq, level + 1);
	}
	static bool findPath(TreeNode* root, const vector<int>& sequence) {
		//参数检查一个小注意点，不是无脑返回false，序列也为空时，应该是true
		if (root == nullptr) return sequence.empty();
		//时间复杂度O(N)，遍历一遍节点；空间复杂度O(N)，为递归栈空间
		return path(root, sequence, 0);
	}
};

//例：给定二叉树和一个目标值，找出树种所有和为目标值的路径（没有开头结尾节点限制，只要符合连续）
class CountAllPathSum {
public:
	static void path(TreeNode* root, vector<int>& cur, vector<vector<int>>& all)
	{
		if (root == nullptr) return;
		cur.push_back(root->val);
		if (root->left == nullptr && root->right == nullptr)
			all.push_back(cur);
		else
		{
			path(root->left, cur, all);
			path(root->right, cur, all);
		}
		cur.pop_back();
	}
	static int countPaths(TreeNode* root, int S) {
		//求出所有路径，然后每条路径使用滑动窗口
		vector<vector<int>> all_path;
		vector<int> cur_path;
		path(root, cur_path, all_path);
		int count = 0;
		for (int i = 0; i < all_path.size(); ++i)
		{
			int window_start = 0, sum = 0;
			for (int window_end = 0; window_end < all_path[i].size(); ++window_end)
			{
				sum += all_path[i][window_end];
				if (sum >= S)
				{
					if (sum == S)
						++count;
					sum -= all_path[i][window_start++];
				}
			}
		}
		return count;
		//另一个思路，无须找出所有路径后单独计算
		//只要在每条路径遍历过程中，倒序往前遍历，就能知道是否有符合条件的
		vector<int> cur;
		int path_num = 0;
		countPathsRecursive(root, S, cur, path_num);
		return path_num;
	}
	static void countPathsRecursive(TreeNode* currentNode, int S, vector<int>& currentPath, int& pathNums) {
		if (currentNode == nullptr) return;
		currentPath.push_back(currentNode->val);

		int sum = 0;
		for (int i = currentPath.size() - 1; i >= 0; --i)
		{
			sum += currentPath[i];
			if (sum == S)
				++pathNums;//万一元素值有0和负数等情况，还是不要break了
		}
		countPathsRecursive(currentNode->left, S, currentPath, pathNums);
		countPathsRecursive(currentNode->right, S, currentPath, pathNums);

		currentPath.pop_back();
	}
};

//
//总结
// 树的深度优先搜索遍历
// 一般使用递归（迭代也可以）
// 与广度优先遍历每层不同
// 从一条路线走到头，再走另一条
// 如果层内需要记录元素，记得在结尾处理时再去掉元素，保证每层参数状态
//

//练习：给定二叉树，找到直径长度（两个叶子节点之间最长路径，可不通过根）
//其实就是求每个节点的左右深度相加最大值
class TreeDiameter {
public:
	static int findDiameter(TreeNode* root) {
		int treeDiameter = 0;
		findDiameterRecursive(root, treeDiameter);
		return treeDiameter;
	}
	static int findDiameterRecursive(TreeNode* root, int& treeDiameter)
	{
		if (root == nullptr) return 0;//遍历到空则为0
		//每次求左子树和右子树的最大深度
		int left = findDiameterRecursive(root->left, treeDiameter);
		int right = findDiameterRecursive(root->right, treeDiameter);
		//左右都不为0时（或左右子树都存在时），计算一次最大值
		//有一边为0时一定有更大值或不满足直径定义（两个叶子节点之间路径）所以不记录
		if (left != 0 && right != 0)
			treeDiameter = max(treeDiameter, left + right + 1);
		//往上回溯，叶子节点是max(0,0)+1，之后类推
		return max(left, right) + 1;
	}
};

//练习：给定二叉树，求具有最大和的路径（任意两个节点间的路径，可不通过根）
class MaximumPathSum {
public:
	static int pathSum(TreeNode* root, int& maxSum)
	{
		if (root == nullptr) return 0;
		//与上题类似，就是相当于求加了权重的直径，只要都是正数，肯定是到叶子节点更大
		int left = pathSum(root->left, maxSum);
		int right = pathSum(root->right, maxSum);
		//不同的就是，有负数的过滤掉，就保证了最大
		left = left < 0 ? 0 : left;
		right = right < 0 ? 0 : right;
		maxSum = max(maxSum, left + right + root->val);
		return max(left, right) + root->val;
	}
	static int findMaximumPathSum(TreeNode* root) {
		int maxSum = INT_MIN;
		pathSum(root, maxSum);
		return maxSum;
	}
};

//=======================================================================

//
//两堆法
//

int main()
{
	std::cout << "Hello World!\n";
}