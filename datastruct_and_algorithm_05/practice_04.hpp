#pragma once

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

//LeetCode

// Reverse String（反转字符串）/problems/reverse-string/
void reverseString(vector<char>& s) {
	if (s.size() == 0 || s.size() == 1) return;
	int start = 0, end = s.size() - 1;
	while (start < end)
	{
		swap(s[start], s[end]);
		++start; --end;
	}
}

// Reverse Words in a String（翻转字符串里的单词）/problems/reverse-words-in-a-string/
string reverseWords(string s) {
	string ret = "";
	s = ' ' + s;//前面加一个空格方便判断
	int start = s.size() - 1, end = s.size() - 1;

	while (start >= 0)
	{
		if (s[start] == ' ')
		{
			if (start < end)
			{
				if (!ret.empty())
					ret += ' ';
				ret += s.substr(start + 1, end - start);
				--start;
				end = start;
			}
			else
			{
				--end;
				start = end;
			}
		}
		else
		{
			--start;
		}
	}

	return ret;

}

// String to Integer(atoi)（字符串转换整数(atoi)）/problems/string-to-integer-atoi/
int myAtoi(string s) {
	//参数检查
	if (s.empty()) return 0;
	//声明辅助变量
	int begin = 0, sign = 1, ret = 0;
	int n = s.size();
	//去空格，检查符号
	while (begin < n && s[begin] == ' ')
		++begin;
	if (begin < n && s[begin] == '+')
		++begin;
	else if (begin < n && s[begin] == '-')
	{
		sign = -1;
		++begin;
	}

	while (begin < n&& isdigit(s[begin]))
	{
		int num = s[begin++] - '0';
		if ((ret > INT_MAX / 10) || (ret == INT_MAX / 10 && num > INT_MAX % 10))//超过int范围
			return sign == 1 ? INT_MAX : INT_MIN;
		ret = 10 * ret + num;//加上前一次结果*10
	}

	return sign == 1 ? ret : -ret;

}