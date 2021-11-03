// explore_learn_queue_and_stack.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <queue>
#include <stack>

//
//leetcode-explore-learn-queue-&-stack
//

using namespace std;

//
//Queue
// a FIFO data structure
// 
class MyCircularQueue {
private:
	int* queue = nullptr;//数组实现
	int head = 0;
	int tail = 0;
	int size = 0;
	int ele_num = 0;
public:
	MyCircularQueue(int k) {
		queue = new int[k];
		size = k;
	}

	bool enQueue(int value) {
		if (queue == nullptr) return false;
		if (isFull()) return false;
		queue[tail++] = value;
		if (tail >= size) tail = 0;
		++ele_num;
		return true;
	}

	bool deQueue() {
		if (queue == nullptr) return false;
		if (isEmpty()) return false;
		++head;
		if (head >= size) head = 0;
		--ele_num;
		return true;
	}

	int Front() {
		if (queue == nullptr || isEmpty()) return -1;
		return queue[head];
	}

	int Rear() {
		if (queue == nullptr || isEmpty()) return -1;
		if (tail == 0) return queue[size - 1];
		return queue[tail - 1];
	}

	bool isEmpty() {
		if (ele_num == 0) return true;
		return false;
	}

	bool isFull() {
		if (ele_num == size) return true;
		return false;
	}
};
// 内置队列
void
test_queue()
{
	// 1. Initialize a queue.
	queue<int> q;
	// 2. Push new element.
	q.push(5);
	q.push(13);
	q.push(8);
	q.push(6);
	// 3. Check if queue is empty.
	if (q.empty()) {
		cout << "Queue is empty!" << endl;
		return;
	}
	// 4. Pop an element.
	q.pop();
	// 5. Get the first element.
	cout << "The first element is: " << q.front() << endl;
	// 6. Get the last element.
	cout << "The last element is: " << q.back() << endl;
	// 7. Get the size of the queue.
	cout << "The size is: " << q.size() << endl;
}
// 
//

//
//Queue and BFS
//


//
//Stack
// a LIFO data structure
// 
class MyStack {
private:
	vector<int> data;               // 用动态数组简单实现
public:
	/** Insert an element into the stack. */
	void push(int x) {
		data.push_back(x);
	}
	/** Checks whether the queue is empty or not. */
	bool isEmpty() {
		return data.empty();
	}
	/** Get the top item from the queue. */
	int top() {
		return data.back();
	}
	/** Delete an element from the queue. Return true if the operation is successful. */
	bool pop() {
		if (isEmpty()) {
			return false;
		}
		data.pop_back();
		return true;
	}
};
// 内置栈
void
test_stack()
{
	// 1. Initialize a stack.
	stack<int> s;
	// 2. Push new element.
	s.push(5);
	s.push(13);
	s.push(8);
	s.push(6);
	// 3. Check if stack is empty.
	if (s.empty()) {
		cout << "Stack is empty!" << endl;
		return;
	}
	// 4. Pop an element.
	s.pop();
	// 5. Get the top element.
	cout << "The top element is: " << s.top() << endl;
	// 6. Get the size of the stack.
	cout << "The size is: " << s.size() << endl;
}
//  
//

//
//最小堆栈
// 
class MinStack0 {
public:
	vector<int> st;//最简做法，正常出入栈然后遍历找最小，时间O(n)
	MinStack0() {
	}

	void push(int val) {
		st.push_back(val);
	}

	void pop() {
		st.pop_back();
	}

	int top() {
		return st[st.size() - 1];
	}

	int getMin() {
		int m = INT_MAX;
		for (auto a : st) {
			m = min(a, m);
		}
		return m;
	}
};
class MinStack {
private:
	stack<int> m_stack;
	stack<int> helper; //双栈，另一个存最小值，时间复杂度O(1)，空间O(n)
public:
	MinStack() {

	}

	void push(int val) {
		m_stack.push(val);
		if (helper.empty() or val < helper.top())
		{
			helper.push(val);
			return;
		}
		helper.push(helper.top());
	}

	void pop() {
		m_stack.pop();
		helper.pop();
	}

	int top() {
		return m_stack.top();
	}

	int getMin() {
		return helper.top();
	}
};
class MinStack2 {
private:
	stack<int> m_stack; //单栈，如果数值有限制范围，可以把int的高低16位当双栈
public:
	MinStack2() {

	}

	void push(int val) {
		if (m_stack.empty()) {
			int num = (val << 16) + (val & 0xffff);//优先级
			m_stack.push(num);
			return;
		}
		int min = m_stack.top() >> 16;
		int num = val < min ? ((val << 16) + (val & 0xffff)) : ((min << 16) + (val & 0xffff));
		m_stack.push(num);
	}

	void pop() {
		m_stack.pop();
	}

	int top() {
		return (int16_t)m_stack.top();
	}

	int getMin() {
		return m_stack.top() >> 16;
	}
};
class MinStack3 {
private:
	stack<int> m_stack;//不存放原值，存插值，时空复杂度都是O(1)
	int min = 0;
public:
	MinStack3() {
		//这个不对
	}

	void push(int val) {
		if (m_stack.empty())
		{
			min = val;
			m_stack.push(0);
			return;
		}
		m_stack.push(val - min);
		if (val < min) min = val;
	}
	void pop() {
		min = m_stack.top() < 0 ? (min - m_stack.top()) : min;
		m_stack.pop();
	}
	int top() {
		return min + m_stack.top();
	}
	int getMin() {
		return min;
	}
};
void test_min_stack() {
	MinStack* min_stack = new MinStack();
	min_stack->push(3);

	MinStack2* min_stack2 = new MinStack2;
	min_stack2->push(-2);
	min_stack2->push(0);
	min_stack2->push(-3);
	min_stack2->push(-2);
	int a = min_stack2->top();
	int b = min_stack2->getMin();
	min_stack2->pop();
	int c = min_stack2->top();
	int d = min_stack2->getMin();
	cout << a << " " << b << " " << c << " " << d << endl;
}
// 
//

int main()
{
	std::cout << "Hello World!\n";
	test_min_stack();
}

