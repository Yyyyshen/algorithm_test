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
		if (index > size - 1 || index < 0) return -1;
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
	ListNode(int x) : val(x), next(NULL) {}
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

	}
};
// 
//


int main()
{
	MyLinkedlist mll;
	mll.addAtHead(7);
	mll.addAtHead(2);
	mll.addAtHead(1);
	mll.addAtIndex(3, 0);
	mll.deleteAtIndex(2);
}
