// grokking_03.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <algorithm>
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

//例：

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
//

int main()
{
	std::cout << "Hello World!\n";
}
