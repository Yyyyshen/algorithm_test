// algorithm_4th_01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//
// 《算法》第四版
//

//书里面主要是Java语言，这里直接用C过一遍，应该也就有一定的理解了
//开始
//

//队列
// 
//先进先出FIFO策略
// 
//集合保存元素的同时，保存他们的相对顺序
//

//栈
// 
//后进先出LIFO策略
// 
//常见的例子是浏览器通过各链接在同一个标签页内导航时，前进后退就类似栈操作
//
class sample_stack {
private:
	int* stack_arr_;
	int capacity_;
	int element_num_;
public:
	sample_stack(int size) :capacity_(size) {
		element_num_ = 0;
		stack_arr_ = new int[size];
	}
	~sample_stack() {
		delete[] stack_arr_;
	}
	bool empty() {
		return element_num_ == 0;
	}
	void push(int val) {
		if (element_num_ == capacity_)
		{
			std::cerr << "stack is full" << std::endl;
			return;
		}
		stack_arr_[element_num_++] = val;
	}
	int pop() {
		if (empty())
		{
			std::cerr << "stack is empty" << std::endl;
			return -1;
		}
		return stack_arr_[--element_num_];
	}
	int size() {
		return element_num_;
	}
	int capacity() {
		return capacity_;
	}
	int top() {
		return empty() ? -1 : stack_arr_[element_num_ - 1];
	}
};

//链表
// 
//一种递归的数据结构，或者为空或者指向一个节点（双向链表有两个指针）
// 
//是很多更复杂数据结构的基础
//
struct node
{
	int val;
	node* next;
	node(int data) :val(data) {
		next = nullptr;
	}
};
void manual_link() {
	node* pn1 = new node(1);
	node* pn2 = new node(2);
	pn1->next = pn2;
}
//
//基于链表实现栈
//
class link_stack {
private:
	node* head;
	int node_num;
public:
	bool empty() {
		return head == nullptr;
	}
	int size() {
		return node_num;
	}
	void push(int val) {
		node* new_head = new node(val);
		new_head->next = head;
		head = new_head;
		++node_num;
	}
	int pop() {
		if (empty())
		{
			std::cerr << "stack is empty" << std::endl;
			return -1;
		}
		node* temp = head;
		head = head->next;
		int ret = temp->val;
		delete temp;
		--node_num;
		return ret;
	}
};
//
//同理可用链表实现队列，使用两个节点指针分别指向头尾即可
// 
//背包就更随意些，在栈基础上去掉pop就是了
//




int main()
{
	std::cout << "Hello World!\n";
}
