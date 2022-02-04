#pragma once

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

//LeetCode

// Reverse String����ת�ַ�����/problems/reverse-string/
void reverseString(vector<char>& s) {
	if (s.size() == 0 || s.size() == 1) return;
	int start = 0, end = s.size() - 1;
	while (start < end)
	{
		swap(s[start], s[end]);
		++start; --end;
	}
}

// Reverse Words in a String����ת�ַ�����ĵ��ʣ�/problems/reverse-words-in-a-string/
string reverseWords(string s) {
	string ret = "";
	s = ' ' + s;//ǰ���һ���ո񷽱��ж�
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

// String to Integer(atoi)���ַ���ת������(atoi)��/problems/string-to-integer-atoi/
int myAtoi(string s) {
	//�������
	if (s.empty()) return 0;
	//������������
	int begin = 0, sign = 1, ret = 0;
	int n = s.size();
	//ȥ�ո񣬼�����
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
		if ((ret > INT_MAX / 10) || (ret == INT_MAX / 10 && num > INT_MAX % 10))//����int��Χ
			return sign == 1 ? INT_MAX : INT_MIN;
		ret = 10 * ret + num;//����ǰһ�ν��*10
	}

	return sign == 1 ? ret : -ret;

}