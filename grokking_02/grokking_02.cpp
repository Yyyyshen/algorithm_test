// grokking_02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <time.h>
#include <vector>
#include <unordered_map>
using namespace std;

//
//滑动窗口
//

//例题：一个数组，求所有K个元素子序列的平均值
class AverageOfSubarrayOfSizeK {
public:
	static vector<double> findAverages(int K, const vector<int>& arr) {
		//暴力解，分别求每五个的总和并计算平均值
		//时间复杂度O(N*K)
#if 0
		vector<double> ret;
		double sum;
		for (int i = 0; i <= arr.size() - K; ++i)
		{
			sum = 0;
			for (int j = 0; j < K; ++j)
				sum += arr[i + j];
			ret.push_back(sum / K);
		}
		return ret;
#endif

		//更优解，每个子序列都有四个元素是重叠的，想办法重用起来
		//时间复杂度降到O(N)
#if 1
		vector<double> ret;
		double window_sum = 0;
		int window_start = 0;
		for (int window_end = 0; window_end < arr.size(); ++window_end)
		{
			window_sum += arr[window_end];
			if (window_end >= K - 1)//从第5个元素开始
			{
				//计算平均值
				ret.push_back(window_sum / K);
				//减掉窗口头元素并后移
				window_sum -= arr[window_start++];
			}
		}
		return ret;
#endif
	}
};
void test_AverageOfSubarrayOfSizeK()
{
	vector<double> result =
		AverageOfSubarrayOfSizeK::findAverages(5, vector<int>{1, 3, 2, 6, -1, 4, 1, 8, 2});
	cout << "Averages of subarrays of size K: ";
	for (double d : result) {
		cout << d << " ";
	}
	cout << endl;
}
//

//例：给定正数数组和一个正数S，找出总和大于等于S的最小连续子数组的长度
class MinSizeSubArraySum {
public:
	static int findMinSubArray(int S, const vector<int>& arr) {
		//自己写的
#if 0
		int window_start = 0, window_end = 0, window_sum = 0;
		int ret = INT_MAX;
		while (true)
		{
			if (window_sum >= S) {
				ret = min(ret, window_end - window_start);
				window_sum -= arr[window_start++];
			}
			else
			{
				if (window_end == arr.size())
					break;
				window_sum += arr[window_end++];
			}

		}
		return ret == INT_MAX ? -1 : ret;
#endif
		//完全套用上面滑动窗口的格式
		//窗口结尾到达符合条件的位置时缩小窗口开端，直到不满足条件
		//内层循环其实只是处理每个元素一次，不会造成乘法复杂度增加而是O(n+n)
		//没有额外空间，复杂度O(1)
		int window_start = 0, window_sum = 0, ret = INT_MAX;
		for (int window_end = 0; window_end < arr.size(); ++window_end)
		{
			window_sum += arr[window_end];
			while (window_sum >= S)
			{
				ret = min(ret, window_end - window_start + 1);
				window_sum -= arr[window_start++];
			}
		}
		return ret == INT_MAX ? -1 : ret;
	}
};

//例：给定字符串，找到不超过K个不同字符的最长子串长度
class LongestSubstringKDistinct {
public:
	static int findLength(const string& str, int k) {
		if (k >= str.size()) return str.size();
		int maxLength = 0, window_start = 0;
		unordered_map<char, int> map;//记录字符出现次数，容器大小就是不同字母个数
		for (int window_end = 0; window_end < str.size(); ++window_end)
		{
			++map[str[window_end]];
			while (map.size() > k)
			{
				char start = str[window_start++];
				if (--map[start] <= 0)
					map.erase(start);
			}
			maxLength = max(maxLength, window_end - window_start + 1);
		}
		//时间复杂度O(N+N)，空间O(K+1)
		return maxLength;
	}
};

//例，给定字符串，找出所有字符都不同的最长子串长度
class NoRepeatSubstring {
public:
	static int findLength(const string& str) {
#if 0
		int maxLength = 0, window_start = 0;
		unordered_map<char, int> map;
		for (int window_end = 0; window_end < str.size(); ++window_end)
		{
			char c = str[window_end];
			++map[c];
			while (map[c] > 1)
			{
				char start = str[window_start++];
				--map[start];
			}
			maxLength = max(maxLength, window_end - window_start + 1);
		}
		return maxLength;
#endif
		//不同的答案
		int windowStart = 0, maxLength = 0;
		unordered_map<char, int> charIndexMap;
		for (int windowEnd = 0; windowEnd < str.length(); windowEnd++) {
			char rightChar = str[windowEnd];
			if (charIndexMap.find(rightChar) != charIndexMap.end())
				//碰到相同字符，则挪动开头到上一次重复字符出现的位置（若开头已经超过此位置则不需要）
				windowStart = max(windowStart, charIndexMap[rightChar] + 1);
			//记录每个字符最后一次出现的位置
			charIndexMap[rightChar] = windowEnd;
			maxLength = max(maxLength, windowEnd - windowStart + 1);
		}

		return maxLength;
	}
};

//例：给定字符串，允许用不超过k个字母替换，求替换后相同字母最长的子串长度
//分析：就是说不同字母的个数总和不超过k个的最长子串
class CharacterReplacement {
public:
	static int findLength(const string& str, int k) {
		int maxLength = 0, window_start = 0, max_repeat = 0;
		unordered_map<char, int> map;
		for (int window_end = 0; window_end < str.size(); ++window_end)
		{
			char end = str[window_end];
			++map[end];
			//只依据最多重复的字符，计算其他字符的替换
			max_repeat = max(max_repeat, map[end]);
			if (window_end - window_start + 1 - max_repeat > k)//其他不同字符数量大于k，则挪动窗口
				--map[str[window_start++]];

			//符合条件计算一次最大长度
			maxLength = max(maxLength, window_end - window_start + 1);
		}
		return maxLength;
	}
};

//
//总结
// 
// 基本固定公式
// 
// 定义窗口开头结尾两个指针
// 尾指针往后遍历
// 每次针对尾部元素进行判断
// 不满足条件时，调整头指针
// 满足条件则记录一次结果值
//


//练习：


int main()
{
	clock_t start = clock();
	test_AverageOfSubarrayOfSizeK();
	clock_t finish = clock();
	cout << "func call times cost: " << finish - start << " ms" << endl;
}
