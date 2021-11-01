// explore_learn_linked_list.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//
//leetcode-explore-learn-linked-list
//

using namespace std;

//Introduction
// 
//线性数据结构，内存不一定连续，每个节点通过指针或引用连接起来
// 
//分为单链表和双链表
//

//Singly Linked List
// 
//基本节点结构
//
//Definition for singly-linked list.
struct SinglyListNode {
	int val;
	SinglyListNode* next;
	SinglyListNode(int x) : val(x), next(NULL) {}
};
// 
//与数组不同，无法通过索引随机访问，只能从头遍历
//但插入删除操作效率更高
//

//Design Linked List
// 
class MyLinkedlist {
public:
	/** Initialize your data structure here. */
	MyLinkedlist() :size(0), head(nullptr) {

	}

	/** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
	int get(int index) {
		if (index > size - 1 || index < 0 || head == nullptr) return -1;
		SinglyListNode* temp = head;
		for (int i = 0; i < index; ++i)
			temp = temp->next;
		return temp->val;
	}

	/** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
	void addAtHead(int val) {
		SinglyListNode* new_node = new SinglyListNode(val);
		if (head != nullptr)
			new_node->next = head;
		head = new_node;
		++size;
	}

	/** Append a node of value val to the last element of the linked list. */
	void addAtTail(int val) {
		if (size == 0) return addAtHead(val);
		SinglyListNode* temp = head;
		while (temp->next != nullptr)
			temp = temp->next;
		SinglyListNode* new_node = new SinglyListNode(val);
		temp->next = new_node;
		++size;
	}

	/** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
	void addAtIndex(int index, int val) {
		if (index < 0 || index > size) return;
		if (index == 0) return addAtHead(val);
		if (index == size) return addAtTail(val);
		SinglyListNode* temp = head;
		for (int i = 0; i < index - 1; ++i)
			temp = temp->next;
		SinglyListNode* new_node = new SinglyListNode(val);
		new_node->next = temp->next;
		temp->next = new_node;
		++size;
	}

	void deleteAtHead() {
		SinglyListNode* temp = head->next;
		delete head;
		head = temp;
		--size;
	}

	/** Delete the index-th node in the linked list, if the index is valid. */
	void deleteAtIndex(int index) {
		if (index < 0 || index > size - 1) return;
		if (index == 0) return deleteAtHead();
		SinglyListNode* temp_pre = head, * temp = head->next;
		for (int i = 1; i < index; ++i) {
			temp_pre = temp_pre->next;
			temp = temp_pre->next;
		}
		temp_pre->next = temp->next;
		delete temp;
		--size;
	}
private:
	int size;
	SinglyListNode* head;//还可以使用两个指针分别记录头和尾，在尾操作时会快很多
};

//Two-Pointer in Linked List
// 
//检测链表是否有环，可以使用此技术
// 定义两个指针，移动速度不同
// 如果有环，快的会追上慢的
// 
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};
class Solution2_1 {
public:
	bool hasCycle(ListNode* head) {
		ListNode* temp1 = head;
		if (temp1 == nullptr) return false;
		ListNode* temp2 = head->next;
		if (temp2 == nullptr) return false;
		while ( /* temp1 != nullptr && */ temp2 != nullptr && temp2->next != nullptr) { //快的不为空就可以保证慢的不为空了，第一个条件可以省略
			if (temp1 == temp2) return true;
			temp1 = temp1->next;
			temp2 = temp2->next->next;
		}
		return false;
	}
};
class Solution2_2 {
public:
	ListNode* detectCycle(ListNode* head) {
		if (head == NULL || head->next == NULL) return NULL;

		ListNode* slow = head;
		ListNode* fast = head;

		while (fast->next != NULL && fast->next->next != NULL)
		{
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast) //直接break在外面写下面的逻辑，可以减少嵌套
			{
				//汇合的话，把快的重新指向头（或者找一个指向头的temp点）；快慢指针汇合点和头同时走会汇合在环开始的点（？）
				fast = head;
				while (slow != fast)
				{
					slow = slow->next;
					fast = fast->next;
				}
				return slow;
			}
		}
		/*

		Explnation:
		Let's say that linked list is of form
		L + circumference

		slowPtr moves L+x and fastPtr moves L+x+circumference

		Since fast ptr moves twice as slowPtr
		2*(L+x) = (L+x)+circumference
		=> L+x = circumference
		=> L = circumference- x

		Now if we set slowPtr to head
		it has to move L steps to point where loop starts and the fastPtr has to move circumference -x steps
		because they both have to move same steps to reach the point where loop starts, we can just move them by one step at a time and compare if they are equal.

		and fastPtr has to move circumference-

		*/
		return NULL;
	}
};
// 
//

//Intersection of Two Linked Lists
// 
//Given the heads of two singly linked-lists headA and headB, return the node at which the two lists intersect.
// If the two linked lists have no intersection at all, return null.
// 
//Example:
//Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
//Output: Intersected at '8'
//Explanation : The intersected node's value is 8 (note that this must not be 0 if the two lists intersect).
//From the head of A, it reads as[4, 1, 8, 4, 5].From the head of B, it reads as[5, 6, 1, 8, 4, 5].
//There are 2 nodes before the intersected node in A; There are 3 nodes before the intersected node in B.
// 
class Solution2_3 {
public:

	int length(ListNode* head) {
		if (head == NULL)
			return 0;
		ListNode* ptr = head;
		int count = 0;
		while (ptr->next != NULL) {
			ptr = ptr->next;
			count++;
		}
		return count;
	}

	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
		int l1 = length(headA);
		int l2 = length(headB);
		int d = 0;
		//先计算两链表的长度
		ListNode* ptr1;
		ListNode* ptr2;

		if (l1 > l2) {
			d = l1 - l2;
			ptr1 = headA;
			ptr2 = headB;
		}
		else {
			d = l2 - l1;
			ptr1 = headB;
			ptr2 = headA;
		}
		//根据两链表长度调整两个对比点
		while (d) {
			ptr1 = ptr1->next;
			if (ptr1 == NULL)
				return NULL;
			d--;
		}
		//调整后两点距离表尾距离相同，只需要同时推进对比即可
		while (ptr1 != NULL && ptr2 != NULL) {
			if (ptr1 == ptr2) {
				return ptr1;
			}

			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}

		return NULL;
	}

};
// 
//

//Remove Nth Node From End of List
// 
class Solution2_4 {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		int position = 1;

		ListNode* start = new ListNode();
		start->next = head;

		ListNode* slow = start;
		ListNode* fast = start;

		while (fast->next != NULL)
		{
			if (position > n)
				slow = slow->next;

			fast = fast->next;
			position++;
		}

		slow->next = slow->next->next;

		return start->next;
	}
};
//
//

//两点法总结
// 
//在使用next节点前，检查节点是否为空
//仔细定义循环条件
//

//Classic Problems
// 
//一些经典问题
//

//Reverse Linked List
// 
//Example:
//Input: head = [1,2,3,4,5]
//Output: [5, 4, 3, 2, 1]
// 
class Solution3_1 {
public:
	ListNode* reverseList(ListNode* head) {
		ListNode* prev = NULL;
		while (head != NULL) {
			ListNode* next = head->next;
			head->next = prev;
			prev = head;//遍历每个节点，把当前节点放到前一个节点的前面去
			head = next;
		}
		return prev;
	}
};
// 
//

//Remove Linked List Elements
// 
//Given the head of a linked list and an integer val, remove all the nodes of the linked list that has Node.val == val, and return the new head.
// 
class Solution3_2 {
public:
	ListNode* removeElements(ListNode* head, int val) {
		if (head == NULL) return NULL;
		ListNode* p = head;
		while (p->next != NULL)
		{
			//先不管头，后面的符合条件节点删除
			if (p->next->val == val)
				p->next = p->next->next;
			else
				p = p->next;
		}
		//最后看头是不是也符合
		if (head->val == val)
			head = head->next;
		return head;
	}
};
// 
//

//Odd Even Linked List
// 
//Given the head of a singly linked list, group all the nodes with odd indices together followed by the nodes with even indices, and return the reordered list.
//
class Solution3_3 {
public:
	ListNode* oddEvenList(ListNode* head) {
		if (!head) return head;
		ListNode* odd = head, * evenhead = head->next, * even = evenhead;
		while (even && even->next)
		{
			//奇偶分别串起来
			odd->next = odd->next->next;
			even->next = even->next->next;
			odd = odd->next;
			even = even->next;
		}
		//两链相连
		odd->next = evenhead;
		return head;
	}
};
//
//

//Palindrome Linked List
// 
//Given the head of a singly linked list, return true if it is a palindrome.
// 
class Solution3_4 {
public:
	bool isPalindrome(ListNode* head) {
		ListNode* slow = head, * fast = head, * prev, * temp;
		while (fast && fast->next)
			slow = slow->next, fast = fast->next->next;
		//用两点法将链表分割开，反转后半部分，之后对比两部分链表是否相同
		prev = slow, slow = slow->next, prev->next = NULL;
		while (slow)
			temp = slow->next, slow->next = prev, prev = slow, slow = temp;
		fast = head, slow = prev;
		while (slow)
			if (fast->val != slow->val) return false;
			else fast = fast->next, slow = slow->next;
		return true;
	}
};
// 
//

//Doubly Linked List
// 
struct DoublyListNode {
	int val;
	DoublyListNode* next, * prev;
	DoublyListNode(int x) : val(x), next(NULL), prev(NULL) {}
};
//

//Conclusion
// 
//总结和一些练习
//

//Merge two sorted linked lists and return it as a sorted list.
//  The list should be made by splicing together the nodes of the first two lists.
//
class Solution5_1 {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (l1 == nullptr) return l2;
		if (l2 == nullptr) return l1;
		ListNode* newList = new ListNode;
		ListNode* head = newList;
		l2->val > l1->val ? newList->val = l1->val : newList->val = l2->val;
		l2->val > l1->val ? l1 = l1->next : l2 = l2->next;
		while (l1 != nullptr && l2 != nullptr)
		{
			if (l2->val > l1->val)
			{
				newList->next = new ListNode(l1->val);
				l1 = l1->next;
			}
			else {
				newList->next = new ListNode(l2->val);
				l2 = l2->next;
			}
			newList = newList->next;
		}
		while (l1 != nullptr)
		{
			newList->next = new ListNode(l1->val);
			l1 = l1->next;
			newList = newList->next;
		}
		while (l2 != nullptr)
		{
			newList->next = new ListNode(l2->val);
			l2 = l2->next;
			newList = newList->next;
		}
		return head;
	}
};

//You are given two non-empty linked lists representing two non-negative integers. 
// The digits are stored in reverse order, and each of their nodes contains a single digit. 
// Add the two numbers and return the sum as a linked list.
//
class Solution5_2 {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		if (l1 == nullptr) return l2;
		if (l2 == nullptr) return l1;
		int val = 0, carry = 0;
		val = (l1->val + l2->val) % 10;
		carry = (l1->val + l2->val) / 10;
		ListNode* newList = new ListNode(val);
		ListNode* head = newList;
		l1 = l1->next;
		l2 = l2->next;
		while (l1 != nullptr && l2 != nullptr)
		{
			int num = l1->val + l2->val + carry;
			val = num % 10;
			carry = num / 10;
			newList->next = new ListNode(val);
			newList = newList->next;
			l1 = l1->next;
			l2 = l2->next;
		}
		while (l1 != nullptr)
		{
			int num = l1->val + carry;
			val = num % 10;
			carry = num / 10;
			newList->next = new ListNode(val);
			newList = newList->next;
			l1 = l1->next;
		}
		while (l2 != nullptr)
		{
			int num = l2->val + carry;
			val = num % 10;
			carry = num / 10;
			newList->next = new ListNode(val);
			newList = newList->next;
			l2 = l2->next;
		}
		if (carry != 0)
		{
			newList->next = new ListNode(carry);
		}
		return head;
	}
};


int main()
{
	MyLinkedlist mll;
	mll.addAtHead(7);
	mll.addAtHead(2);
	mll.addAtHead(1);
	mll.addAtIndex(3, 0);
	mll.deleteAtIndex(2);
}
