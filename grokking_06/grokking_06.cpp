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

int main()
{
	std::cout << "Hello World!\n";
}