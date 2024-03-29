﻿// grokking_02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <time.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

//
//滑动窗口
//
//两点法
// 
//快慢指针
//

//=======================================================================

//滑动窗口

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


//练习：给定字符串和一个模式串，找出字符串是否包含模式串的任何排列
//分析，窗口大小固定，即模式串长度，使用map作为模式串统计
class StringPermutation {
public:
	static bool findPermutation(const string& str, const string& pattern) {
		unordered_map<char, int> map;
		int window_start = 0, matched = 0;//记录已经匹配的字符
		for (auto c : pattern)
			++map[c];
		for (int window_end = 0; window_end < str.size(); ++window_end)
		{
			char right = str[window_end];
			//在模式串里，匹配到了，则计数
			if (map.find(right) != map.end())
				if (--map[right] == 0)
					++matched;

			//所有字符都匹配，则返回true
			if (matched == map.size())
				return true;

			if (window_end >= pattern.size() - 1)
			{
				char start = str[window_start++];
				//某字符从匹配变为不匹配
				if (map.find(start) != map.end())
					if (map[start]++ == 0)
						--matched;
			}
		}
		//时间复杂度O(N+M)，M为模式串长度，空间O(M)
		return false;
	}
};

//练习：给定字符串和一个模式串，找出模式串各排列在主串中出现的索引
//分析，与上题类似，只不过每次匹配到，不直接返回，而是记录窗口初始位置
class StringAnagrams {
public:
	static vector<int> findStringAnagrams(const string& str, const string& pattern) {
		vector<int> resultIndices;
		unordered_map<char, int> map;
		int window_start = 0, matched = 0;
		for (auto c : pattern)
			++map[c];
		for (int window_end = 0; window_end < str.size(); ++window_end)
		{
			char right = str[window_end];
			if (map.find(right) != map.end())
				if (--map[right] == 0)
					++matched;
			if (matched == map.size())
				resultIndices.push_back(window_start);
			if (window_end >= pattern.size() - 1)
			{
				char left = str[window_start++];
				if (map.find(left) != map.end())
					if (map[left]++ == 0)
						--matched;
			}
		}
		return resultIndices;
	}
};

//练习：给定字符串和模式串，找出最小包含模式串所有字符的窗口
//分析，还是与上面差不多的题目，只是匹配到之后，记录最小窗口
class MinimumWindowSubstring {
public:
	static string findSubstring(const string& str, const string& pattern) {
		unordered_map<char, int> map;
		int window_start = 0, matched = 0;
		int memo[2] = { -1 };//记录最小窗口索引
		for (auto c : pattern)
			++map[c];
		for (int window_end = 0; window_end < str.size(); ++window_end)
		{
			char right = str[window_end];
			if (map.find(right) != map.end())
				if (--map[right] == 0)
					++matched;

			//只要符合，缩小窗口继续验证
			while (matched == map.size())
			{
				if (memo[1] - memo[0] > window_end - window_start || memo[0] == -1)
				{
					memo[0] = window_start;
					memo[1] = window_end;
				}
				char left = str[window_start++];
				if (map.find(left) != map.end())
					if (map[left]++ == 0)
						--matched;
			}
		}
		if (memo[0] == -1)
			return "";
		return str.substr(memo[0], memo[1] + 1);
	}
};

//练习：给定字符串和单词列表，找到所有是单词列表串联而成子串的起始索引
//分析，相当于字符的高级版，记录每个单词的出现频率，之后用现成的substr找子串，如果找到了所有单词，则记录一次结果
class WordConcatenation {
public:
	static vector<int> findWordConcatenation(const string& str, const vector<string>& words) {
		unordered_map<string, int> wordFrequencyMap;
		for (auto word : words) {
			wordFrequencyMap[word]++;
		}

		vector<int> resultIndices;
		int wordsCount = words.size(), wordLength = words[0].length();

		for (int i = 0; i <= int(str.length()) - wordsCount * wordLength; i++) {
			unordered_map<string, int> wordsSeen;
			for (int j = 0; j < wordsCount; j++) {
				int nextWordIndex = i + j * wordLength;
				// get the next word from the string
				string word = str.substr(nextWordIndex, wordLength);
				if (wordFrequencyMap.find(word) ==
					wordFrequencyMap.end()) {  // break if we don't need this word
					break;
				}

				wordsSeen[word]++;  // add the word to the 'wordsSeen' map

				// no need to process further if the word has higher frequency than required
				if (wordsSeen[word] > wordFrequencyMap[word]) {
					break;
				}

				if (j + 1 == wordsCount) {  // store index if we have found all the words
					resultIndices.push_back(i);
				}
			}
		}

		return resultIndices;
	}
};

//=======================================================================

//两点法

//例：给定排序数组和一个目标总和，找到一个总和等于目标值的索引对
//分析，暴力解就是两层for循环，相加求解，O(N*N)；优化暴力解，由于有序，内层循环用二分，O(N*logN)
//力扣第一题中是非排序数组的两数之和，是一次遍历，每次用map记录已遍历值，下一次遍历在map寻找目标值-元素值
//本例是排序数组，直接两点法，O(N)，空间O(1)
class PairWithTargetSum {
public:
	static pair<int, int> search(const vector<int>& arr, int targetSum) {
		int p1 = 0, p2 = arr.size() - 1;
		while (p1 < p2)
		{
			if (arr[p1] + arr[p2] == targetSum)
				return { p1,p2 };
			if (arr[p1] + arr[p2] < targetSum)
				++p1;
			else
				--p2;
		}
		return make_pair(-1, -1);

		//map法，时间O(N)，空间O(N)
		unordered_map<int, int> nums;
		for (int i = 0; i < arr.size(); ++i)
		{
			if (nums.find(targetSum - arr[i]) != nums.end())
				return { nums[targetSum - arr[i]],i };

			nums[arr[i]] = i;
		}
		return { -1,-1 };
	}
};

//例：给定排序数组，移除所有重复项，不能使用额外空间，返回不重复的子序列长度
//用一个索引标记不重复的位置，往前填充
//时间O(N)，空间O(1)
class RemoveDuplicates {
public:
	static int remove(vector<int>& arr) {
		int ret = 1;
		for (int i = 1; i < arr.size(); ++i)
			if (arr[i] != arr[i - 1])
				arr[ret++] = arr[i];

		return ret;
	}
};

//例：给定排序数组，求一个新数组，有序且各元素为给定数组的平方
//分析，先遍历一遍找到正负分界点，然后两个点依次比较大小并向头尾移动
class SortedArraySquares {
public:
	static vector<int> makeSquares(const vector<int>& arr) {
#if 0
		vector<int> squares;
		int p1 = 0, p2 = 0;
		while (arr[p1] < 0)
			++p1;
		p2 = p1 - 1;
		while (p2 >= 0 && p1 < arr.size())
		{
			if ((arr[p1] * arr[p1]) > (arr[p2] * arr[p2]))
			{
				squares.push_back(arr[p2] * arr[p2]);
				--p2;
			}
			else
			{
				squares.push_back(arr[p1] * arr[p1]);
				++p1;
			}
		}
		while (p2 >= 0)
		{
			squares.push_back(arr[p2] * arr[p2]);
			--p2;
		}
		while (p1 < arr.size())
		{
			squares.push_back(arr[p1] * arr[p1]);
			++p1;
		}

		return squares;
#endif
		//更简单的做法
		//从两边开始，由于是平方，所以无论正负，两边的最大，还可以避免前后长度不同的处理
		int n = arr.size();
		vector<int> ret(n);
		int p1 = 0, p2 = n - 1, max_square = n - 1;
		while (p1 <= p2)
		{
			if (arr[p1] * arr[p1] < arr[p2] * arr[p2])
			{
				ret[max_square] = arr[p2] * arr[p2];
				--max_square; --p2;
			}
			else
			{
				ret[max_square] = arr[p1] * arr[p1];
				--max_square; ++p1;
			}
		}

		return ret;
	}
};

//例：给定未排序数组，找出所有和为0的唯一三元组
//分析，与力扣三数之和差不多，可以分解为两次两数之和
//更好的方法是，先排序，然后选用三点法
//时间复杂度 排序快排N*logN 两层for循环 加起来 O(N*logN+N*N)
class TripletSumToZero {
public:
	static vector<vector<int>> searchTriplets(vector<int>& arr) {
		vector<vector<int>> triplets;
		sort(arr.begin(), arr.end());
		for (int i = 0; i < arr.size() - 2; ++i)
		{
			if (i > 0 && arr[i] == arr[i - 1]) continue;//去重左边
			for (int p1 = i + 1, p2 = arr.size() - 1; p1 < p2;)
			{
				int sum = arr[i] + arr[p1] + arr[p2];
				if (sum == 0)
				{
					triplets.push_back({ arr[i],arr[p1],arr[p2] });
					++p1; --p2;
					//去重右边
					while (p2 > p1 && arr[p2] == arr[p2 + 1]) --p2;
				}
				else if (sum < 0)
					++p1;
				else
					--p2;
			}
		}
		return triplets;
	}
};

//例：给定未排序数组和一个目标数，找出最接近目标数的三元组的和
//分析，类似题目，每次移动计算一次三元组和，并记录与目标值最接近的情况，若相同则返回和最小的
class TripletSumCloseToTarget {
public:
	static int searchTriplet(vector<int>& arr, int targetSum) {
		sort(arr.begin(), arr.end());
		int min_diff = INT_MAX;//记录最小差距
		for (int i = 0; i < arr.size() - 2; ++i)
		{
			for (int p1 = i + 1, p2 = arr.size() - 1; p1 < p2;)
			{
				int diff = targetSum - arr[i] - arr[p1] - arr[p2];
				if (diff == 0) return targetSum;//找到一样的，则直接返回
				if (abs(diff) < abs(min_diff) || (abs(diff) == abs(min_diff) && diff > min_diff/* 差异越大，和越小 */))
					min_diff = diff;
				if (diff > 0)
					++p1;
				else
					--p2;
			}
		}
		return targetSum - min_diff;
	}
};

//例：给定未排序数组和目标值，找出所有小于目标值的三元组
class TripletWithSmallerSum {
public:
	static vector<vector<int>> searchTriplets(vector<int>& arr, int target) {
		sort(arr.begin(), arr.end());
		vector<vector<int>> ret;
		for (int i = 0; i < arr.size() - 2; ++i)
		{
			for (int p1 = i + 1, p2 = arr.size() - 1; p1 < p2;)
			{
				int sum = arr[p1] + arr[p2] + arr[i];
				if (sum < target)
				{
					//p2左边所有情况都满足
					int tmp = p2;
					while (tmp > p1)
						ret.push_back({ arr[i],arr[p1],arr[tmp--] });
					++p1;
				}
				else
					--p2;
			}
		}
		return ret;
	}
};

//例：给定数组和目标数，求所有乘积小于目标数的连续子数组
//分析，连续子数组，是滑动窗口
class SubarrayProductLessThanK {
public:
	static vector<vector<int>> findSubarrays(const vector<int>& arr, int target) {
		vector<vector<int>> result;
		int window_start = 0, product = 1;
		for (int window_end = 0; window_end < arr.size(); ++window_end)
		{
			product *= arr[window_end];
			while (product >= target && window_start < arr.size())
				product /= arr[window_start++];
			//每次把窗口所有子集放入
			//vector<int> tmp;
			//for (int i = window_start; i <= window_end; ++i)
			//{
			//	tmp.push_back(arr[i]);
			//	result.push_back(tmp);
			//}
			//为了避免重复，应从右侧开始，扩展子集******
			deque<int> tmp;
			for (int i = window_end; i >= window_start; --i)
			{
				tmp.push_front(arr[i]);
				result.push_back(vector<int>(tmp.begin(), tmp.end()));
			}
		}
		return result;
	}
};

//例：荷兰国旗问题，给定包含0，1，2的数组（三种不同元素），就地排序
//分析，只有三种元素，应该不需要适用性广的快排O(nlogn)
//只需要两点法一次遍历，时间O(N)，空间O(1)
class DutchFlag {
public:
	static void sort(vector<int>& arr) {
		int p1 = 0, p2 = arr.size() - 1;
		//两点，遍历数组，0从头指针开始放，2从尾指针开始放，1自动处在中间
		for (int i = 0; i <= p2/* p2之后的都放好了 */;)
		{
			if (arr[i] == 0)
			{
				swap(arr[i], arr[p1]);
				++i; ++p1;
			}
			else if (arr[i] == 2)
			{
				swap(arr[i], arr[p2]);
				//交换后i位置可能还是2，而开头换0可以++i是因为i前面的都已经是换好的
				--p2;
			}
			else
				++i;
		}
	}
};

//
//总结
// 对于有序数组（或链表），可以使用两个指针指向头尾
// 当需要特定值，两指针计算后小于特定值，说明需要更大的值，则后移头指针
// 反之，需要更小的值，则前移尾指针
//

//练习：四数之和
//分析，分解成三数之和与两数之和
//时间复杂度O(N*NlogN+N*N*N)，空间复杂度O(1)，若排序是归并，则是O(N)
class QuadrupleSumToTarget {
public:
	static vector<vector<int>> searchQuadruplets(vector<int>& arr, int target) {
		vector<vector<int>> quadruplets;
		sort(arr.begin(), arr.end());
		for (int i = 0; i < arr.size() - 3; ++i)
		{
			if (i > 0 && arr[i] == arr[i - 1]) continue;//跳过左边重复情况
			for (int j = i + 1; j < arr.size() - 2; ++j)
			{
				if (j > i + 1 && arr[j] == arr[j - 1]) continue;//同理外层跳过左边重复情况
				for (int p1 = j + 1, p2 = arr.size() - 1; p1 < p2;)
				{
					int sum = arr[i] + arr[j] + arr[p1] + arr[p2];
					if (sum == target)
					{
						quadruplets.push_back({ arr[i],arr[j],arr[p1],arr[p2] });
						++p1; --p2;
						while (p2 > p1 && arr[p2] + arr[p2 + 1]) --p2;//跳过右侧重复情况
					}
					else if (sum < target)
						++p1;
					else
						--p2;
				}
			}
		}
		return quadruplets;
	}
};

//练习：给定两个包含退格的字符串（字符#标识）比较两个字符串是否相同
//分析，两点法没想到太好的解法，可以用队列
class BackspaceCompare {
public:
	static bool compare(const string& str1, const string& str2) {
		deque<char> deq;
		string s1, s2;
		for (int i = 0; i < str1.size(); ++i)
		{
			if (str1[i] == '#')
				deq.pop_back();
			else
				deq.push_back(str1[i]);
		}

		while (!deq.empty())
		{
			s1 += deq.front();
			deq.pop_front();
		}
		for (int i = 0; i < str2.size(); ++i)
		{
			if (str2[i] == '#')
				deq.pop_back();
			else
				deq.push_back(str2[i]);
		}

		while (!deq.empty())
		{
			s2 += deq.front();
			deq.pop_front();
		}
		return s1 == s2;

		//还是比较麻烦的，四次循环，额外空间也很大
		//使用两点法，不用真的对比字符串，而是每个字符验证
		//由于是退格，可以倒着遍历，遇到退格符则是跳过
		int p1 = str1.size() - 1, p2 = str2.size() - 1;
		while (p1 >= 0 && p2 >= 0)
		{

			if (str1[p1] == '#')
			{
				int nums = 0;
				while (str1[p1] == '#')
				{
					--p1;
					++nums;
				}
				p1 -= nums;

			}
			if (str2[p2] == '#')
			{
				int nums = 0;
				while (str2[p2] == '#')
				{
					--p2;
					++nums;
				}
				p2 -= nums;
			}
			if (str1[p1] != str2[p2]) return false;
			--p1; --p2;
		}
		return p1 == p2;
	}
};

//练习：给定数组，找出所有元素都需要排序的最小子数组
//分析
class ShortestWindowSort {
public:
	static int sort(const vector<int>& arr) {
		int low = 0, high = arr.size() - 1;
		// find the first number out of sorting order from the beginning
		while (low < arr.size() - 1 && arr[low] <= arr[low + 1]) {
			low++;
		}

		if (low == arr.size() - 1) {  // if the array is sorted
			return 0;
		}

		// find the first number out of sorting order from the end
		while (high > 0 && arr[high] >= arr[high - 1]) {
			high--;
		}

		// find the maximum and minimum of the subarray
		int subarrayMax = numeric_limits<int>::min(), subarrayMin = numeric_limits<int>::max();
		for (int k = low; k <= high; k++) {
			subarrayMax = max(subarrayMax, arr[k]);
			subarrayMin = min(subarrayMin, arr[k]);
		}

		// extend the subarray to include any number which is bigger than the minimum of the subarray
		while (low > 0 && arr[low - 1] > subarrayMin) {
			low--;
		}
		// extend the subarray to include any number which is smaller than the maximum of the subarray
		while (high < arr.size() - 1 && arr[high + 1] < subarrayMax) {
			high++;
		}

		return high - low + 1;
	}
};

//================================================================

//
//快慢指针
//

//例：环链表相关
class ListNode {
public:
	int value = 0;
	ListNode* next;

	ListNode(int value) {
		this->value = value;
		next = nullptr;
	}
};
class LinkedListCycle {
public:
	//检测环
	//时间复杂度O(N)，空间O(1)
	static bool hasCycle(ListNode* head) {
		if (head == nullptr) return false;
		ListNode* slow = head, * fast = head;
		while (fast != nullptr && fast->next != nullptr)
		{
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast) return true;
		}
		return false;
	}

	//求环长
	static int cycleLen(ListNode* head) {
		if (head == nullptr) return -1;
		ListNode* slow = head, * fast = head;
		int ret = 0;
		while (fast != nullptr && fast->next != nullptr)
		{
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast)
			{
				//找到环之后，一次走一步并计数，直到再次找到
				do
				{
					fast = fast->next;
					++ret;
				} while (slow != fast);
				break;
			}
		}
		return ret;
	}

	//求环头
	static ListNode* findCycleStart(ListNode* head) {
		ListNode* slow = head, * fast = head;
		int cycle_len = 0;
		while (fast != nullptr && fast->next != nullptr)
		{
			fast = fast->next->next;
			slow = slow->next;
			if (slow == fast)//检测环
			{
				do
				{
					fast = fast->next;
					++cycle_len;
				} while (fast != slow);
				break;//计算环长
			}
		}
		if (cycle_len != 0)
		{
			//两个指针归位
			slow = fast = head;
			//快指针先走环长步数
			while (cycle_len > 0)
			{
				fast = fast->next;
				--cycle_len;
			}
			//之后两个指针一起走，第一次相遇的时候就是环头
			while (slow != fast)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		return slow;
	}
};

//例：求快乐数字
//快乐数字的定义是，一个数字反复计算每一位的平方和，最终回回归到1
//不是快乐数字的平方和计算中，会出现循环
class HappyNumber {
public:
	static bool find(int num) {
		//方法1，使用额外空间记录
		unordered_set<int> memo;//记录出现过的平方和
		while (true)
		{
			int mod = 0, sum = 0;
			//计算平方和
			while (num > 0)
			{
				mod = num % 10;
				sum += mod * mod;
				num /= 10;
			}
			//出现过，则有循环，返回false
			if (memo.find(sum) != memo.end())
				break;
			//平方和为1，满足条件，返回true
			if (sum == 1)
				return true;
			//并记录本次计算结果并准备下一次计算
			memo.insert(sum);
			num = sum;
		}
		return false;

		//方法2
		//使用本章内容的快慢指针思想，可以不使用额外空间
		int slow = 0, fast = 0;
		do
		{
			//每次循环，慢的计算一次，快的计算两次，用调用次数来表示步数，一开始想不到
			//不管是归为1还是出现循环，最终他们会相等
			slow = square_sum(slow);
			fast = square_sum(square_sum(fast));
		} while (slow != fast);
		return slow == 1;//看相当时结果是否为1

		//时间复杂度应该相同，就是快慢指针节约了空间
		//其中，数字在1000以内，最多计算1001次，N+1
		//但N足够大时，根据科学计算，M位，也就是Log(N+1)位，最多出现的平方和为9^2M
		//也就是 O(81*log(N+1)) 可以看作时间复杂度 O(LogN)
	}
	//封装计算平方和函数
	static int square_sum(int num)
	{
		int sum = 0, mod = 0;
		while (num > 0)
		{
			mod = num % 10;
			sum += mod * mod;
			num /= 10;
		}
		return sum;
	}
};

//例：求链表中间元素
class MiddleOfLinkedList {
public:
	static ListNode* findMiddle(ListNode* head) {
		ListNode* slow = head, * fast = head;
		while (fast != nullptr && fast->next != nullptr)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		return slow;
	}
};

//
//总结
// 两个指针以不同速度在数组/链表中移动
// 最经典的问题是处理循环
// 也可用于产生距离，找特定位置元素
// 
// 快慢指针还可以变种
// 用调用次数代替步数概念，例如求平方和例子
//

//练习：给定单链表，检查链表内容是否为回文
class PalindromicLinkedList {
public:
	static bool isPalindrome(ListNode* head) {
		if (head == nullptr || head->next == nullptr) return true;
		ListNode* tmp = head;
		//定义一个反转链表，然后对比是否相同
		ListNode* l2 = new ListNode(tmp->value);
		do
		{
			tmp = tmp->next;
			ListNode* new_node = new ListNode(tmp->value);
			new_node->next = l2;
			l2 = new_node;
		} while (tmp->next != nullptr);
		ListNode* p1 = head, * p2 = l2;
		while (p1 != nullptr && p2 != nullptr)
		{
			if (p1->value != p2->value) return false;
			p1 = p1->next;
			p2 = p2->next;
		}
		return p1 == p2;

		//使用快慢指针，先找中点，然后原地反转后半部分
		//由于要求原链不变，检查完回文再恢复
		if (head == nullptr || head->next == nullptr) return true;
		ListNode* slow = head, * fast = head;
		while (fast != nullptr && fast->next != nullptr)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		//走完后，slow为中间，原地反转
		ListNode* new_head = reverse(slow);
		//反转后new_head为新头
		//验证是否是回文
		ListNode* p1 = head, * p2 = new_head;
		while (p1 != nullptr && p2 != nullptr)
		{
			if (p1->value != p2->value)
				break;
			p1 = p1->next;
			p2 = p2->next;
		}
		//根据new_head反转一次链表，恢复状态
		reverse(new_head);
		//返回是否为回文
		if (p1 == nullptr || p2 == nullptr)
			return true;
		return false;
	}
	static ListNode* reverse(ListNode* head)
	{
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

//练习：给定单链表，将后半部分节点已相反顺序交替插入前半部分，要求原地操作
//分析，先找中点，再把后续每个节点插入到前面，由于是相反顺序插入，则反转后半部分再从头依次插入
class RearrangeList {
public:
	static void reorder(ListNode* head) {
		if (head == nullptr || head->next == nullptr) return;
		ListNode* slow = head, * fast = head;
		while (fast != nullptr && fast->next != nullptr)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		//根据中点slow反转后半部分
		ListNode* prev = nullptr, * tmp = nullptr;
		while (slow != nullptr)
		{
			tmp = slow->next;
			slow->next = prev;
			prev = slow;
			slow = tmp;
		}
		//从头开始，交替拼接
		ListNode* p1 = head, * p2 = prev;
		while (p1 != nullptr && p2 != nullptr)
		{
			tmp = p2->next;
			p2->next = p1->next;
			p1->next = p2;
			p1 = p2->next;
			p2 = tmp;
		}
		if (p1 != nullptr)
			p1->next = nullptr;
	}
};

//练习：一个包含正负数的数组，索引的每个值都代表下一次行进的步数
//检查是否含有环（单项，也就是不能同时有正负）
//分析，快慢指针找环，找到环之后遍历一遍环，看正负数个数
class CircularArrayLoop {
public:
	static bool loopExists(const vector<int>& arr) {
		int n = arr.size(), p1 = 0, p2 = 0, n1 = 0, n2 = 0, times = 2 * n;
		if (n == 0 || n == 1) return false;
		while (times > 0)
		{
			p1 = (p1 + arr[p1]) % n;
			p2 = (p2 + arr[p2]) % n;
			p2 = (p2 + arr[p2]) % n;
			if (p1 == p2) break;
			times--;
		}
		if (p1 != p2) return false;
		do
		{
			if (arr[p2] > 0)
				++n1;
			else
				++n2;
			p2 = (p2 + arr[p2]) % n;
		} while (p1 != p2);
		if (n1 != 0 && n2 != 0) return false;
		return true;

		//答案思路，从数组每个索引开始找循环
		//循环中，如果改变了方向，则不符合
		for (int i = 0; i < arr.size(); i++) {
			bool isForward = arr[i] >= 0;  // if we are moving forward or not
			int slow = i, fast = i;

			// if slow or fast becomes '-1' this means we can't find cycle for this number
			do {
				slow = findNextIndex(arr, isForward, slow);  // move one step for slow pointer
				fast = findNextIndex(arr, isForward, fast);  // move one step for fast pointer
				if (fast != -1) {
					fast = findNextIndex(arr, isForward, fast);  // move another step for fast pointer
				}
			} while (slow != -1 && fast != -1 && slow != fast);

			if (slow != -1 && slow == fast) {
				return true;
			}
		}

		return false;
	}
	static int findNextIndex(const vector<int>& arr, bool isForward, int currentIndex) {
		bool direction = arr[currentIndex] >= 0;
		if (isForward != direction) {
			return -1;  // change in direction, return -1
		}

		int nextIndex = (currentIndex + arr[currentIndex]) % (int)arr.size();
		if (nextIndex < 0)
			nextIndex += arr.size(); // wrap around for negative numbers

		  // one element cycle, return -1
		if (nextIndex == currentIndex) {
			nextIndex = -1;
		}

		return nextIndex;
	}
};

//================================================================

//都是采用两个标记来辅助的方法，放在一起

int main()
{
	clock_t start = clock();
	test_AverageOfSubarrayOfSizeK();
	clock_t finish = clock();
	cout << "func call times cost: " << finish - start << " ms" << endl;
}
