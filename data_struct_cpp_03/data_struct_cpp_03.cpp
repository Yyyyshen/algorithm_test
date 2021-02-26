// data_struct_cpp_03.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;
/**
 * 链表
 */
int var_0 = 0;//没用的，单纯为了注释的排版
/**
 * 单链表
 */
class Node { //节点
public:
	int data_; //Data to store (could be int,string,object etc)
	Node* nextElement;  //Pointer to next element

	Node(int data) :data_(data) {
		//Constructor to initialize nextElement of newly created Node
		nextElement = nullptr;
	}
};
class LinkedList { //链表
private:
	Node* head;  // pointing to start of the list

public:
	//一些链表基本操作
	LinkedList() {
		head = nullptr;
	}
	//获取头节点
	Node* getHead() {
		return head;
	}
	//判空
	bool isEmpty() {
		return head == nullptr ? true : false;
	}
	//打印链表
	bool printList() {
		if (isEmpty())
		{
			cout << "linked list is empty" << endl;
			return false;
		}
		Node* temp = head;
		cout << "linked list: ";
		while (temp != nullptr)
		{
			cout << temp->data_ << " -> ";
			temp = temp->nextElement;
		}
		cout << "null len: " << length() << endl;
		return true;
	}
	//从头插入
	void insertAtHead(int value) {
		Node* node = new Node(value);
		node->nextElement = head;
		head = node;
	}
	//从尾插入
	void insertAtTail(int value) {
		if (isEmpty())
		{
			//如果是空的，直接复用从头插入
			insertAtHead(value);
		}
		else
		{
			Node* node = new Node(value);
			Node* temp = head;
			while (temp->nextElement != nullptr)
			{
				temp = temp->nextElement;
			}
			temp->nextElement = node;
		}
	}
	//搜索节点是否存在
	bool search(int value) {
		Node* temp = head;
		while (temp != nullptr)
		{
			if (temp->data_ == value)
			{
				return true;
			}
			temp = temp->nextElement;
		}
		return false;
	}
	//从头删除
	bool deleteAtHead() {
		if (isEmpty())
		{
			cout << "linked list is empty" << endl;
			return false;
		}
		Node* temp = head;//记录当前头
		head = head->nextElement;//头指向下一个节点
		delete temp;//删除当前头
		return true;
	}
	//从尾删除
	bool deleteAtTail() {
		if (isEmpty())
		{
			cout << "linked list is empty" << endl;
			return false;
		}
		Node* temp = head;
		Node* last = nullptr;//记录删除后的最后一个对象
		while (temp->nextElement != nullptr)
		{
			last = temp;
			temp = temp->nextElement;
		}
		delete temp;
		if (last != nullptr)
		{
			last->nextElement = nullptr;
		}
		return true;
	}
	//根据值删除
	bool deleteByValue(int value) {
		if (isEmpty())
		{
			cout << "linked list is empty" << endl;
			return false;
		}
		Node* temp = head;
		Node* pre_temp = nullptr;
		//如果头就是要删除的，直接复用
		if (temp->data_ == value)
		{
			deleteAtHead();
			return true;
		}
		//往后找
		pre_temp = temp;
		temp = temp->nextElement;
		while (temp != nullptr)
		{
			if (temp->data_ == value)
			{
				pre_temp->nextElement = temp->nextElement;
				delete temp;
				return true;
			}
			pre_temp = temp;
			temp = temp->nextElement;
		}
		cout << "the value is not exist" << endl;
		return false;
	}
	//获取链表长度
	int length() {
		int len = 0;
		Node* temp = head;
		while (temp != nullptr)
		{
			len++;
			temp = temp->nextElement;
		}
		return len;
	}
	//翻转链表
	void reverse() {
		Node* previous = nullptr; //To keep track of the previous element, will be used in swapping links
		Node* current = head; //firstElement
		Node* next = nullptr;

		//While Traversing the list, swap links
		while (current != nullptr) {
			next = current->nextElement;
			current->nextElement = previous;//把每个节点指向下个节点的指针指向前一个节点
			previous = current;
			current = next;
		}

		head = previous; // 最后头指向原本最后一个节点
	}
	//检测是否存在循环
	bool detectLoop() {
		//我的思路就是简单遍历对比是否会重新指向头
		//if (isEmpty())
		//{
		//	return false;
		//}
		//Node* temp = head->nextElement;
		//while (temp != nullptr)
		//{
		//	if (temp == head)
		//	{
		//		return true;
		//	}
		//	temp = temp->nextElement;
		//}
		//return false;
		//网站思路是两个指针，一个跑的比另一个快，如果他们会重合，说明是环
		Node* slow = head, * fast = head; //starting from head of the list

		while (slow && fast && fast->nextElement) //checking if all elements exist 
		{
			slow = slow->nextElement;
			fast = fast->nextElement->nextElement;

			/* If slow and fast meet at some point then there
				is a loop */
			if (slow == fast) {
				// Return 1 to indicate that loop is found */
				return true;
			}
		}
		// Return 0 to indeciate that ther is no loop*/
		return false;
	}
	//找中间节点
	int findMid() {
		if (isEmpty())
		{
			return 0;//链表为空直接返回
		}
		Node* temp = head;
		if (temp->nextElement == nullptr)
		{
			return temp->data_;//只有一个头，直接返回
		}
		//自己思路，用length计算位置
		//int ret = length() % 2, mid, cur = 0;
		//if (ret == 1) {
		//	mid = length() / 2;
		//}
		//if (ret == 0) {
		//	mid = length() / 2 - 1;
		//}
		//while (temp != nullptr) {
		//	if (cur == mid) {
		//		return temp->data_;
		//	}
		//	temp = temp->nextElement;
		//	cur++;
		//}
		//网站思路，用步长为2的指针当结尾，并以单步长移位当做中间节点
		Node* midNode = temp; //midNode starts at head
		temp = temp->nextElement->nextElement; //currentNode moves two steps forward

		//Move midNode (Slower) one step at a time
		//Move currentNode (Faster) two steps at a time
		//When currentNode reaches at end, midNode will be at the middle of List
		while (temp != nullptr) {		// traversing from head to end

			midNode = midNode->nextElement;

			temp = temp->nextElement;		// pointing to current's next
			if (temp != nullptr)
				temp = temp->nextElement;		// pointing to current's next

		}
		if (midNode != nullptr)		// pointing at middle of the list
			return midNode->data_;
		return 0;
	}
	//移除重复项
	void removeDuplicates() {
		struct Node* start, * startNext, * dup;
		start = head;

		/* Pick elements one by one */
		while (start != nullptr && start->nextElement != nullptr) {
			startNext = start;
			//外层依次遍历各值
			/* Compare the picked element with rest
			   of the elements */
			while (startNext->nextElement != nullptr) {
				//内层遍历比较后面是否与外层遍历值相同的节点，相同则删除
				/* If duplicate then delete it */
				if (start->data_ == startNext->nextElement->data_) {
					/* sequence of steps is important here */
					dup = startNext->nextElement; // picking duplicate
					// skipping elements from the list to be deleted
					startNext->nextElement = startNext->nextElement->nextElement;
					delete(dup); // deleting duplicate
				}
				else
					startNext = startNext->nextElement; // pointing to next of startNext
			}
			start = start->nextElement;
		}
	}
	//取并集放入第一个表
	void Union(LinkedList list1, LinkedList list2) {
		//Return other List if one of them is empty
		if (list1.isEmpty())
			return;
		if (list2.isEmpty())
			return;

		Node* start = list1.head; // starting from head of list 1

		//Traverse first list till the last element
		while (start->nextElement != nullptr) {
			start = start->nextElement;
		}
		//直接两个链表连起来去重
		//Link last element of first list to the first element of second list
		start->nextElement = list2.head; // appendinf list2 with list 1
		list1.removeDuplicates(); // removing duplicates from list and return list
		list1.printList();
	}
	//取交集放在新的链表
	void Intersection(LinkedList list1, LinkedList list2) {
		LinkedList list3;
		Node* t1 = list1.head, * t2 = list2.head;
		//遍历其中一个链表每个值在另一个链表中的相同值放入新链表，最后对新链表去重
		// Traverse both lists and store the same element 
		// in the resultant list list3
		while (t1 != nullptr) {
			while (t2 != nullptr) {
				if (t1->data_ == t2->data_)
					list3.insertAtHead(t1->data_);
				t2 = t2->nextElement;
			}
			t2 = list2.head;
			t1 = t1->nextElement;
		}
		list3.removeDuplicates();
		list3.printList();
	}
	//查找从结尾开始的第N个节点
	int findNth(int n) {
		if (isEmpty()) // if list is empty return -1
			return -1;

		int length = 0;
		Node* currentNode = head; // pointing to head of the list

		// finding the length of the list
		while (currentNode != nullptr) {
			currentNode = currentNode->nextElement;
			length++;
		}
		//方法一：找出链表长度，通过长度计算正向索引，检查索引合法性，正向寻找节点值
		//Find the Node which is at (len - n) position from start
		currentNode = head;
		int position = length - n;

		if (position < 0 || position > length) // check if out of the range of the list
			return -1;

		int count = 0;
		// traversing till the nth Element of the list
		while (count != position && currentNode != nullptr) { // finding the position of the element
			currentNode = currentNode->nextElement;
			count++;
		}

		if (currentNode != nullptr) // if node exists
			return currentNode->data_;

		return -1;
	}
	int findNth_2(int n) {
		if (isEmpty()) // if list is empty return -1
			return -1;
		// This pointer will reach the nth node
		Node* nth_node = head;
		// This pointer will reach the end node
		Node* end_node = head;
		//方法二：两个指针，把一个节点调整到距离另一个节点为n的位置，两个节点同时向后推进，当后面的节点为结尾节点时，另一个节点就是从结尾开始第n个节点
		int count = 0;

		while (count < n) {
			if (end_node == nullptr) {
				return -1;
			}
			end_node = end_node->nextElement;
			count++;
		}

		while (end_node != nullptr) {
			end_node = end_node->nextElement;
			nth_node = nth_node->nextElement;
		}
		if (nth_node != nullptr) {
			return nth_node->data_;
		}
		return -1;
	}
};
/**
Operation			Linked List			Array
Access					O(n)			O(1)
Insert (at head)		O(1)			O(n)
Delete (at head)		O(1)			O(n)
Insert (at tail)		O(n)			O(n)
Delete (at tail)		O(n)			O(n)
 */
void test_sll()
{
	LinkedList sll;
	cout << sll.isEmpty() << endl;
	for (int i = 1; i < 10; i++) {
		sll.insertAtHead(i); // inserting data at head of the list
	}
	sll.printList();
	for (int i = 2; i < 5; i++) {
		sll.insertAtTail(i); // inserting value at the tail of the list
	}
	sll.printList();
	sll.deleteAtHead();
	sll.printList();
	sll.deleteAtTail();
	sll.printList();
	sll.deleteByValue(1);
	sll.printList();
	sll.reverse();
	sll.printList();
	sll.removeDuplicates();
	sll.printList();
}
/**
 * 双向链表
 *
 * 对于单链表，除了依赖于头节点的操作复杂度为O(1)，其他操作几乎至少都需要遍历一遍链表，也就是复杂度至少为O(n)
 * 双向链表可以一定程度上提高很多操作的效率
 */
class Node_2 {
public:
	int data; //Data to store (could be int,string,object etc)
	Node_2* nextElement;  //Pointer to next element
	Node_2* previousElement; //pointer to previous element
	Node_2() {
		//Constructor to initialize nextElement of newlyCreated Node
		nextElement = nullptr;
		previousElement = nullptr;
	}
};
class DoublyLinkedList {
private:
	Node_2* head;
	Node_2* tail;//可再记录一个尾指针，增加便利性
public:
	DoublyLinkedList() {      // Doubly linkedlist constructor
		head = nullptr;
	}
	bool isEmpty() {      // check if the list is empty
		if (head == nullptr) //Check whether the head points to null
			return true;
		else
			return false;
	}

	Node_2* getHead() {
		return head;
	}

	bool printList() {    // printing all elements of the list
		if (isEmpty()) {
			cout << "List is Empty!" << endl;
			return false;
		}
		Node_2* temp = head;   // temp points to head of the list
		cout << "List : ";

		while (temp != nullptr) {    // traverse through the list
			cout << temp->data << "->";
			temp = temp->nextElement;
		}
		cout << "null " << endl;
		return true;
	}

	bool insertAtHead(int value) {    // insert value at head
		Node_2* newNode = new Node_2();
		newNode->data = value;
		newNode->previousElement = nullptr;
		newNode->nextElement = head; //Linking newNode to head's nextNode
		if (head != nullptr) {
			head->previousElement = newNode;
		}
		//move the head to point to the new node
		head = newNode;
		cout << value << " Inserted!    ";
	}

	bool deleteAtHead() {
		bool deleted = false;
		if (isEmpty()) {
			cout << "List is Empty" << endl;
			return deleted;
		}
		head = head->nextElement;    // pointing head to head's nextElement
		head->previousElement = nullptr;
		return true;
	}

	bool Delete(int value)
	{
		bool deleted = false;
		if (isEmpty()) {
			cout << "List is Empty" << endl;
			return deleted;
		}

		//if list is not empty, start traversing it from the head
		Node_2* currentNode = head;

		if (currentNode->data == value) {    // deleting value of head
			cout << value << " deleted!" << endl;
			deleted = deleteAtHead();
			return deleted;
		}

		//Traversing/Searching for Node to Delete
		while (currentNode != nullptr) {

			//Node to delete is found
			if (currentNode->data == value) {
				// pointing current's previous next to current's next
				currentNode->previousElement->nextElement = currentNode->nextElement;

				if (currentNode->nextElement != nullptr)
					// pointing current's next previous to current's next
					currentNode->nextElement->previousElement = currentNode->previousElement;

				cout << value << " deleted!" << endl;

				deleted = true;
				return deleted;
			}
			// pointing current to current's next
			currentNode = currentNode->nextElement;
		}

		if (deleted == false) {
			cout << value << " does not exist!" << endl;
		}
		return deleted;
	}//end of delete()
};


int main()
{
	test_sll();
	return 0;
}

