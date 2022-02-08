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
//两点法
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

//例：

int main()
{
	clock_t start = clock();
	test_AverageOfSubarrayOfSizeK();
	clock_t finish = clock();
	cout << "func call times cost: " << finish - start << " ms" << endl;
}
