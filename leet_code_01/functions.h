#pragma once
#include <vector>
#include <unordered_map>
/**
 * 两数之和：
 * 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 的那 两个 整数，并返回它们的数组下标。
 * 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。
 * 你可以按任意顺序返回答案。
 */
inline
std::vector<int>
twoSum(std::vector<int>& nums, int target) {
	std::vector<int> ret;

	//暴力解法，枚举；时间复杂度N^2，空间复杂度1

	//for (auto it_fir = nums.begin(); it_fir != nums.end(); it_fir++)
	//{
	//	for (auto it_sec = it_fir + 1; it_sec != nums.end(); it_sec++)
	//	{
	//		if (*it_fir + *it_sec == target)
	//		{
	//			ret.push_back(it_fir - nums.begin());
	//			ret.push_back(it_sec - nums.begin());
	//			break;
	//		}
	//	}
	//}

	//以上耗时136ms，用迭代器有点夸张了
	//之前用java写，耗时还没有这么高，不过c++内存占的少
	//直接当成数组来解更快

	//for (int i = 0; i < nums.size(); i++) {
	//	for (int j = i + 1; j < nums.size(); j++) {
	//		if (nums[i] + nums[j] == target) {
	//			ret.push_back(i);
	//			ret.push_back(j);
	//			break;
	//		}
	//	}
	//}

	//哈希表法，遍历一次，遍历中对每个元素寻找target-x，找到则返回两个索引，否则存入哈希表
	//时间复杂度N，空间复杂度N
	std::unordered_map<int, int> hashtable;
	for (int i = 0; i < nums.size(); i++)
	{
		auto it = hashtable.find(target - nums[i]);
		if (it != hashtable.end()) {
			ret.push_back(i);
			ret.push_back(it->second);
			break;
		}
		hashtable[nums[i]] = i;
	}

	return ret;
}

/**
 * 两数相加
 * 给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
 * 请你将两个数相加，并以相同形式返回一个表示和的链表。
 * 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 */
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};
ListNode* dfs(ListNode* l, ListNode* r, int i);
inline
ListNode* 
addTwoNumbers(ListNode* l1, ListNode* l2) {
	//官方解法
	//ListNode* head = nullptr, * tail = nullptr;
	//int carry = 0;//进位
	//while (l1 || l2) { //对位都为空则结束
	//	int n1 = l1 ? l1->val : 0;
	//	int n2 = l2 ? l2->val : 0;
	//	int sum = n1 + n2 + carry;
	//	if (!head) {
	//		head = tail = new ListNode(sum % 10);
	//	}
	//	else {
	//		tail->next = new ListNode(sum % 10);
	//		tail = tail->next;
	//	}
	//	carry = sum / 10;
	//	if (l1) {
	//		l1 = l1->next;
	//	}
	//	if (l2) {
	//		l2 = l2->next;
	//	}
	//}
	//if (carry > 0) { //最后若还有进位，链表增加一个节点
	//	tail->next = new ListNode(carry);
	//}
	//return head;

	//简单写法
	ListNode preHead(0), * p = &preHead;
	int extra = 0;
	while (l1 || l2 || extra) {
		if (l1) extra += l1->val, l1 = l1->next;
		if (l2) extra += l2->val, l2 = l2->next;
		p = p->next = new ListNode(extra % 10);
		extra /= 10;
	}
	return preHead.next;

	//递归写法
	return dfs(l1, l2, 0);
}
ListNode* 
dfs(ListNode* l, ListNode* r, int i) {
	if (!l && !r && !i) return nullptr;
	int sum = (l ? l->val : 0) + (r ? r->val : 0) + i;
	ListNode* node = new ListNode(sum % 10);
	node->next = dfs(l ? l->next : nullptr, r ? r->next : nullptr, sum / 10);
	return node;
}