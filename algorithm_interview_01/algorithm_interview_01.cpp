// algorithm_interview_01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//
//极客专栏——算法面试通关
//

//
//让时间、空间复杂度的判断成为习惯
//

//
//怎么在leetcode刷题
// 
//切题四件套
// 数据范围，特殊值、临界值等测试用例覆盖
// 思考包括暴力解法在内的所有解法，对比时间复杂度
// 实际把代码敲出来
// 看其他人的讨论和解法
//

//
//数组&链表
// 
//常见题目
// 206.反转链表
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		if (head == nullptr || head->next == nullptr) return head;

		ListNode* prev = nullptr, *next = nullptr;
		while (head)
		{
			next = head->next;
			head->next = prev;
			prev = head;
			head = next;
		}
		return prev;
	}
};
// 24. Swap Nodes in Pairs
class Solution {
public:
	ListNode* swapPairs(ListNode* head) {
		if (head == nullptr || head->next == nullptr) return head;


	}
};
// 
//

//视频课，不方便看，先暂停了

int main()
{
	return 0;
}
