#pragma once

#include "public_header.hpp"
#include <algorithm>
#include <vector>
#include <stack>
#include <unordered_map>
#include <string>
#include <queue>
using namespace std;

//递归

//n阶乘
int fac(int n)
{
	if (n < 0)
		return -1;
	if (n == 0 || n == 1)
		return 1;

	return n * fac(n - 1);
}

//斐波那契
int fib(int n)
{
	if (n == 1 || n == 2)
		return 1;
	return fib(n - 1) + fib(n - 2);
}

//全排列
void perm(int* arr, int k, size_t m)
{
	if (k == m)
	{
		for (int i = 0; i < m; ++i)
			std::cout << arr[i] << " ";
		std::cout << std::endl;
		return;
	}

	for (int i = k; i < m; ++i)
	{
		std::swap(arr[k], arr[i]);
		perm(arr, k + 1, m);
		std::swap(arr[k], arr[i]);
	}

}

//爬楼梯 /problems/climbing-stairs/
class Solution {
public:
	int count = 0;
	int climbStairs(int n) {
		//抽象为斐波那契
		vector<int>dp(n + 1, 0);
		dp[0] = 1;
		dp[1] = 1;
		for (int i = 2; i <= n; ++i)
			dp[i] = dp[i - 1] + dp[i - 2];
		return dp[n];

		//简化空间为O(1)
		int two = 1, one = 1;
		for (int i = n - 2; i >= 0; --i)
		{
			int t = one;
			one = one + two;
			two = t;
		}
		return one;

	}
};


// 栈

// Valid Parentheses（有效的括号）/problems/valid-parentheses/
bool isValid(string s) {
	stack<char> st;
	//设定上，只含括号，不考虑其他字符
	for (int i = 0; i < s.size(); ++i)
	{
		char temp = s[i];
		switch (temp)
		{
		case '(':
		case '[':
		case '{':
		{
			st.push(temp);
			break;
		}
		case ')':
		{
			if (st.empty())
				return false;
			if (st.top() != '(')
				return false;
			else
				st.pop();
			break;
		}
		case ']':
		{
			if (st.empty())
				return false;
			if (st.top() != '[')
				return false;
			else
				st.pop();
			break;
		}
		case '}':
		{
			if (st.empty())
				return false;
			if (st.top() != '{')
				return false;
			else
				st.pop();
			break;
		}
		}

	}
	return st.empty();

	//借助一个字典简化逻辑判断
	stack<char> st;
	unordered_map<char, char> m{ { '[',']' }, { '(',')' }, { '{','}' } };
	for (auto c : s)
	{
		if (m.find(c) != m.end())
			st.push(c);
		else
		{
			if (st.empty())
				return false;
			if (c != m[st.top()])
				return false;
			st.pop();
		}
	}
	return st.empty();
}

// Longest Valid Parentheses（最长有效的括号）/problems/longest-valid-parentheses/
int longestValidParentheses(string s) {
	//用栈
	int max = 0;
	stack<int> st;//存放字符索引
	st.push(-1);
	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] == '(')
			st.push(i);//记录左括号所在索引
		else
		{
			if (!st.empty())
				st.pop();
			if (!st.empty())
				max = std::max(max, i - st.top());//st.top为当前非有效的最后一个括号位置
			else
				st.push(i);//为空还有右括号，记录为最后一个非有效括号位置
		}
	}
	return max;


	//怪聪明的解法
	int left = 0, right = 0, max = 0;
	for (auto c : s)
	{
		if (c == '(')
			++left;
		else
			++right;
		if (left == right)
			max = std::max(max, left * 2);
		else if (right > left)
			left = right = 0;
	}
	left = right = 0;
	for (int i = s.size() - 1; i >= 0; --i)
	{
		if (s[i] == '(')
			++left;
		else
			++right;
		if (left == right)
			max = std::max(max, left * 2);
		else if (left > right)
			left = right = 0;
	}

	return max;
}

// Evaluate Reverse Polish Notatio（逆波兰表达式求值）/problems/evaluate-reverse-polish-notation/
int evalRPN(vector<string>& tokens) {
	stack<int>s;
	for (int i = 0; i < tokens.size(); i++) {
		if (tokens[i] == "+") {
			int a = s.top();
			s.pop();
			int b = s.top();
			s.pop();
			s.push(a + b);
		}
		else if (tokens[i] == "-") {
			int a = s.top();
			s.pop();
			int b = s.top();
			s.pop();
			s.push(b - a);
		}
		else if (tokens[i] == "*") {
			int a = s.top();
			s.pop();
			int b = s.top();
			s.pop();
			s.push(a * b);
		}
		else if (tokens[i] == "/") {
			int a = s.top();
			s.pop();
			int b = s.top();
			s.pop();
			s.push(b / a);
		}
		else {
			s.push(stoi(tokens[i]));
		}
	}
	return s.top();
}


// 队列

// Design Circular Deque（设计一个双端队列）/problems/design-circular-deque/
class MyCircularDeque {
public:
	MyCircularDeque(int k)
		:size(k)
	{
		arr = new int[size];
		if (arr == nullptr)
			throw "ctor failed";
	}
	~MyCircularDeque()
	{
		if (arr != nullptr)
			delete[] arr;
		arr = nullptr;
	}

	bool insertFront(int value) {
		if (head == -1)
		{
			arr[0] = value;
			head = tail = 0;
			return true;
		}
		if ((head - 1 + size) % size == tail)
			return false;
		head = (head - 1 + size) % size;
		arr[head] = value;
		return true;
	}

	bool insertLast(int value) {
		if (tail == -1)
		{
			arr[0] = value;
			head = tail = 0;
			return true;
		}
		if ((tail + 1) % size == head)
			return false;
		tail = (tail + 1) % size;
		arr[tail] = value;
		return true;
	}

	bool deleteFront() {
		if (head == -1)
			return false;
		if (head == tail)//只剩一个元素
		{
			head = tail = -1;
			return true;
		}
		head = (head + 1) % size;
		return true;
	}

	bool deleteLast() {
		if (head == -1)
			return false;
		if (head == tail)//只剩一个元素
		{
			head = tail = -1;
			return true;
		}
		tail = (tail - 1 + size) % size;
		return true;
	}

	int getFront() {
		if (head == -1)
			return -1;
		return arr[head];
	}

	int getRear() {
		if (head == -1)
			return -1;
		return arr[tail];
	}

	bool isEmpty() {
		return head == -1;
	}

	bool isFull() {
		if (head == -1)
			return false;
		return ((tail + 1) % size) == head;
	}

private:
	int head = -1;
	int tail = -1;
	int size = 0;
	int* arr = nullptr;
};

// Sliding Window Maximum（滑动窗口最大值）/problems/sliding-window-maximum/
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
	//暴力解，leetcode超时
	if (nums.size() == 0) return { -1 };
	if (nums.size() == 1) return nums;
	if (k >= nums.size())
	{
		int max = INT_MIN;
		for (auto i : nums)
			if (i > max)
				max = i;
		return { max };
	}
	vector<int> ret;
	for (int i = 0; i <= nums.size() - k; ++i)
	{
		int max = INT_MIN;
		for (int j = 0; j < k; ++j)
			if (nums[i + j] > max)
				max = nums[i + j];
		ret.push_back(max);
	}
	return ret;

	//最大堆
	vector<int>v;
	priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int,int>>>pq;

	for (int i = 0; i < k; i++)
	{
		pq.push({ nums[i],i });
	}
	v.push_back(pq.top().first);
	for (int i = k; i < nums.size(); i++)
	{
		pq.push({ nums[i],i });

		while (!pq.empty() and pq.top().second <= i - k)
		{
			pq.pop();
		}
		v.push_back(pq.top().first);

	}
	return v;

	//普通队列
	deque<pair<int, int>> dq;
	vector<int> ret;

	for (int i = 0; i < nums.size(); ++i)
	{
		//不为空且窗口已满，先弹出前一个数字
		if (!dq.empty() && dq.front().first <= i - k)//i - k为窗口范围，超过队中第一个要出队
			dq.pop_front();
		//进队时只保留比入队元素更大的
		while (!dq.empty() && nums[i] > dq.back().second)
			dq.pop_back();
		//入队
		dq.push_back({ i,nums[i] });
		if (i >= k - 1)//从第3个元素位置开始记录
			ret.push_back(dq.front().second);
	}
	return ret;
}