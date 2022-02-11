// grokking_03.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
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

//例：

//
//总结
//

int main()
{
	std::cout << "Hello World!\n";
}
