// grokking_04.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

//
//树的广度优先搜索 BFS
//
//树的深度优先搜索 DFS
// 
//两堆法
// 
//子集
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

//例：设计一个类，以便求一组数字的中位数
class MedianOfAStream {
public:
	virtual void insertNum(int num) {
		//根据元素大小，填入不同的堆
		if (smaller.empty() || num <= smaller.top())
			smaller.push(num);
		else
			bigger.push(num);
		//平衡两堆大小，最大堆允许比最小堆大1
		if (smaller.size() > bigger.size() + 1)
		{
			bigger.push(smaller.top());
			smaller.pop();
		}
		else if (bigger.size() > smaller.size())
		{
			smaller.push(bigger.top());
			bigger.pop();
		}
	}

	virtual double findMedian() {
		//由于最大堆可以大1，所以堆顶要么是两堆顶平均值，要么是最大堆堆顶。另外注意返回浮点数
		return smaller.size() == bigger.size() ? (smaller.top() / 2.0 + bigger.top() / 2.0) : smaller.top();
	}
private:
	//较小的半组数据用最大堆，较大的半组数据用最小堆，这样中位数在两个堆顶产生
	priority_queue<int> smaller;
	priority_queue<int, vector<int>, greater<int>> bigger;
};

//例：给定数组和一个数字k，求每个大小为k的窗口的中位数
//滑动窗口结合上例求中位数，但需要扩展一个移除接口
template<typename T, class Container = vector<T>, class Compare = less<typename Container::value_type>>
class priority_queue_with_remove :public priority_queue<T, Container, Compare>
{
public:
	bool remove(const T& value)
	{
		auto iter = find(this->c.begin(), this->c.end(), value);//找是否存在指定元素
		if (iter == this->c.end()) return false;//没找到则返回失败
		this->c.erase(iter);//删除指定元素
		std::make_heap(this->c.begin(), this->c.end(), this->comp);//删除后要手动重新堆化
		return true;
	}
};
class SlidingWindowMedian {
public:
	virtual vector<double> findSlidingWindowMedian(const vector<int>& nums, int k) {
		vector<double> result(nums.size() - k + 1);
		int window_start = 0;
		for (int window_end = 0; window_end < nums.size(); ++window_end)
		{
			insert(nums[window_end]);
			if (window_end >= k - 1)
			{
				result.push_back(findMedian());
				remove(nums[window_start]);
				++window_start;
			}
		}
		//时间复杂度O(N*K)，遍历整个数组消耗N，在堆操作中，插入/移除消耗logK但移除前搜索需要消耗K
		//空间复杂度O(K)，因为是固定大小窗口，两堆中存放元素总数恒定
		return result;
	}
	void insert(int num)
	{
		if (smaller.empty() || num <= smaller.top())
			smaller.push(num);
		else
			bigger.push(num);
		balance();
	}
	double findMedian()
	{
		return smaller.size() == bigger.size() ? (smaller.top() / 2.0 + bigger.top() / 2.0) : smaller.top();
	}
	void remove(int num)
	{
		if (num <= smaller.top())
			smaller.remove(num);
		else
			bigger.remove(num);
		balance();
	}
	void balance()
	{
		if (smaller.size() > bigger.size() + 1)
		{
			bigger.push(smaller.top());
			smaller.pop();
		}
		else if (bigger.size() > smaller.size())
		{
			smaller.push(bigger.top());
			bigger.pop();
		}
	}
private:
	//同样使用大顶堆存较小一半，小顶堆存较大一半
	priority_queue_with_remove<int> smaller;
	priority_queue_with_remove<int, vector<int>, greater<int>> bigger;
};

//
//总结
// 在一些问题中，一组元素可以分为两部分
// 用最大、最小两个堆，分别了解最大和最小元素来解决问题
//

//练习：给定区间数组，找出每个区间的下一个区间是否在数组中以及他们的位置
//对区间头和区间尾分别建立一个最大堆
//从最大区间尾开始，如果大于最大区间头，则一定没有后续区间，弹出继续
//如果有后续区间，要从以区间头建立的最大堆中找到区间头最小且满足条件的一个
//注意每次找到一个满足条件的区间后还要放回最大区间头的堆，因为可能还会作为另一个区间的后续区间
class Interval {
public:
	int start = 0;
	int end = 0;
	Interval(int start, int end) {
		this->start = start;
		this->end = end;
	}
};
class NextInterval {
public:
	struct startCompare {
		bool operator()(const pair<Interval, int>& x, const pair<Interval, int>& y) {
			return y.first.start > x.first.start;
		}
	};

	struct endCompare {
		bool operator()(const pair<Interval, int>& x, const pair<Interval, int>& y) {
			return y.first.end > x.first.end;
		}
	};

	static vector<int> findNextInterval(const vector<Interval>& intervals) {
		int n = intervals.size();
		// heap for finding the maximum start
		priority_queue<pair<Interval, int>, vector<pair<Interval, int>>, startCompare> maxStartHeap;
		// heap for finding the minimum end
		priority_queue<pair<Interval, int>, vector<pair<Interval, int>>, endCompare> maxEndHeap;

		vector<int> result(n);
		for (int i = 0; i < intervals.size(); i++) {
			maxStartHeap.push(make_pair(intervals[i], i));
			maxEndHeap.push(make_pair(intervals[i], i));
		}

		// go through all the intervals to find each interval's next interval
		for (int i = 0; i < n; i++) {
			// let's find the next interval of the interval which has the highest 'end'
			auto topEnd = maxEndHeap.top();
			maxEndHeap.pop();

			result[topEnd.second] = -1;  // defaults to -1
			if (maxStartHeap.top().first.start >= topEnd.first.end) {
				auto topStart = maxStartHeap.top();
				maxStartHeap.pop();
				// find the the interval that has the closest 'start'
				while (!maxStartHeap.empty() && maxStartHeap.top().first.start >= topEnd.first.end) {
					topStart = maxStartHeap.top();
					maxStartHeap.pop();
				}
				result[topEnd.second] = topStart.second;
				// put the interval back as it could be the next interval of other intervals
				maxStartHeap.push(topStart);
			}
		}
		return result;
	}
};

//=======================================================================

//
//子集
//

//例：给定集合，求所有子集
//时间复杂度O(N*2^N)，遍历所有元素消耗N，每个元素遍历后子集数翻倍消耗2^N
//空间复杂度O(N*2^N)，每次拷贝出之前的所有子集消耗N，新子集数量翻倍消耗2^N
class Subsets {
public:
	static vector<vector<int>> findSubsets(const vector<int>& nums) {
		vector<vector<int>> subsets;
		subsets.push_back(vector<int>());
		for (auto num : nums)
		{
			int size_now = subsets.size();
			for (int i = 0; i < size_now; ++i)
			{
				vector<int> new_subset(subsets[i]);
				new_subset.push_back(num);
				subsets.push_back(new_subset);
			}
		}
		return subsets;
	}
};

//例：给定集合，可能包含重复数字，找出所有不同子集
class SubsetWithDuplicates {
public:
	static vector<vector<int>> findSubsets(vector<int>& nums) {
		vector<vector<int>> subsets;
		//记录每次添加前子集数量，如果下一个是重复元素，跳过前一次处理子集数量的子集
		int memo = 0;
		subsets.push_back(vector<int>());
		for (int i = 0; i < nums.size(); ++i)
		{
			int size_now = subsets.size();
			int j = 0;
			if (i > 0 && nums[i] == nums[i - 1])
				j = memo;
			for (; j < size_now; ++j)
			{
				vector<int> set(subsets[j]);
				set.push_back(nums[i]);
				subsets.push_back(set);
			}
			memo = size_now;
		}
		return subsets;
	}
};

//例：给定一组数字，找出所有排列
//与子集类似， 但要包含所有元素
class Permutations {
public:
	static vector<vector<int>> findPermutations(const vector<int>& nums) {
		vector<vector<int>> result;
		queue<vector<int>> permutations;
		permutations.push(vector<int>());
		for (auto cur : nums)
		{
			int n = permutations.size();
			for (int i = 0; i < n; ++i)
			{
				//取出一个之前的组合，准备进行跟新元素组合
				vector<int> old = permutations.front();
				permutations.pop();
				//往旧组合每个拷贝中的不同位置（头、中间、尾）插入新元素，组成新组合
				for (int j = 0; j <= old.size(); ++j)
				{
					vector<int> new_permutations(old);
					new_permutations.insert(new_permutations.begin() + j, cur);
					//当组合数与原组大小一致时，填充结果
					if (new_permutations.size() == nums.size())
						result.push_back(new_permutations);
					//否则，装入现有组合列表，准备下一次执行
					else
						permutations.push(new_permutations);
				}
			}
		}
		return result;
	}
};

//例：给定字符串，找到所有排列（规则为序列不变但改变大小写）
//上例变种，每次添加的组合是大小写，数字跳过
class LetterCaseStringPermutation {
public:
	static vector<string> findLetterCaseStringPermutations(const string& str) {
		vector<string> permutations;
		if (str.empty()) return permutations;
		permutations.push_back(str);
		for (int i = 0; i < str.length(); ++i)
		{
			if (isdigit(str[i])) continue;
			int n = permutations.size();
			for (int j = 0; j < n; ++j)
			{
				string s = permutations[i];
				if (isupper(s[i]))
					s[i] = tolower(s[i]);
				else
					s[i] = toupper(s[i]);
				permutations.push_back(s);
			}
		}

		return permutations;
		//答案写法，迭代器效率更高？
		vector<string> permutations;
		if (str == "") {
			return permutations;
		}

		permutations.push_back(str);
		// process every character of the string one by one
		for (int i = 0; i < str.length(); i++) {
			if (isalpha(str[i])) {  // only process characters, skip digits
			  // we will take all existing permutations and change the letter case appropriately
				int n = permutations.size();
				for (int j = 0; j < n; j++) {
					vector<char> chs(permutations[j].begin(), permutations[j].end());
					// if the current character is in upper case change it to lower case or vice versa
					if (isupper(chs[i])) {
						chs[i] = tolower(chs[i]);
					}
					else {
						chs[i] = toupper(chs[i]);
					}
					permutations.push_back(string(chs.begin(), chs.end()));
				}
			}
		}
		return permutations;
	}
};

//例：给定一个数字N，生成N对平衡括号的所有组合
//从空集开始，每次向之前的组合中添加左括号或右括号
//要符合左括号数量小于等于给定N，右括号数小于等于左括号数
class ParenthesesString {
public:
	//定义一个辅助类记录当前左右括号数
	string str;
	int openCount = 0;   // open parentheses count
	int closeCount = 0;  // close parentheses count
	ParenthesesString(const string& s, int openCount, int closeCount) {
		this->str = s;
		this->openCount = openCount;
		this->closeCount = closeCount;
	}
};
class GenerateParentheses {
public:
	static vector<string> generateValidParentheses(int num) {
		vector<string> result;
		queue<ParenthesesString> queue;
		queue.push({ "",0,0 });
		while (!queue.empty())
		{
			ParenthesesString ps = queue.front();
			queue.pop();
			//开闭括号数量同时符合条件，添加到结果集
			if (ps.openCount == num && ps.closeCount == num)
				result.push_back(ps.str);
			else
			{
				//开括号数量小于组数则可以添加
				if (ps.openCount < num)
					queue.push({ ps.str + "(",ps.openCount + 1,ps.closeCount });
				//比括号数量小于开括号数量则满足括号平衡，可以添加
				if (ps.closeCount < ps.openCount)
					queue.push({ ps.str + ")",ps.openCount,ps.closeCount + 1 });
			}
		}
		return result;
	}
};

//例：给定一个单词，生成所有通用缩写
//将单词每个子字符串替换为子字符串中字符数即通用缩写
//比如“ab”，子字符串有“”“a”“b”“ab”
//用字符数替换后，得到“ab”“1b”“a1”“2”
class AbbreviatedWord {
public:
	string str;
	int start = 0;
	int count = 0;

	AbbreviatedWord(string str, int start, int count) {
		this->str = str;
		this->start = start;
		this->count = count;
	}
};
class GeneralizedAbbreviation {
public:
	static vector<string> generateGeneralizedAbbreviation(const string& word) {
		int wordLen = word.length();
		vector<string> result;
		queue<AbbreviatedWord> queue;
		//从一个空字符开始
		queue.push({ "", 0, 0 });
		while (!queue.empty()) {
			//每次把两个缩写规则应用与上一次的组合
			AbbreviatedWord abWord = queue.front();
			queue.pop();
			if (abWord.start == wordLen) {
				if (abWord.count != 0) {
					abWord.str += to_string(abWord.count);
				}
				result.push_back(abWord.str);
			}
			else {
				//每个词可以缩写或添加
				// continue abbreviating by incrementing the current abbreviation count
				queue.push({ abWord.str, abWord.start + 1, abWord.count + 1 });

				// restart abbreviating, append the count and the current character to the string
				if (abWord.count != 0) {
					abWord.str += to_string(abWord.count);
				}
				abWord.str += word[abWord.start];
				queue.push({ abWord.str, abWord.start + 1, 0 });
			}
		}

		return result;
	}
};

//
//总结
// BFS相关问题
// 要生成集合的所有子集，可以从一个空集开始
// 遍历所有数字，每次遍历将新数字与现有所有子集组合一遍
// 最后都添加到现有集合
//

//练习：给定一个算术表达式，使用括号对数字和运算符分组，找出所有计算方式
//将等式通过符号分割的形式表示括号，递归计算每部分
class EvaluateExpression {
public:
	static vector<int> diffWaysToEvaluateExpression(const string& input) {
		vector<int> result;
		// base case: if the input string is a number, parse and add it to output.
		if (input.find("+") == string::npos && input.find("-") == string::npos &&
			input.find("*") == string::npos) {
			result.push_back(stoi(input));
		}
		else
		{
			for (int i = 0; i < input.length(); i++)
			{
				char chr = input[i];
				if (!isdigit(chr))
				{
					// break the equation here into two parts and make recursively calls
					vector<int> leftParts = diffWaysToEvaluateExpression(input.substr(0, i));
					vector<int> rightParts = diffWaysToEvaluateExpression(input.substr(i + 1));
					for (auto part1 : leftParts)
					{
						for (auto part2 : rightParts)
						{
							if (chr == '+')
								result.push_back(part1 + part2);
							else if (chr == '-')
								result.push_back(part1 - part2);
							else if (chr == '*')
								result.push_back(part1 * part2);
						}
					}
				}
			}
		}
		return result;
	}

	//备忘录版，用一个hashmap跳过递归中可能重复的情况
	unordered_map<string, vector<int>> map = unordered_map<string, vector<int>>();
	virtual vector<int> diffWaysToEvaluateExpression_memo(const string& input) {
		if (map.find(input) != map.end()) {
			return map[input];
		}
		vector<int> result;
		// base case: if the input string is a number, parse and return it.
		if (input.find("+") == string::npos && input.find("-") == string::npos &&
			input.find("*") == string::npos) {
			result.push_back(stoi(input));
		}
		else {
			for (int i = 0; i < input.length(); i++) {
				char chr = input[i];
				if (!isdigit(chr)) {
					vector<int> leftParts = diffWaysToEvaluateExpression_memo(input.substr(0, i));
					vector<int> rightParts = diffWaysToEvaluateExpression_memo(input.substr(i + 1));
					for (auto part1 : leftParts) {
						for (auto part2 : rightParts) {
							if (chr == '+') {
								result.push_back(part1 + part2);
							}
							else if (chr == '-') {
								result.push_back(part1 - part2);
							}
							else if (chr == '*') {
								result.push_back(part1 * part2);
							}
						}
					}
				}
			}
		}
		map[input] = result;
		return result;
	}
};

//练习：给定数字n，找出所有可以存储值1~n的结构唯一的二叉搜索树（BST）
//从1遍历到n，将每个数字作为树的根
//之后根据BST规则，比根大的依次往右分别放一次，比根小的依次往左放依次
class UniqueTrees {
public:
	static vector<TreeNode*> findUniqueTrees(int n) {
		if (n <= 0) {
			return vector<TreeNode*>();
		}
		return findUniqueTreesRecursive(1, n);
	}
	static vector<TreeNode*> findUniqueTreesRecursive(int start, int end) {
		vector<TreeNode*> result;
		// base condition, return 'null' for an empty sub-tree
		// consider n=1, in this case we will have start=end=1, this means we should have only one tree
		// we will have two recursive calls, findUniqueTreesRecursive(1, 0) & (2, 1)
		// both of these should return 'null' for the left and the right child
		if (start > end) {
			result.push_back(nullptr);
			return result;
		}

		for (int i = start; i <= end; i++) {
			// making 'i' root of the tree
			vector<TreeNode*> leftSubtrees = findUniqueTreesRecursive(start, i - 1);
			vector<TreeNode*> rightSubtrees = findUniqueTreesRecursive(i + 1, end);
			for (auto leftTree : leftSubtrees) {
				for (auto rightTree : rightSubtrees) {
					TreeNode* root = new TreeNode(i);
					root->left = leftTree;
					root->right = rightTree;
					result.push_back(root);
				}
			}
		}
		return result;
	}
};

//练习：给定数字n，找出所有可以存储1~n的结构唯一的BST的计数
//上题的简化版，不需要构建树，只要计数
class CountUniqueTrees {
public:
	int countTrees(int n) {
		if (n <= 1) return 1;
		int count = 0;
		for (int i = 1; i <= n; i++) {
			// making 'i' root of the tree
			int countOfLeftSubtrees = countTrees(i - 1);
			int countOfRightSubtrees = countTrees(n - i);
			count += (countOfLeftSubtrees * countOfRightSubtrees);
		}
		return count;
	}
	//备忘录版本
	unordered_map<int, int> map = unordered_map<int, int>();
	virtual int countTrees_memo(int n) {
		if (map.find(n) != map.end()) {
			return map[n];
		}

		if (n <= 1) {
			return 1;
		}

		int count = 0;
		for (int i = 1; i <= n; i++) {
			// making 'i' root of the tree
			int countOfLeftSubtrees = countTrees_memo(i - 1);
			int countOfRightSubtrees = countTrees_memo(n - i);
			count += (countOfLeftSubtrees * countOfRightSubtrees);
		}
		map[n] = count;
		return count;
	}
};

int main()
{
	std::cout << "Hello World!\n";
}