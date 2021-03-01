// data_struct_cpp_04.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;
/**
 * 栈和队列
 */
int val_0 = 0;
/**
 * 栈——LIFO
 *
 * 软件常见撤销操作多用栈结构实现
 * 栈结构可以用数组或者链表实现，这里使用数组
 */
class YStack {
private:
	int* stackArr;
	int capacity;
	int numElements;
public:
	//初始化
	YStack(int size) {
		capacity = size;
		stackArr = new int[size];
		numElements = 0;
	}
	//打印
	void showStack() {
		int i = 0;
		while (i < numElements)
		{
			cout << '\t' << stackArr[numElements - 1 - i];
			i++;
		}
		cout << endl;
	}
	//判空
	bool isEmpty() {
		return numElements == 0;
	}
	//取栈顶
	int getTop() {
		return isEmpty() ? -1 : stackArr[numElements - 1];
	}
	//取大小
	int getSize() {
		return numElements;
	}
	//压栈
	bool push(int val) {
		if (numElements >= capacity)
		{
			cout << "stack full" << endl;
			return false;
		}
		stackArr[numElements] = val;
		numElements++;
	}
	//弹栈
	int pop() {
		if (isEmpty())
		{
			cout << "stack empty" << endl;
			return -1;
		}
		numElements--;
		return stackArr[numElements];
	}
};
//测试栈
void testYStack()
{
	YStack s(10);
	cout << "\ns.top(): " << s.getTop();
	s.push(10);
	s.push(30);
	s.push(20);
	s.push(5);
	s.push(1);
	cout << "\nThe stack is: ";
	s.showStack();
	cout << "\ns.top(): " << s.getTop();
	cout << "\ns.pop(): " << s.pop() << endl;
	cout << "\ns.pop(): " << s.pop() << endl;
	cout << "\ns.pop(): " << s.pop() << endl;
	cout << "\ns.pop(): " << s.pop() << endl;
	s.push(23);
	s.push(57);
	s.push(17);
	s.push(29);
	s.push(6);
	s.push(7);
	s.push(12);
	s.push(19);
	cout << "\nThe stack is: ";
	s.showStack();
	cout << "\ns.pop(): " << s.pop() << endl;
	cout << "s.pop(): " << s.pop() << endl;
	cout << "The stack size is: " << s.getSize() << endl;
}
/**
 * 队列——FIFO
 */
class YQueue {
private:
	int* queueArr;
	int capacity;
	int numElements;
	int front;
	int back;
public:
	//构造
	YQueue(int size) {
		capacity = size;
		queueArr = new int[size];
		numElements = 0;
		front = 0;
		back = -1;
	}
	//判空
	bool isEmpty() {
		return (numElements == 0);
	}
	//取队列头
	int getFront() {
		if (isEmpty()) {
			cout << "Queue Empty" << endl;
			return -1;
		}
		else
			return queueArr[front];
	}
	//取大小
	int getSize() {
		return numElements;
	}
	//入队（循环使用数组）
	void enqueue(int val) {
		if (numElements == capacity)
		{
			cout << "queue full" << endl;
			return;
		}
		if (back == capacity - 1)
		{
			back = -1;
		}
		queueArr[++back] = val;
		numElements++;
	}
	//出队
	int dequeue() {
		if (isEmpty()) {
			cout << "Queue Empty" << endl;
			return -1;
		}
		int tmp = queueArr[front++];

		if (front == capacity)
			front = 0;
		numElements--;
		return tmp;
	}
	void showQueue() {
		int i = front;
		int count = 0;
		while (count != numElements) {
			cout << '\t' << queueArr[i % capacity];//利用余数从队列头处开始打印
			i++;
			count++;
		}
		cout << endl;
	}
};
/**
 * 利用队列生成从1到n的二进制数字符串
 */
#include <string>
string* findBin(int n) {
	//return your answers in the following result array
	string* result = new string[n];
	YQueue queue(n + 1);
	queue.enqueue(1);

	string s1, s2;
	for (int i = 0; i < n; i++) {
		result[i] = to_string(queue.dequeue());
		s1 = result[i] + "0";
		s2 = result[i] + "1";
		queue.enqueue(stoi(s1));
		queue.enqueue(stoi(s2));
	}
	return result;
}
/**
 * 使用单个数组实现两个栈
 */
class twoStacks {

private:
	int size;
	int* arr;
	int top1, top2;
	//Store top value indices of Stack 1 and Stack 2
public:
	twoStacks(int n) {
		size = n;
		arr = new int[size];
		top1 = -1;
		top2 = size;

	}
	//Insert Value in First Stack  
	void push1(int value) {
		//Check for empty space and insert value if there's an empty space.
		if (top1 < top2 - 1) {
			arr[++top1] = value;
		}
	}
	//Insert Value in Second Stack  
	void push2(int value) {
		//Check for empty space and insert value if there's an empty space.
		if (top1 < top2 - 1) {
			arr[--top2] = value;
		}
	}

	//Return and remove top Value from First Stack
	int pop1() {
		//Get value from top1 index and increment it.
		if (top1 >= 0) {
			int val = arr[top1--];
			return val;
		}
		return -1;
	}

	//Return and remove top Value from Second Stack
	int pop2() {
		//Get value from top2 index and increment it.
		if (top2 < size) {
			int val = arr[top2++];
			return val;
		}
		return -1;
	}
};
/**
 * 反转队列中前n个元素
 */
YQueue reverseK(YQueue queue, int k) {
	if (!queue.isEmpty()) {
		YStack stack(k);
		int count = 0;
		//将前k个放入栈
		while (count < k) {
			stack.push(queue.dequeue());
			count++;
		}
		//利用栈特性重新入队
		while (!stack.isEmpty()) {
			queue.enqueue(stack.pop());
		}
		int size = queue.getSize();
		//重置队列头位置
		for (int i = 0; i < size - k; i++) {
			queue.enqueue(queue.dequeue());
		}

	}

	return queue;
}
void testReverseK() {
	YQueue mQ(5);

	mQ.enqueue(1);
	mQ.enqueue(2);
	mQ.enqueue(3);
	mQ.enqueue(4);
	mQ.enqueue(5);
	mQ.showQueue();
	mQ = reverseK(mQ, 3);
	mQ.showQueue(); //show queue prepended in the hidden code
}
/**
 * 用栈实现队列
 * 两个栈来实现
 */
class newQueue {
private:
	YStack* mainStack;
	YStack* tempStack;
public:
	newQueue(int size) {
		//Can use size from argument to create stack
		mainStack = new YStack(size);
		tempStack = new YStack(size);
	}
	void enQueue(int value) {
		//Traverse elements from mainStack to tempStack
		//Push given value to mainStack
		//Traverse back the elements from tempStack to mainStack
		while (!mainStack->isEmpty()) {

			tempStack->push(mainStack->pop());
		}

		mainStack->push(value);

		while (!tempStack->isEmpty()) {

			mainStack->push(tempStack->pop());
		}


	}
	int deQueue() {
		//If mainStack is empty then we have no elements.
		//else return top element of mainStack as we always put oldest entered
		//element at the top of mainStack
		if (mainStack->isEmpty())
			return -1;
		else
			return mainStack->pop();
	};

};
/**
 * 排序栈中元素
 * 用另一个栈来辅助排序，原理同——汉诺塔
 */
YStack sortStack(YStack stack, int size) {
	//1. Use a second tempStack.
	//2. Pop value from mainStack.
	//3. If the value is greater or equal to the top of tempStack, then push the value in tempStack
	//else pop all values from tempStack and push them in mainStack and in the end push value in tempStack and repeat from step 2.
	//till mainStack is not empty.
	//4. When mainStack will be empty, tempStack will have sorted values in descending order.
	//5. Now transfer values from tempStack to mainStack to make values sorted in ascending order.
	YStack tempStack(size);

	while (!stack.isEmpty()) {
		int value = stack.pop();

		if (value >= tempStack.getTop()) {
			tempStack.push(value);
		}
		else {
			while (!tempStack.isEmpty()) {
				stack.push(tempStack.pop());
			}
			tempStack.push(value);
		}
	}

	//Transfer from tempStack => stack
	while (!tempStack.isEmpty()) {
		stack.push(tempStack.pop());
	}
	return stack;
}
//另一个思路，递归，先弹出所有元素，再递归比较按顺序插入回栈
void insert(YStack* stack, int value) {
	if (stack->isEmpty() || value < stack->getTop())
		stack->push(value);
	else {
		int temp = stack->pop();
		insert(stack, value);
		stack->push(temp);
	}
}
void sortStack(YStack* stack) {
	if (!stack->isEmpty()) {
		int value = stack->pop();
		sortStack(stack);
		insert(stack, value);
	}
}
/**
 * 使用栈计算后缀表达式
 *
 * 后缀表达式：921*-8-4+ 等价于 9 - 2 * 1 - 8 + 4
 */
int evaluatePostFix(string exp) {

	YStack stack(exp.length());
	char character;
	int x, y;
	//1.Scan expression character by character,
	//2.If character is a number push it in stack
	//3.If character is operator then pop two elements from stack
	//perform the operation and put the result back in stack
	//At the end, Stack will contain result of whole expression.
	for (int i = 0; i < exp.length(); i++) {

		character = exp[i];

		if (!isdigit(character)) {
			x = stack.pop();
			y = stack.pop();

			switch (character) {
			case '+':
				stack.push(y + x);
				break;
			case '-':
				stack.push(y - x);
				break;
			case '*':
				stack.push(y * x);
				break;
			case '/':
				stack.push(y / x);
				break;
			}
		}
		else
			stack.push(character - '0');
	}
	return stack.pop();
}
void testEva() {
	evaluatePostFix("921*-8-4+");
}
/**
 * 对于给定数组，找出每个元素后面比自身大的值，例如：
 * int arr[]= {4, 6, 3, 2, 8, 1};
 * result = {6, 8, 8, 8, -1, -1}
 */
int* nextGreaterElement(int* arr, int size) {

	YStack stack(size);
	int* result = new int[size];
	int next, top;
	for (int i = size - 1; i >= 0; i--) {

		next = arr[i]; //potential nextGreaterElement
		top = stack.getTop();

		while (!stack.isEmpty() && top <= next) {

			stack.pop();
			top = stack.getTop();
		}

		if (!stack.isEmpty())
			result[i] = stack.getTop();
		else
			result[i] = -1;

		//For next iteration
		stack.push(next);

	} //end of for loop
	return result;
}
/**
 * 用栈检测表达式括号是否平衡，例如；
 * string exp = "{[({})]}";
 * true
 */
bool isBalanced(string exp) {

	//Iterate through the string exp.
	//For each opening parentheses, push it into stack
	//For every closing parentheses check for its opening parentheses in stack
	//If you can't find the opening parentheses for any closing one then returns false.
	//and after complete traversal of string exp, if there's any opening parentheses left
	//in stack then also return false.
	//At the end return true if you haven't encountered any of the above false conditions.
	YStack stack(exp.length());
	char character;
	//把一边的括号先压栈，在遇到右括号时，在栈中检查是否有对应括号
	for (int i = 0; i < exp.length(); i++) {

		character = exp[i];
		if (character == '}' || character == ')' || character == ']') {

			if (stack.isEmpty())
				return false;

			if ((character == '}' && stack.pop() != '{') || (character == ')' && stack.pop() != '(') || (character == ']' && stack.pop() != '['))
				return false;

		}
		else
			stack.push(character);

	}
	if (!stack.isEmpty())
		return false;

	return true;
}
/**
 * 取栈中最小值
 * 
 */
class newStack {

	//We will use two stacks mainStack to hold origional values
	//and minStack to hold minimum values. Top of minStack will always
	//be the minimum value from mainStack
	YStack* mainStack;
	YStack* minStack;
public:
	newStack(int size) {
		mainStack = new YStack(size);
		minStack = new YStack(size);
	}

	//Removes and return value from newStack
	//1. Pop element from minStack to make it sync with mainStack,
	//2. Pop element from mainStack and return that value.
	int pop() {

		minStack->pop();
		return mainStack->pop();

	}

	//Pushes values into newStack
	//1. Push value in mainStack and check value with the top value of minStack
	//2. If value is greater than top, then push top in minStack
	//else push value in minStack.
	void push(int value) {

		mainStack->push(value);

		if (value > minStack->getTop() && !minStack->isEmpty()) {
			minStack->push(minStack->getTop());
		}//只压入更小的值，其余的为了保证同步，压入当前栈顶值
		else
			minStack->push(value);
	}

	//Returns minimum value from newStack in O(1) Time
	int min() {
		return minStack->getTop();
	}

};


int main()
{
	//testYStack();
	//testReverseK();
	testEva();
}

