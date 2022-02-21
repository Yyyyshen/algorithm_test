// grokking_06.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//
//K路合并
// 
//0-1背包（动态规划）
// 
//拓扑排序（图）
// 
//补充
// 
//总结
//

//=======================================================================

//
//K路合并
//

//例：给定K个排序的链表，将他们合并到一个排序列表中
class ListNode {
public:
	int value = 0;
	ListNode* next;
	ListNode(int value) {
		this->value = value;
		this->next = nullptr;
	}
};
class MergeKSortedLists {
public:
	struct nodeComp {
		bool operator()(ListNode* a, ListNode* b) { return a->value > b->value; };
	};
	static ListNode* merge(const vector<ListNode*>& lists) {
		ListNode* resultHead = nullptr, * cur = nullptr;
		if (lists.empty()) return resultHead;
		if (lists.size() == 1) return lists[0];
		priority_queue<ListNode*, vector<ListNode*>, nodeComp> minHeap;
		for (auto head : lists)
			if (head != nullptr)
				minHeap.push(head);
		while (!minHeap.empty())
		{
			ListNode* tmp = minHeap.top();
			minHeap.pop();
			if (resultHead == nullptr)
				resultHead = cur = tmp;
			else
			{
				cur->next = tmp;
				cur = tmp;
			}
			if (tmp->next != nullptr)
				minHeap.push(tmp->next);
		}
		return resultHead;
	}
};

//例：给定一些排序数组，找出所有数组中第K个最小的数
//每次从最小的数组中找一个加入最小堆，不同的是需要自己记录所处数组和所处索引
class KthSmallestInMSortedArrays {
public:
	using pair_type = pair<int, pair<int, int>>;
	struct pairComp {
		bool operator()(const pair_type& a, const pair_type& b)
		{
			return a.first > b.first;
		}
	};
	static int findKthSmallest(const vector<vector<int>>& lists, int k) {
		priority_queue<pair_type, vector<pair_type>, pairComp> minHeap;
		for (int i = 0; i < lists.size(); ++i)
			if (!lists[i].empty())
				minHeap.push({ lists[i][0],{i, 0} });
		for (int i = 0; i < k - 1 && !minHeap.empty(); ++i)
		{
			auto top = minHeap.top();
			minHeap.pop();
			if (top.second.second < lists[top.second.first].size())
				minHeap.push({ lists[top.second.first][top.second.second + 1], {top.second.first,top.second.second + 1} });
		}
		return minHeap.empty() ? -1 : minHeap.top().first;
		//类似问题，求所有数字的中位数
		//即K = mid，先求所有数组size和，除以2即可
		//时间复杂度O(K*LogM)，空间复杂度O(M)，M为列表个数
	}
};

//例：给定N*N矩阵，行列元素都递增排序，找到第K个最小元素
//完全套用上面的代码能得到答案，但没有利用到列递增这个条件
//思路
// 行列都有序，对角线两个元素matrix[0][0]与martix[n-1][n-1]为极值
// 是否可以用二分法来计算
// 这里巧妙的是，索引在二维上很难界定，所以使用其值来做二分的起始和结束
// 计算中间值，中间值不一定是矩阵中一个元素
// 计数矩阵中所有小于等于中间值的数字，同时找到大于中间值的最小数，记n1
// 同时找到小于等于中间值的最大数，记n2
// 如果计数等于K，那么n1就是所需数字
// 如果计数小于K，将start记为n2，继续搜索矩阵中较高部分
// 计数大于K，将end记为n1，继续搜索矩阵中较低的部分
// 时间复杂度O(N*log(max-min))，空间O(1)
//
class KthSmallestInSortedMatrix {
public:
public:
	static int findKthSmallest(vector<vector<int>>& matrix, int k) {
		int n = matrix.size();
		int start = matrix[0][0], end = matrix[n - 1][n - 1];
		while (start < end) {
			int mid = start + (end - start) / 2;
			// first number is the smallest and the second number is the largest
			pair<int, int> smallLargePair = { matrix[0][0], matrix[n - 1][n - 1] };
			int count = countLessEqual(matrix, mid, smallLargePair);
			if (count == k) {
				return smallLargePair.first;
			}

			if (count < k) {
				start = smallLargePair.second;  // search higher
			}
			else {
				end = smallLargePair.first;  // search lower
			}
		}
		return start;
	}

private:
	static int countLessEqual(vector<vector<int>>& matrix, int mid, pair<int, int>& smallLargePair) {
		int count = 0;
		int n = matrix.size(), row = n - 1, col = 0;
		while (row >= 0 && col < n) {
			if (matrix[row][col] > mid) {
				// as matrix[row][col] is bigger than the mid, let's keep track of the
				// smallest number greater than the mid
				smallLargePair.second = min(smallLargePair.second, matrix[row][col]);
				row--;
			}
			else {
				// as matrix[row][col] is less than or equal to the mid, let's keep track of the
				// biggest number less than or equal to the mid
				smallLargePair.first = max(smallLargePair.first, matrix[row][col]);
				count += row + 1;
				col++;
			}
		}
		return count;
	}
};

//例：给定M个排序数组，找出至少包含每个列表中一个数字的最小范围
//所有数组第一个数字入最小堆，并跟踪其中最大数字
//每次循环取出顶部最小元素，与最大数字组合成一个范围，如果比之前的更小，就记录
//搜索完成的标准是，检查堆中元素是否小于M个（是否每个列表的元素都包含）
class SmallestRange {
public:
	struct valueCompare {
		bool operator()(const pair<int, pair<int, int>>& x, const pair<int, pair<int, int>>& y) {
			return x.first > y.first;
		}
	};
	static pair<int, int> findSmallestRange(const vector<vector<int>>& lists) {
		// we will store the actual number, list index and element index in the heap
		priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, valueCompare>
			minHeap;

		int rangeStart = 0, rangeEnd = numeric_limits<int>::max(),
			currentMaxNumber = numeric_limits<int>::min();
		// put the 1st element of each array in the min heap
		for (int i = 0; i < lists.size(); i++) {
			if (!lists[i].empty()) {
				minHeap.push(make_pair(lists[i][0], make_pair(i, 0)));
				currentMaxNumber = max(currentMaxNumber, lists[i][0]);
			}
		}
		// take the smallest (top) element form the min heap, if it gives us smaller range, update the
		// ranges if the array of the top element has more elements, insert the next element in the heap
		while (minHeap.size() == lists.size()) {
			auto node = minHeap.top();
			minHeap.pop();
			if (rangeEnd - rangeStart > currentMaxNumber - node.first) {
				rangeStart = node.first;
				rangeEnd = currentMaxNumber;
			}
			node.second.second++;
			if (lists[node.second.first].size() > node.second.second) {
				node.first = lists[node.second.first][node.second.second];
				minHeap.push(node);  // insert the next element in the heap
				currentMaxNumber = max(currentMaxNumber, node.first);
			}
		}

		return make_pair(rangeStart, rangeEnd);
	}
};

//
//总结
// 在 有多个排序列 表类型的问题中
// 可以使用堆来有效的对K组元素进行排列
// 例如多个递增数组，使用最小堆（优先级队列）
// 一般是把每个列表第一个先都放入堆中
// 每次出队的一定是三个中最小，之后把出队的那个元素所在列表的下一个元素加入队列
// 重复这个过程直到所有列表都遍历一遍
//

//练习：降序排序的数组，找到总和最大的K对（每对由两个数组中数字组成）
//暴力解法可以遍历两个数组创建对，并且都放入最小堆，存放k对
//优化
// 只迭代两个数组中前K个数字，而不是遍历所有，因为数组是降序的，结果一定在两组中前K个产生
class LargestPairs {
public:
	struct sumCompare {
		bool operator()(const pair<int, int>& x, const pair<int, int>& y) {
			return x.first + x.second > y.first + y.second;
		}
	};
	static vector<pair<int, int>> findKLargestPairs(const vector<int>& nums1,
		const vector<int>& nums2, int k) {
		vector<pair<int, int>> minHeap;
		for (int i = 0; i < nums1.size() && i < k; i++) {
			for (int j = 0; j < nums2.size() && j < k; j++) {
				if (minHeap.size() < k) {
					minHeap.push_back(make_pair(nums1[i], nums2[j]));
					push_heap(minHeap.begin(), minHeap.end(), sumCompare());
				}
				else {
					// if the sum of the two numbers from the two arrays is smaller than the smallest (top)
					// element of the heap, we can 'break' here. Since the arrays are sorted in the descending
					// order, we'll not be able to find a pair with a higher sum moving forward.
					if (nums1[i] + nums2[j] < minHeap.front().first + minHeap.front().second) {
						break;
					}
					else {  // else: we have a pair with a larger sum, remove top and insert this pair in
						   // the heap
						pop_heap(minHeap.begin(), minHeap.end(), sumCompare());
						minHeap.pop_back();
						minHeap.push_back(make_pair(nums1[i], nums2[j]));
						push_heap(minHeap.begin(), minHeap.end(), sumCompare());
					}
				}
			}
		}
		return minHeap;
	}
};

//=======================================================================

//
//0-1背包（动态规划）
//

//例：给定N个物品的重量和价值，将这些物品放入容量为C的背包，找出最大利润的装法
// 每个物品只能选一次
/*
Items: { Apple, Orange, Banana, Melon }
Weights: { 2, 3, 1, 4 }
Profits: { 4, 5, 3, 7 }
Knapsack capacity : 5
*/
//之前学的动态规划
#if 0
// 此例中，可以看出Melon和Banana加起来重量5，利润10，是最佳选择
//状态数组分析
// 以物品个数以及背包质量作为状态数组 state[4][5+1]（重量最大5，所以需要大小为6的容量）
// 对于第一个物品，填充第一行状态，装或者不装，在质量的位置记录价值
// 苹果 state[0] = { 0, -1, 4, -1, -1, -1 } 默认为-1，不装在重量0的位置价值0，装的话在重量2的位置价值4
// 橘子 state[1] = { 0, -1, 4, 5, -1, 9 } 不装的话，继承state[0]的所有状态，装的话，重量3位置价值5，重量5位置价值9
// 香蕉 state[2] = { 0, 3, 4, 7, 8, 9 } 继承或装入，只考虑能继续装的位置，超出的跳过，重量重复的位置保留更大的结果
// 西瓜 state[3] = { 0, 3, 4, 7, 8, 10 } 最后只能在0或1重量考虑，因为西瓜本身重量就是4
// 装的话，在0+4的位置价值7，但已有8，不记录；在1+4的位置价值3+7，10>9，覆盖
// 最后在最后一层状态state[3]中寻找最大值
//
class Knapsack {
public:
	int solveKnapsack(const vector<int>& profits, vector<int>& weights, int capacity) {
		//状态数组
		vector<vector<int>> state(profits.size(), vector<int>(capacity + 1, -1));
		//不装第一个物品
		state[0][0] = 0;//重量0，价值0
		//装第一个物品
		if (weights[0] <= capacity)//背包能装下才装
			state[0][weights[0]] = profits[0];//重量2，价值4
		//填充状态
		for (int i = 1; i < state.size(); ++i)
		{
			//不装第i个物品，继承之前的所有状态
			for (int j = 0; j < state[i].size(); ++j)
				if (state[i - 1][j] != -1)
					state[i][j] = state[i - 1][j];
			//装第i个物品，只考虑能装下的状态
			for (int j = 0; j <= capacity - weights[i]; ++j)
				if (state[i - 1][j] != -1)
					state[i][j + weights[i]] = max(state[i][j + weights[i]], state[i - 1][j] + profits[i]);
		}
		int ret = -1;
		for (int i = 0; i < state[state.size() - 1].size(); ++i)
			if (ret < state[state.size() - 1][i])
				ret = state[state.size() - 1][i];
		return ret;
	}
};
#endif
//从递归（回溯/深度优先）方式枚举所有情况分析
#if 0
class Knapsack {
public:
	int solveKnapsack(const vector<int>& profits, vector<int>& weights, int capacity) {
		return this->knapsackRecursive(profits, weights, capacity, 0);//从第一个物品开始评估
	}
private:
	int knapsackRecursive(const vector<int>& profits, const vector<int>& weights, int capacity,
		int currentIndex/* 当前执行到第几个物品 */)
	{
		//基本参数检查
		if (capacity <= 0 || currentIndex >= profits.size())
			return 0;

		//不装这个物品，直接进入下一层
		int profit1 = knapsackRecursive(profits, weights, capacity, currentIndex + 1);
		//装这个物品，先判断能否装下，可以去掉一部分不需要考虑的情况，剪枝
		int profit2 = 0;
		if (weights[currentIndex] <= capacity)
			profit2 = profits[currentIndex] + knapsackRecursive(profits, weights, capacity - weights[currentIndex], currentIndex + 1);
		//两种情况取最大
		return max(profit1, profit2);
		/*
		时间复杂度O(2^n)，几乎遍历所有情况，空间复杂度O(n)，为递归栈占用
		递归树分析
								c: 5 i: 0					//初始状态，容量5，没有东西装
					c:5 i:1					c:3 p:1 		//第一个物品，装或者不装，容量两个情况
			 c:5 i:2    c:2 i:2		   c:3 i:2	 c:0 p:2	//第二个物品，同理
			略		c:2 i:3	 c:1 i:3		c:2 i:3			//第三个物品，发现进行到这，有两个情况容量剩余一致
			//那么从这两个一样的情况往下发展，都是一样的分支，这部分就可以优化掉
			//可以使用一个二维数组记录当前情况，后续如果发现相同情况，则直接返回，不再算一遍
			//也就是常说的 回溯+备忘录 方法
		*/
	}
};
#endif
//自上而下使用备忘录的方式（回溯+备忘录≈动态规划）
#if 0
class Knapsack {
public:
	virtual int solveKnapsack(const vector<int>& profits, vector<int>& weights, int capacity) {
		vector<vector<int>> memo(profits.size(), vector<int>(capacity + 1, -1));
		return this->knapsackRecursive(memo, profits, weights, capacity, 0);
	}
private:
	int knapsackRecursive(vector<vector<int>>& memo,/* 备忘录，可修改，不加const */
		const vector<int>& profits, const vector<int>& weights, int capacity,
		int currentIndex /* 进行到那个物品 */)
	{
		if (capacity <= 0 || currentIndex >= profits.size())
			return 0;
		//检查备忘录，是否已经有重复情况
		if (memo[currentIndex][capacity] != -1)
			return memo[currentIndex][capacity];
		//跟之前一样计算装和不装的两个情况
		int profits1 = knapsackRecursive(memo, profits, weights, capacity, currentIndex + 1);
		int profits2 = 0;
		if (weights[currentIndex] <= capacity)
			profits2 = profits[currentIndex] + knapsackRecursive(memo, profits, weights, capacity - weights[currentIndex], currentIndex + 1);
		//在备忘录中记录此种情况
		memo[currentIndex][capacity] = max(profits1, profits2);
		return memo[currentIndex][capacity];
		//时间复杂度O(N*C)，最多计算备忘录元素数次数的情况，也就是物品个数*容量
		//空间复杂度O(N*C)，同理
	}
};
#endif
//自下而上的动态规划
/*
	我们希望找到的是，每个子阵列的最大利润和每个可能容量
	意味着状态数组dp[i][c]代表从第i个项目计算的容量c的最大利润
	只有两种情况
	一是继承于上一级同位置的数值，代表这个东西没有装的情况，即 dp[i-1][c]
	二是这个物品装的情况，则数值是本身价值加上前一层减去自身重量位置记录的价值，即 profits[i]+dp[i-1][c-weights[i]]
	最后每一格的数值计算公式可推导为 dp[i][c] = max(dp[i-1][c], profits[i] + dp[i-1][c-weight[i]])
	实际填充情况
	index ↓ | capacity → 0	1	2	3	4	5
		0				   0	0	4	4	4	4  第一行，只有一个物品能装，只要容量够，利润恒定为此物品利润
		1				   0	0	4	5	5	9
		2				   0	3	4	7	8	9	   接着根据第一行和第一列填入
		3				   0	3	4	7	8	10👉最后的最好结果
		第一列，容量0，什么都装不下，利润只能是0
*/
class Knapsack {
public:
	int solveKnapsack(const vector<int>& profits, vector<int>& weights, int capacity) {
		if (capacity <= 0 || profits.empty() || weights.empty() != profits.size()/* 参数检查 */)
			return 0;
		//建立动态规划状态数组
		vector<vector<int>> dp(profits.size(), vector<int>(capacity + 1));
		//手动填充第一行第一列，建立初始状态
		for (int i = 0; i < profits.size(); ++i)
			dp[i][0] = 0;//第一列，容量0肯定利润也只能都为0
		for (int i = 0; i <= capacity; ++i)
			dp[0][i] = weights[0] <= i ? profits[0] : 0;//第一行，只有容量装得下才填入，否则填0
		//之后，填充其余位置状态
		for (int i = 1; i < profits.size(); ++i)//外层遍历是哪个物品
		{
			for (int c = 1; c <= capacity; ++c)//内层遍历此容量下可能的情况
			{
				int profit1 = 0, profit2 = 0;//两种情况
				profit1 = dp[i - 1][c];//第一种情况是没有装当前物品，从上面状态继承其价值
				if (weights[i] <= c)//第二种情况是装了当前物品，看上一层中没装时的价值，加上自己的价值
					profit2 = profits[i] + dp[i - 1][c - weights[i]];
				dp[i][c] = max(profit1, profit2);//在此处记录最大的可能
			}
		}
		//二维数组最后的格子记录了最好情况
		return dp[profits.size() - 1][capacity];
		//时间空间复杂度也是O(N*C)
	}
};
//找到了最好情况，如何知道最好情况是怎么组合来的
/*
	最终结果产生于右下角，所以从这个点开始寻找
	往回想，还是两种情况
	没装当前物品就是从上一层继承的数值
	装了就是减去自己价值后，上一层减去自己重量的位置
	所以，如果当前点等于上一层，可以就认为是继承的，往上找
	否则，减去自身利润后，看剩余利润是怎么来的
	如此循环
*/
void printSelectedElementsFromDP(vector<vector<int>>& dp,
	const vector<int>& weights, const vector<int>& profits, int capacity)
{
	cout << "Selected Weights: ";
	int ret = dp[profits.size() - 1][capacity];
	for (int i = profits.size() - 1; i > 0; --i)
	{
		//如果不是从上面继承来的，则肯定选了自己，输出
		if (ret != dp[i - 1][capacity])
		{
			cout << " " << weights[i];
			//减去自身的重量和价值，看剩余价值和容量是怎么来的
			capacity -= weights[i];
			ret -= profits[i];
		}
	}
	//如果找到最上层，总价值还不是0，说明第一个物品也选了
	if (ret != 0)
		cout << " " << weights[0];
	cout << endl;
	//输出价值/物品索引同理
}
//挑战：优化空间复杂度为O(C)
#if 0
/*
	我们发现在状态数组计算过程中，每次我们都是用前一行的状态
	所以理论上，我们可以用两行的状态数组轮流记录
	使空间复杂度降为O(2C)
	迭代时，采用 i % 2 求模形式达到每次选择另一行的目的
*/
class KnapsackSpaceOptimization
{
	int solveKnapsack(const vector<int>& profits, const vector<int>& weights, int capacity) {
		//检查参数
		if (capacity <= 0 || profits.empty() || weights.size() != profits.size())
			return 0;
		//建立只有两行的状态数组
		vector <vector<int>> dp(2, vector<int>(capacity + 1));
		//初始化第一行状态，还是只有装得下才填充价值
		for (int i = 0; i <= capacity; ++i)
			dp[0][i] = weights[0] <= i ? profits[0] : 0;
		//依次计算其他行状态
		for (int i = 1; i < profits.size(); ++i)
		{
			for (int c = 1; c <= capacity; ++c)
			{
				int profit1 = 0, profit2 = 0;
				profit1 = dp[(i - 1) % 2][c];
				if (weights[i] <= c)
					profit2 = profits[i] + dp[(i - 1) % 2][c - weights[i]];
				dp[i % 2][c] = max(profit1, profit2);
			}
		}
		return dp[(profits.size() - 1) % 2][capacity];
	}
};
#endif
/*
	除了轮流使用两行状态之外，还可以极值优化到只用一行
	但要注意一个问题
	我们总是需要使用迭代中的两个值，装或者不装，即dp[c]和dp[c-weight[i]]
	内部循环时，从0到capacity迭代时，dp[c]计算没有问题
	如果dp[c]计算后覆盖了上一轮的值，如果下次迭代的c-weight[i]刚好等于这次c的位置
	则会影响后续的dp[c]的计算
	这也是动态规划的无后效性导致的
	解决办法其实很简单，我们倒着来遍历，就不会出现低的结果先被覆盖的情况了
*/
class KnapsackOptimalSolution {
public:
	int solveKnapsack(const vector<int>& profits, vector<int>& weights, int capacity) {
		//参数检查
		if (capacity <= 0 || profits.empty() || weights.size() != profits.size()) {
			return 0;
		}
		//建立一维状态数组
		vector<int> dp(capacity + 1);
		//填充第一次
		for (int c = 0; c <= capacity; ++c)
			dp[c] = weights[0] <= c ? profits[0] : 0;
		//逐个物品评判
		for (int i = 1; i < profits.size(); ++i)
		{
			//倒着来计算，防止前面的结果被覆盖
			for (int c = capacity; c >= 0; --c)
			{
				int profit1 = 0, profit2 = 0;
				profit1 = dp[c];//没装自己，直接继承当前值
				if (weights[i] <= c)//装了自己，看剩余容量怎么来的
					profit2 = profits[i] + dp[c - weights[i]];
				dp[c] = max(profit1, profit2);
			}
		}
		return dp[capacity];
	}
};

//例：给定一组正数，判断是否能分成两个子集，使两个子集元素之和相等
//分析
// 抽象为0-1背包
// 被装进包的和没有被装进包的就是两个子集
// 先求出数组内所有数字和，那么被装进包里的就应该是 和/2
// 转化为
// 几件东西，是否能有刚好装满一个承重是他们和重量一半的包
//
class PartitionSet {
public:
	bool canPartition(const vector<int>& num) {
		if (num.empty()) return false;
		int sum = 0;
		//求和
		for (auto n : num)
			sum += n;
		//不能整除则一定不能分成和一样的子集
		if (sum % 2 != 0)
			return false;
		//暴力回溯
		return likeKnapsackBruteForce(num, sum / 2, 0);
		//回溯+备忘录
		vector<vector<int>> memo(num.size(), vector<int>(sum / 2 + 1, -1));
		return canPartitionRecursive(memo, num, sum / 2, 0);
		//动态规划
		return canPartitionDP(num, sum / 2);
	}
	bool likeKnapsackBruteForce(const vector<int>& nums, int sum, int currentIndex)
	{
		//刚好加到0，则返回true
		if (sum == 0)
			return true;
		//检查到最后一个也没凑成刚好为0的情况
		if (currentIndex >= nums.size())
			return false;
		//两个情况，当前元素是否放入一个子集
		bool b1 = likeKnapsackBruteForce(nums, sum, currentIndex + 1);//不放
		bool b2 = false;
		if (nums[currentIndex] <= sum)//小于和才继续放
			b2 = likeKnapsackBruteForce(nums, sum - nums[currentIndex], currentIndex + 1);
		return b1 || b2;//有一个成功的即可
	}
	bool canPartitionRecursive(vector<vector<int>>& dp, const vector<int>& num, int sum, int currentIndex) {
		// base check
		if (sum == 0)
			return true;
		if (currentIndex >= num.size())
			return false;
		// if we have not already processed a similar problem
		if (dp[currentIndex][sum] == -1) {//只计算没有算过的情况
			// recursive call after choosing the number at the currentIndex
			// if the number at currentIndex exceeds the sum, we shouldn't process this
			if (num[currentIndex] <= sum) {
				if (canPartitionRecursive(dp, num, sum - num[currentIndex], currentIndex + 1)) {
					dp[currentIndex][sum] = 1;
					return true;
				}
			}
			// recursive call after excluding the number at the currentIndex
			dp[currentIndex][sum] = canPartitionRecursive(dp, num, sum, currentIndex + 1) ? 1 : 0;
		}

		return dp[currentIndex][sum] == 1 ? true : false;
	}
	bool canPartitionDP(const vector<int>& nums, int sum)
	{
		//记录求和，dp[i][s]中，如果从第i个数字可以求到和s，则置为true
		vector<vector<bool>> dp(nums.size(), vector<bool>(sum + 1));
		//第一列，和为0，全都不放，也就是空子集可以凑成0，全为true
		for (int i = 0; i < nums.size(); ++i)
			dp[i][0] = true;
		//第一行，第一个数字能凑成的和只有它自己的数值
		for (int s = 1; s <= sum; ++s)
			dp[0][s] = (nums[s] == s ? true : false);
		//填充所有状态，直到所有数字被评判
#if 0
		for (int i = 1; i < nums.size(); ++i)
		{
			for (int s = 1; s <= sum; ++s)
			{
				//两个情况，没放入自己继承前状态或放了自己看剩余数有没有能凑成的
				bool b1 = false, b2 = false;
				b1 = dp[i - 1][s];
				if (nums[i] <= s)
					b2 = dp[i - 1][s - nums[i]];
				dp[i][s] = b1 || b2;
			}
		}
#endif
		//极简写法
		for (int i = 1; i < nums.size(); ++i)
			for (int s = 1; s <= sum; ++s)
				dp[i][s] = dp[i - 1][s] || (nums[i] <= s ? dp[i - 1][s - nums[i]] : false);
		return dp[nums.size() - 1][sum];
	}
};

//例：给定正数数组，确定是否存在总和等于给定S的子集（进阶 求子集是什么）
//分析，直接跟上题抽象完是一样的，还更加明确了一些
class SubsetSum {
public:
	virtual bool canPartition(const vector<int>& num, int sum) {
#if 0
		if (num.empty() || sum <= 0) return false;
		//定义动态规划状态数组
		vector<vector<bool>> dp(num.size(), vector<bool>(sum + 1));
		//第一列，空集能凑成和为0，全为true
		for (int i = 0; i < num.size(); ++i)
			dp[i][0] = true;
		//第一行，只能凑成等于自己的和
		for (int s = 1; s <= sum; ++s)
			dp[0][s] = num[0] == s ? true : false;
		//填充其他状态
		for (int i = 1; i < num.size(); ++i)
			for (int s = 1; s <= sum; ++s)
				dp[i][s] = dp[i - 1][s] || (num[i] <= s ? dp[i - 1][s - num[i]] : false);
		return dp[num.size() - 1][sum];
#endif
		//优化空间
		if (num.empty() || sum <= 0) return false;
		//定义动态规划状态数组
		vector<bool> dp(sum + 1);
		//空集凑成0，置为true
		dp[0] = true;
		//第一行，只能凑成等于自己的和
		for (int s = 1; s <= sum; ++s)
			dp[s] = num[0] == s ? true : false;
		//填充其他状态
		for (int i = 1; i < num.size(); ++i)
			for (int s = sum; s >= 0; --s)
				dp[s] = dp[s] || (num[i] <= s ? dp[s - num[i]] : false);
		return dp[sum];
	}
	//尝试输出子集，只能从未优化空间的完整状态中输出
	void printSubset(vector<vector<bool>>& dp, const vector<int>& nums, int sum)
	{
		int tmp = sum;
		vector<int> subset;
		if (dp[nums.size() - 1][sum] == false)
		{
			cout << "no subset" << endl;
			return;
		}
		for (int i = nums.size() - 1; i > 0; --i)
		{
			//如果不是继承来的，则往回找
			if (dp[i - 1][sum] != true)
			{
				subset.push_back(nums[i]);
				sum -= nums[i];
			}
		}
		//如果找到第一行的时候和还没有为0，则一定是第一个数字在子集里
		if (sum != 0)
			subset.push_back(nums[0]);
		cout << "sum = " << tmp << " 's subset: ";
		for (auto n : subset)
			cout << n << " ";
		cout << endl;
	}
};

//例：给定一组正数，将分组分成两个子集是他们子集和之间差异最小
//分析
// 两子集和问题的变种，这次允许两个子集和不相等，求最小差异
// 可以用dp[i][sum]，每行存储将i放入集合或不放入集合后的差值
// 所有填充完毕后，从最后一行找一个最小的，就是结果，有没有更好的办法？
// 有的，还是遵从sum/2那道题一样，只是最后有一点差别
class PartitionSet {
public:
	int canPartition(const vector<int>& num) {
		//暴力回溯 O(2^n) | O(n)
		return this->canPartitionRecursive(num, 0, 0, 0);
		//回溯+备忘录 O(n*s) s为所有数总和
		int sum = 0;
		for (auto n : num)
			sum += n;//计算所有数值和，备忘录记录索引和一个子集和，另一个子集和就是所有数值和减去记录和
		vector<vector<int>> memo(num.size(), vector<int>(sum + 1, -1));
		return this->canPartitionRecursiveMemo(memo, num, 0, 0, 0);
		//动态规划 O(n*s)
		return this->canPartitionDP(num, sum / 2,sum);
	}

private:
	int canPartitionRecursive(const vector<int>& num, int currentIndex, int sum1, int sum2) {
		//比较到最后一个，计算两个和的差值
		if (currentIndex == num.size())
			return abs(sum1 - sum2);
		//一个数值，往两个和里累加
		int diff1 = canPartitionRecursive(num, currentIndex + 1, sum1 + num[currentIndex], sum2);
		int diff2 = canPartitionRecursive(num, currentIndex + 1, sum1, sum2 + num[currentIndex]);
		//两个情况取最小
		return min(diff1, diff2);
	}
	int canPartitionRecursiveMemo(vector<vector<int>>& memo, const vector<int>& nums, int currentIndex, int sum1, int sum2)
	{
		if (currentIndex == nums.size())
			return abs(sum1 - sum2);
		if (memo[currentIndex][sum1] != -1)
			memo[currentIndex][sum1] = min(canPartitionRecursiveMemo(memo, nums, currentIndex + 1, sum1 + nums[currentIndex], sum2),
				canPartitionRecursiveMemo(memo, nums, currentIndex + 1, sum1, sum2 + nums[currentIndex]));
		//只有没计算过的结果，才会先计算，否则直接返回
		return memo[currentIndex][sum1];
	}
	int canPartitionDP(const vector<int>& nums, int sum, int total)
	{
		//根据和的一半，尝试找是否有和完全相等的两个子集
		vector<vector<bool>> dp(nums.size(), vector<bool>(sum + 1));
		//填充第一列，空集可以凑成和为0，全是true
		for (int i = 0; i < nums.size(); ++i)
			dp[i][0] = true;
		//填充第一行，只有一个数字，只能凑齐等于自身的和
		for (int s = 1; s <= sum; ++s)
			dp[0][s] = s == nums[0] ? true : false;
		//填充其他情况，子集不包含本数和包含本数两个情况，有一个符合就为true
		for (int i = 1; i < nums.size(); ++i)
			for (int s = 1; s <= sum; ++s)
				dp[i][s] = dp[i - 1][s] || (nums[i] <= s ? dp[i - 1][s - nums[i]] : false);
		//找到了完全相等的两个子集和，也就是差异为0，省略这一步直接走下面逻辑也是一样的
		if (dp[nums.size() - 1][sum] == true)
			return 0;
		//没找到则在最后一行，找到最大为true的情况，代表子集最接近和一半的情况，也就是差值最小的情况
		int maxIndex = sum;
		while (!dp[nums.size() - 1][maxIndex])
			--maxIndex;
		//整数除法都是向下舍的，所以应该不用加abs
		return total - maxIndex - maxIndex;
	}
};

//
//总结
// 0-1背包可以用贪心、回溯和动态规划求解
// 其中动态规划最重要也最高效
// 回溯+备忘录方式接近动态规划
//

//练习：记错时间，订阅过期了，不过已经看了90%，在其他地方补一下

int main()
{
	std::cout << "Hello World!\n";
}