// grokking_03.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
using namespace std;

//
//合并区间
// 
//循环排序
// 
//链表反转
//

//=======================================================================

//
//合并区间
//

//例：给定区间列表，合并其中可以合并的区间
class Interval {
public:
	int start = 0;
	int end = 0;

	Interval(int start, int end) {
		this->start = start;
		this->end = end;
	}
};
//分析，当区间a开头小于区间b开头，且b区间开头小于a区间结尾，则可以合并
//合并后区间为a开头与max(a结尾,b结尾)
//可以先根据所有区间的头进行排序，保证a.start <= b.start成立
//当 b.start <= a.end，则合并后的区间c
// c.start = a.start; c.end = max(a.end, b.end);
//把区间c与下一个区间同样进行这个逻辑判断，直到没有重合区间，则加入到结果列表
class MergeIntervals {
public:
	static vector<Interval> merge(vector<Interval>& intervals) {
		int n = intervals.size();
		if (n < 2) return intervals;
		//lambda表达式定义规则，根据区间头大小进行排序
		sort(intervals.begin(), intervals.end(),
			[](const Interval& a, const Interval& b) {
				return a.start < b.start;
			});
		vector<Interval> mergedIntervals;
		Interval tmp = intervals[0];
		for (int i = 1; i < n; ++i)
		{
			//区间不重叠，则将上一次的区间加入结果集，并准备继续判断
			if (intervals[i].start > tmp.end)
			{
				mergedIntervals.push_back(tmp);
				tmp = intervals[i];
			}
			else
			{
				tmp.end = max(tmp.end, intervals[i].end);
			}
		}
		//最后一个区间记得放进结果
		mergedIntervals.push_back(tmp);

		return mergedIntervals;
	}
};

//例：给定无重叠的区间排序列表和一个额外区间，将这个额外区间合并进去
class InsertInterval {
public:
	static vector<Interval> insert(const vector<Interval>& intervals, Interval newInterval) {
		//将新区间放进去，然后复用上一例的逻辑，但本例输入为const，需要一个只读遍历逻辑
#if 0
		intervals.push_back(newInterval);
		sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {return a.start < b.start; });
		vector<Interval> mergedIntervals;
		Interval tmp = intervals[0];
		for (int i = 1; i < intervals.size(); ++i)
		{
			if (intervals[i].start > tmp.end)
			{
				mergedIntervals.push_back(tmp);
				tmp = intervals[i];
			}
			else
			{
				tmp.end = max(intervals[i].end, tmp.end);
			}
		}
		mergedIntervals.push_back(tmp);
		return mergedIntervals;
#endif
		//由于输入区间列表本身是排序的，所以根据区间情况逐个判断
		if (intervals.empty()) return vector<Interval>{newInterval};//参数检查
		vector<Interval> mergedIntervals;
		int i = 0;
		//区间尾小于新区间头的，直接全部添加到结果集
		while (i < intervals.size() && intervals[i].end < newInterval.start)
		{
			mergedIntervals.push_back(intervals[i]);
			++i;
		}
		//走完上一轮循环，则自带一个先决条件 区间尾大于等于新区间头
		//则，有重合部分的另一个条件是 区间头小于等于新区间尾
		//合并这些部分
		while (i < intervals.size() && intervals[i].start <= newInterval.end)
		{
			newInterval.start = min(intervals[i].start, newInterval.start);
			newInterval.end = max(intervals[i].end, newInterval.end);
			++i;
		}
		//合并后的区间加入结果集
		mergedIntervals.push_back(newInterval);
		//将后续不重合的区间加入结果集
		while (i < intervals.size())
		{
			mergedIntervals.push_back(intervals[i]);
			++i;
		}
		return mergedIntervals;
	}
};

//例：给定两个排序区间，求交集
class IntervalsIntersection {
public:
	static vector<Interval> merge(const vector<Interval>& arr1, const vector<Interval>& arr2) {
		vector<Interval> result;
		int i = 0, j = 0;
		while (i < arr1.size() && j < arr2.size())
		{
			//有交集的情况
			if ((arr1[i].start >= arr2[j].start && arr1[i].start <= arr2[j].end) ||
				(arr2[j].start >= arr1[i].start && arr2[j].start <= arr1[i].end))
			{
				int s = max(arr1[i].start, arr2[j].start);
				int e = min(arr1[i].end, arr2[j].end);
				result.push_back({ s,e });
			}
			//谁先结束就先往后移动比较
			if (arr1[i].end < arr2[j].end)
				++i;
			else
				++j;
		}
		return result;
	}
};

//例：给定一个时间间隔数组，代表每件事需要的时间段，判断一个人能否做所有事
//其实就是给定区间列表，看是否有交集，结果为反即可
class ConflictingAppointments {
public:
	static bool canAttendAllAppointments(vector<Interval>& intervals) {
		if (intervals.empty()) return true;
		//先排序，然后逐个比较，看是否有交集
		sort(intervals.begin(), intervals.end(),
			[](const Interval& a, const Interval& b) {return a.start < b.start; });
		for (int i = 1; i < intervals.size(); ++i)
			if (intervals[i].start < intervals[i - 1].end) //注意交集比较时，没有<=，只有并集才需要判断相等
				return false;
		return true;
	}
};

//
//总结
// 涉及区间问题时，有几种情况
// 区间a和b 不重叠  b在a后 或 a在b后
// 区间a和b 部分重叠 b在a后 或 a在b后
// 区间a和b 相互包含 a包含b 或 b包含a
// 此类问题
// 我们需要找到重叠区间
// 另外可能
// 重叠情况下，合并区间
// 
//做法
// 根据区间头大小进行排序
// 之后就可以根据每个区间的头与前一个区间尾比较，看是否能够合并
// 取交集的话，看区间头是否在另一个区间内
//

//练习：给定会议时间列表，找出举行所有会议需要的房间数
//也就是找出在所有区间内，同时有交集的区间数量
class Meeting {
public:
	int start = 0;
	int end = 0;

	Meeting(int start, int end) {
		this->start = start;
		this->end = end;
	}
};
class MinimumMeetingRooms {
public:
	static int findMinimumMeetingRooms(vector<Meeting>& meetings) {
		//两层循环思路
		//排序区间列表
		//根据排序的头尾，外层循环遍历所有时间点
		//内层循环看命中了几个区间，最后取最大值
		int n = meetings.size();
		if (n == 0) return 0;
		if (n == 1) return 1;
		int ret = -1;
		sort(meetings.begin(), meetings.end(),
			[](const Meeting& a, const Meeting& b) {return a.start < b.start; });
		int start = meetings[0].start, end = meetings[meetings.size() - 1].end;
		for (double i = start + 0.5; i < end; ++i)//粒度要比间隔小
		{
			int hits = 0;
			for (int j = 0; j < meetings.size(); ++j)
				if (i > meetings[j].start && i < meetings[j].end)
					++hits;
			ret = max(hits, ret);
		}
		return ret;

		//单次循环解法
		//排序区间列表
		//用一个最小堆存储活动的会议（结束时间小于下次会议开始时间）
		//每次把当前会议入堆，将开完的会议出堆
		//过程中，堆的最大大小就是需要的最小房间数
		int n = meetings.size();
		if (n < 2) return n;
		int ret = -1;
		//以会议结束时间为标准建立最小堆
		priority_queue<Meeting, vector<Meeting>, end_compare> active_rooms;
		sort(meetings.begin(), meetings.end(),
			[](const Meeting& a, const Meeting& b) {return a.start < b.start; });
		for (int i = 0; i < n; ++i)
		{
			while (!active_rooms.empty() && active_rooms.top().end <= meetings[i].start)
				active_rooms.pop();
			active_rooms.push(meetings[i]);
			ret = max((int)active_rooms.size(), ret);
		}
		//时间复杂度分析，外层循环 N 内层循环遍历优先级队列 logN
		//O(N*logN)
		//空间在最坏情况下，所有会议入队 O(N)
		return ret;
	}
	struct end_compare
	{
		bool operator()(const Meeting& a, const Meeting& b) { return a.end > b.end; }
	};
};

//练习：给定任务列表，每个任务包含信息为开始、结束时间以及CPU负载
//找出同一时间内，CPU最大负载
//与上题基本相同，只不过这次相加取最大的是每个元素内的信息
class Job {
public:
	int start = 0;
	int end = 0;
	int cpuLoad = 0;

	Job(int start, int end, int cpuLoad) {
		this->start = start;
		this->end = end;
		this->cpuLoad = cpuLoad;
	}
};
class MaximumCPULoad {
public:
	struct end_comp {
		bool operator()(const Job& a, const Job& b) { return a.end > b.end; }
	};
	static int findMaxCPULoad(vector<Job>& jobs) {
		int maxCPULoad = 0, curCPULoad = 0;
		//根据结束时间建立小顶堆
		priority_queue<Job, vector<Job>, end_comp> q;
		//按开始时间排序
		sort(jobs.begin(), jobs.end(),
			[](const Job& a, const Job& b) {return a.start < b.start; });
		for (auto job : jobs)
		{
			while (!q.empty() && q.top().end < job.start)//已经完成的任务出队
			{
				curCPULoad -= q.top().cpuLoad;
				q.pop();
			}
			q.push(job);
			curCPULoad += job.cpuLoad;
			maxCPULoad = max(curCPULoad, maxCPULoad);
		}

		return maxCPULoad;
	}
};

//练习：给定一批员工的工作时间表，判断是否有所有员工都空闲的时间，求时间段列表
// 假定列表中各员工按开始时间排序，且每个员工自己的时间表按开始时间排序
class EmployeeFreeTime {
public:
	using work_time = pair <Interval, pair<int, int>>;
	struct work_comp {
		bool operator()(const work_time& a, const work_time& b) { return a.first.start > b.first.start; }
	};
	static vector<Interval> findEmployeeFreeTime(const vector<vector<Interval>>& schedule) {
		//简单解法，把所有员工所有工作时间放在一个列表中，按开始时间排序，之后遍历求出补集
#if 0
		vector<Interval> tmp;
		for (auto employee : schedule)
			for (auto work : employee)
				tmp.push_back(work);
		sort(tmp.begin(), tmp.end(),
			[](const Interval& a, const Interval& b) {return a.start < b.start; });
		vector<Interval> result;
		for (int i = 1; i < tmp.size(); ++i)
			if (tmp[i].start > tmp[i - 1].end)
				result.push_back({ tmp[i - 1].end,tmp[i].start });
		return result;
#endif
		//更好的解法
		//暴力解没有利用到原本就有的条件，即每个员工的工作时间都是排序好的
		//可以利用最小堆，入队每个员工的第一段工作时间，以开始时间排序
		//之后，每个有人在工作的时间段的结束时间与下一段有人在工作的时间段的开始时间对比，有差距，则是所有人都空闲的时间
		//另外，每次出队时，需要加入当前这个员工的下一段工作时间，所以需要定义一个pair标记是哪个员工和进行到哪个时间段了
		vector<Interval> result;
		if (schedule.empty()) return result;
		priority_queue<work_time, vector<work_time>, work_comp> q;
		for (int i = 0; i < schedule.size(); ++i)
			q.push({ schedule[i][0],{i,0} });
		work_time prev = q.top();
		while (!q.empty())
		{
			work_time tmp = q.top();
			q.pop();

			if (prev.first.end < tmp.first.start)
				result.push_back({ prev.first.end,tmp.first.start });
			else
				if (prev.first.end < tmp.first.end)//这里要注意，只有结束时间更晚，才替换
					prev = tmp;

			if (tmp.second.second + 1 < schedule[tmp.second.first].size())
				q.push({ schedule[tmp.second.first][tmp.second.second + 1],{tmp.second.first,tmp.second.second + 1} });
		}

		return result;
	}
};

//=======================================================================

//
//循环排序
//

//例：1到n范围的数组，原地排序
//数值范围确认，则与索引可以建立一种映射关系，将元素换到对应位置即可
class CyclicSort {
public:
	static void sort(vector<int>& nums) {
		int start = 0;
		while (start < nums.size())
		{
			if (nums[start] == nums[nums[start] - 1])
				++start;
			else
				swap(nums[start], nums[nums[start] - 1]);
		}
	}
};

//例：给定n个0~n的数字，找出缺失的数字
class MissingNumber {
public:
	static int findMissingNumber(vector<int>& nums) {
		//位图法，需要额外空间
#if 0
		vector<int> memo(nums.size() + 1, -1);
		for (auto num : nums)
			memo[num] = num;
		for (int i = 0; i < memo.size(); ++i)
			if (memo[i] == -1)
				return i;
		return -1;
#endif
		//依然使用上一例中的原地交换，也需要两次循环
		int i = 0;
		while (i < nums.size())
		{
			if (nums[i] != i && nums[i] < nums.size())//范围比个数大一，跳过超过的情况
				swap(nums[i], nums[nums[i]]);
			else
				++i;
		}
		//遍历一遍，没有被换到正确位置的数字（超过数组范围的那个）的索引就是缺失的数
		for (int i = 0; i < nums.size(); ++i)
			if (nums[i] != i)
				return i;
		return -1;
	}
};

//例：给定1~n范围内数字查找重复数字
class FindAllDuplicate {
public:
	static vector<int> findNumbers(vector<int>& nums) {
		//位图法都大同小异，略过，找原地操作的方法
		vector<int> duplicateNumbers;
		//同样是把数字往对应的位置上放，当交换时发现两个数相等，则记录并进行下一个
		int i = 0;
		while (i < nums.size())
		{
			if (nums[i] != i + 1)
			{
				if (nums[i] == nums[nums[i] - 1])
				{
					//或者全换完，出去的时候再遍历一遍找不在正确位置的元素
					duplicateNumbers.push_back(nums[i]);
					++i;
				}
				else
					swap(nums[i], nums[nums[i] - 1]);
			}
			else
				++i;
		}

		return duplicateNumbers;
	}
};

//
//总结
// 用于处理涉及给定范围内数字的数组问题
// 由于范围确定，那么元素与数组索引之间一定存在一种映射关系
// （以为我的理解，这类问题会想到位图法）
// 本方法思想是
// 在原地处理的基础上
// 根据映射关系在循环中交换元素到正确的位置
//

//练习：给定1到n的n个数字，其中有一个重复，找出重复的数字以及因为重复而缺失的数字
class FindCorruptNums {
public:
	static vector<int> findNumbers(vector<int>& nums) {
		int i = 0;
		while (i < nums.size())
		{
			//交换到正确位置，并且如果交换的数字相等，则跳过，避免死循环
			if (nums[i] != nums[nums[i] - 1])
				swap(nums[i], nums[nums[i] - 1]);
			else
				++i;
		}
		for (i = 0; i < nums.size(); ++i)
			if (nums[i] != i + 1)
				//不在正确位置上的数字为重复数字，而其索引+1，为缺失数字
				return { i + 1,nums[i] };
		return vector<int>{-1, -1};
	}
};

//练习：给定未排序数组，找到缺失的最小正数
class FirstSmallestMissingPositive {
public:
	static int findNumber(vector<int>& nums) {
		//跟前面题一样，把数字换到正确位置，只不过超过范围的和负数跳过
		int i = 0;
		while (i < nums.size())
		{
			if (nums[i] == nums[nums[i] - 1] && nums[i] > 0 && nums[i] <= nums.size())
				swap(nums[i], nums[nums[i] - 1]);
			else
				++i;
		}
		for (int i = 0; i < nums.size(); ++i)
			if (nums[i] != i + 1)
				return i + 1;
		return nums.size() + 1;//都符合，则缺少的是最后一个数+1，也是size+1
	}
};

//练习：找出前K个缺失的正数
class FirstKMissingPositive {
public:
	static vector<int> findNumbers(vector<int>& nums, int k) {
		//跟之前一样的思路，将数字都换到正确的位置
		//之后遍历一遍，与索引位置不对应的是缺失的数字
		//不同的是，如果数组中缺失的个数小于k，需要从数组大小之后的数字往里填
		//而不再正确位置的数字可能本身就是超过数组大小的，所以要记录下来并跳过
		vector<int> missingNumbers;
		int i = 0;
		while (i < nums.size())
		{
			if (nums[i] != nums[nums[i] - 1] && nums[i] > 0 && nums[i] <= nums.size())
				swap(nums[i], nums[nums[i] - 1]);
			else
				++i;
		}
		unordered_set<int> memo;
		for (int i = 0; i < nums.size() && missingNumbers.size() < k; ++i)
		{
			if (nums[i] != i + 1)
			{
				memo.insert(nums[i]);
				missingNumbers.push_back(i + 1);
			}
		}
		int miss = nums.size() + 1;
		while (missingNumbers.size() < k)
		{
			if (memo.find(miss) != memo.end())
				++miss;
			else
				missingNumbers.push_back(miss++);
		}

		return missingNumbers;
	}
};

//=======================================================================

//
//反转链表
//

//例：反转链表
class ListNode {
public:
	int value = 0;
	ListNode* next;

	ListNode(int value) {
		this->value = value;
		next = nullptr;
	}
};
class ReverseLinkedList {
public:
	static ListNode* reverse(ListNode* head) {
		//一般例子都是使用三个辅助成员，而其实参数head本身就可以作为一个成员使用
		ListNode* prev = nullptr, * tmp = nullptr;
		while (head != nullptr)
		{
			tmp = head->next;
			head->next = prev;
			prev = head;
			head = tmp;
		}
		return prev;
	}
};

//例：反转部分链表
class ReverseSubList {
public:
	static ListNode* reverse(ListNode* head, int p, int q) {
		if (p >= q) return head;//区间不正确
		//记录q指向点的下一个，p指向点以及其前一个
		ListNode* qnext = head, * cur_prev = head, * cur = nullptr;
		//找pprev
		for (int i = 1; i < p - 1 && cur_prev != nullptr; ++i)
			cur_prev = cur_prev->next;
		//p超过链长
		if (cur_prev == nullptr || cur_prev->next == nullptr) return head;
		cur = cur_prev->next;
		//特殊情况，p指向头，变种题目就是反转前k个元素
		if (p == 1)
		{
			cur_prev = nullptr;
			cur = head;
		}
		//找qnext
		for (int i = 1; i < q + 1 && qnext != nullptr; ++i)
			qnext = qnext->next;
		//反转p到q
		ListNode* prev = qnext, * tmp = nullptr;
		while (cur != qnext)
		{
			tmp = cur->next;
			cur->next = prev;
			prev = cur;
			cur = tmp;
		}
		//p前点拼接
		if (cur_prev != nullptr)
			cur_prev->next = prev;
		else//p=1也就是指向头时的特殊情况
			head = prev;
		return head;
	}
};

//例：反转链表中每K个元素
class ReverseEveryKElements {
public:
	static ListNode* reverse(ListNode* head, int k) {
		//检查参数
		if (head == nullptr || k <= 1) return head;
		//记录 每次k个元素之后的下一个元素，也是下次反转的头元素；当前反转头，以及所需的辅助指针
		ListNode* everyKhead = head, * cur = nullptr, * prev = nullptr, * tmp = nullptr;
		//记录 每次最开始的头指针，用于串联每次反转后前面的部分
		ListNode* everyold = nullptr, * tmp2 = nullptr;
		do
		{
			//每次从k个元素下一个开始
			cur = everyKhead;
			tmp2 = everyKhead;
			//找到下一个备用，也是反转后第一个prev的指向点，可用于串联后面
			for (int i = 0; i < k && everyKhead != nullptr; ++i)
				everyKhead = everyKhead->next;
			prev = everyKhead;
			while (cur != everyKhead)
			{
				tmp = cur->next;
				cur->next = prev;
				prev = cur;
				cur = tmp;
			}
			if (everyold == nullptr)
				head = prev;
			else
				everyold->next = prev;
			everyold = tmp2;
		} while (everyKhead != nullptr);
		return head;

		//标准答案，直接反转后再串联前后的方法，比自己的方法少用一个辅助指针
		if (k <= 1 || head == nullptr) {
			return head;
		}

		ListNode* current = head, * previous = nullptr;
		while (true) {
			ListNode* lastNodeOfPreviousPart = previous;
			// after reversing the LinkedList 'current' will become the last node of the sub-list
			ListNode* lastNodeOfSubList = current;
			ListNode* next = nullptr;  // will be used to temporarily store the next node
			// reverse 'k' nodes
			for (int i = 0; current != nullptr && i < k; i++) {
				next = current->next;
				current->next = previous;
				previous = current;
				current = next;
			}

			// connect with the previous part
			if (lastNodeOfPreviousPart != nullptr) {
				lastNodeOfPreviousPart->next =
					previous;  // 'previous' is now the first node of the sub-list
			}
			else {         // this means we are changing the first node (head) of the LinkedList
				head = previous;
			}

			// connect with the next part
			lastNodeOfSubList->next = current;

			if (current == nullptr) {  // break, if we've reached the end of the LinkedList
				break;
			}
			// prepare for the next sub-list
			previous = lastNodeOfSubList;
		}

		return head;
	}
};

//
//总结
// 一些问题中，需要反转（部分）链表
// 时间复杂度上，使用额外的新空间建立一条反向链表 与 就地反转
// 都需要两次循环，建立/回收 与 反转/反转
// 为了节省空间，最好还是就地反转
// 例如之前的回文链表检查，除了两点法，还用到了原地反转后半部分链表
//

//练习：交替反转链表中每k个元素（k个元素反转，下k个元素不反转，依次类推
class ReverseAlternatingKElements {
public:
	static ListNode* reverse(ListNode* head, int k) {
		if (head == nullptr || k < 2) return head;
		ListNode* cur = head, * prev = nullptr, * tmp = nullptr;
		while (cur != nullptr)
		{
			ListNode* prev_tmp = prev, * cur_tmp = cur;
			//反转当前
			for (int i = 0; i < k; ++i)
			{
				tmp = cur->next;
				cur->next = prev;
				prev = cur;
				cur = tmp;
			}

			cur_tmp->next = cur;//链接后面
			if (prev_tmp == nullptr)
				head = prev;
			else
				prev_tmp->next = prev;//链接前面

			//交替进行
			for (int i = 0; i < k && cur != nullptr; ++i)
			{
				prev = cur;
				cur = cur->next;
			}
		}
		return head;
	}
};

//练习：给定单链表，右旋转k个节点
class RotateList {
public:
	static ListNode* rotate(ListNode* head, int rotations) {
		//参数检查
		if (head == nullptr || head->next == nullptr || rotations <= 0) return head;
		//记录 链尾，当前处理节点，以及下一个要处理的节点
		ListNode* tail = head, * cur = head, * next = nullptr;
		//找到链尾
		while (tail->next != nullptr) tail = tail->next;
		//循环链接
		for (int i = 0; i < rotations; ++i)
		{
			next = cur->next;
			cur->next = nullptr;
			tail->next = cur;
			tail = cur;
			cur = next;
			head = cur;
		}
		return head;

		//优化，旋转中，如果旋转次数超过链长，超过部分实际上就相当于又从原链表开始操作
		//所以，实际上可以在找链尾时顺便计算链长，之后旋转次数对链长取模，避免不必要的操作
		//另外，对于反转操作，不需要每次都 断开第一个节点-》链接到尾部-》重新记录头尾
		//可以直接把尾部指向头，形成一个环，然后找一个指针走模长的步数，并在此处断开链环即可
		if (head == nullptr || head->next == nullptr || rotations <= 0)
			return head;
		ListNode* tail = head;
		int link_len = 1;
		//求链尾和链长
		while (tail->next != nullptr)
		{
			tail = tail->next;
			++link_len;
		}
		//计算真实操作步骤
		int op_nums = link_len - (rotations % link_len);
		//然链成环
		tail->next = head;
		//走对应步数
		for (int i = 0; i < op_nums; ++i)
			tail = tail->next;
		//断开环
		head = tail->next;
		tail->next = nullptr;
		return head;
	}
};

//=======================================================================

//总结
// 每个问题看先排序是否有助于解决问题
// 优先级队列应用广泛，涉及到k个列表处理时很有用
// 循环排序除了使用额外空间以类似位图的形式使用之外，还可以原地交换每个元素到对应位置
// 反转链表要熟练
// 旋转链表的真实操作次数要根据链长进行优化，另外可以先首尾连成环，找到位置后再断开
//

int main()
{
	std::cout << "Hello World!\n";
}
