// data_struct_cpp_05.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
/**
 * 图
 */
int val_0 = 0;
/**
 * 组成部分为顶点和边缘
 * 顶点构成一个图形，边连接各个顶点，可以是单向也可以是双向
 * 常用于GPS、神经网络、搜索引擎等
 *
 * 术语：
 * 顶点度，分为进出两个方向
 * 平行边，两个无向边最终顶点相同，则平行；两个有向边起终点都相同，则平行
 * 自循环，边的起终点在同一个顶点上
 * 邻接，两个有边连接的顶点被认为是相邻的
 *
 * 常见类型：
 * 有向图
 * 无向图
 *
 * 表示图的常见方式：
 * 邻接矩阵
 * 邻接表，列表数组用于存储图形中的所有边，数组大小等于顶点数
 */
using namespace std;
//图实现依赖于链表
class Node { //节点
public:
	int data; //Data to store (could be int,string,object etc)
	Node* nextElement;  //Pointer to next element

	Node(int d) :data(d) {
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
			cout << temp->data << " -> ";
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
			if (temp->data == value)
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
		if (temp->data == value)
		{
			deleteAtHead();
			return true;
		}
		//往后找
		pre_temp = temp;
		temp = temp->nextElement;
		while (temp != nullptr)
		{
			if (temp->data == value)
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

};
//一些算法需要使用之前的结构
class myQueue {
private:
	int* queueArr;
	int capacity;
	int numElements;
	int front;
	int back;
public:
	//构造
	myQueue(int size) {
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
class myStack {
private:
	int* stackArr;
	int capacity;
	int numElements;
public:
	//初始化
	myStack(int size) {
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
//图的基本构成
class Graph {
private:
	//Total number of vertices
	int vertices;
	//definining an array which can hold multiple LinkedLists equal to the number of vertices in the graph
	LinkedList* array;
public:

	Graph(int v) {
		//Creating a new LinkedList for each vertex/index of the array
		array = new LinkedList[v];
		vertices = v;
	}

	void addEdge(int source, int destination) {
		if (source < vertices && destination < vertices)
			array[source].insertAtHead(destination);
	}

	void printGraph() {
		cout << "Adjacency List of Directed Graph" << endl;
		Node* temp;
		for (int i = 0; i < vertices; i++) {
			cout << "|" << i << "| => ";
			temp = (array[i]).getHead();

			while (temp != NULL) {
				cout << "[" << temp->data << "] -> ";
				temp = temp->nextElement;
			}
			cout << "NULL" << endl;
		}
	}

	LinkedList* getArray()
	{
		return array;
	}

	int getVertices()
	{
		return vertices;
	}
};
/**
 * 二部图
 * 顶点集V可分割为两个互不相交的子集，并且图中每条边依附的两个顶点都分属于这两个互不相交的子集，两个子集内的顶点不相邻。
 */
int val_1 = 1;
/**
 * 图遍历
 * 广度优先，遍历某个级别中的所有节点，再进入下一个级别，可确保对于任何一个起点都能一次到达所有顶点
 * 深度优先，从任何节点开始，移动到相邻节点，直到最远的顶点，再回到起点选择另一个相邻节点继续该操作
 */
void bfsTraversal_helper(Graph g, int source, bool* visited, string& result)
{

	if (g.getVertices() < 1) {
		return;
	}
	//Create Queue(Implemented in previous chapters) for Breadth First Traversal and enqueue source in it
	myQueue queue(g.getVertices());

	queue.enqueue(source);
	visited[source] = true;
	int current_node;
	//Traverse while queue is not empty
	while (!queue.isEmpty()) {

		//Dequeue a vertex/node from queue and add it to result
		current_node = queue.dequeue();

		result += to_string(current_node);

		//Get adjacent vertices to the current_node from the array,
		//and if they are not already visited then enqueue them in the Queue
		Node* temp = (g.getArray())[current_node].getHead();

		while (temp != NULL) {

			if (!visited[temp->data]) {
				queue.enqueue(temp->data);
				visited[temp->data] = true; //Visit the current Node
			}
			temp = temp->nextElement;
		}
	} //end of while
}
//广度优先算法
string bfsTraversal(Graph g)
{
	string result = "";
	//Bool Array to hold the history of visited nodes
	//Make a node visited whenever you push it into stack
	bool* visited = new bool[g.getVertices()];
	for (int i = 0; i < g.getVertices(); i++) {
		visited[i] = false;
	}
	for (int i = 0; i < g.getVertices(); i++) {
		if (!visited[i])
			bfsTraversal_helper(g, i, visited, result);
	}
	delete[] visited;
	visited = NULL;
	return result;
}
//
void dfs_helper(Graph g, int source, bool* visited, string& result)
{
	if (g.getVertices() < 1) {
		return;
	}

	//Create Stack(Implemented in previous chapters) for Depth First Traversal and Push source in it
	myStack stack(g.getVertices());

	stack.push(source);
	visited[source] = true;
	int current_node;
	Node* temp;
	//Traverse while stack is not empty
	while (!stack.isEmpty()) {

		//Pop a vertex/node from stack and add it to the result
		current_node = stack.pop();
		result += to_string(current_node);

		//Get adjacent vertices to the current_node from the array,
		//and if they are not already visited then push them in the stack
		temp = (g.getArray())[current_node].getHead();

		while (temp != NULL) {

			if (!visited[temp->data]) {
				stack.push(temp->data);
				//Visit the node
				visited[temp->data] = true;
			}
			temp = temp->nextElement;
		}
	} //end of while

}
//深度优先算法
string dfsTraversal(Graph g)
{

	string result = "";

	//Bool Array to hold the history of visited nodes
	//Make a node visited whenever you push it into stack
	bool* visited = new bool[g.getVertices()];
	for (int i = 0; i < g.getVertices(); i++) {
		visited[i] = false;
	}
	for (int i = 0; i < g.getVertices(); i++) {
		if (!visited[i])
			dfs_helper(g, i, visited, result);
	}

	delete[] visited;
	visited = NULL;

	return result;
}
/**
 * 检测图中是否有环
 */
bool detectCycleRec(Graph g, int i, bool* visited, bool* recNodes) {
	// Check if current node is being visited in the same recursive call

	if (visited[i] == false) {
		// Set recursive array and visited to true
		visited[i] = true;
		recNodes[i] = true;

		int adjacent;
		Node* adjacentNode = (g.getArray())[i].getHead();
		while (adjacentNode != NULL) {
			// Access adjacent node and repeat algorithm
			adjacent = adjacentNode->data;
			if ((!visited[adjacent]) && detectCycleRec(g, adjacent, visited, recNodes))
				return true;  // Loop found
			else if (recNodes[adjacent])
				return true;
			adjacentNode = adjacentNode->nextElement;
		}

	}


	recNodes[i] = false;
	return false;
}
bool detectCycle(Graph g) {

	int num_of_vertices = g.getVertices();
	//Boolean Array to hold the history of visited nodes (by default-false)
	//Make a node visited whenever you traverse it
	bool* visited = new bool[num_of_vertices];

	//Boolean array of vertices which will recursively called
	bool* recNodes = new bool[num_of_vertices];

	for (int i = 0; i < num_of_vertices; i++)
	{
		visited[i] = false;
		recNodes[i] = false;
	}

	for (int i = 0; i < num_of_vertices; i++) { // Recursive function called
		if (detectCycleRec(g, i, visited, recNodes))
			return true;
		// If cycle detected, return true
	}
	return false;
}
/**
 * 寻找母节点
 */
void DFS(Graph g, int node, bool* visited) {

	// Mark the current node as visited and print it
	visited[node] = true;

	// Recur for all the vertices adjacent to this vertex
	Node* temp = (g.getArray())[node].getHead();
	while (temp) {
		if (visited[temp->data] == false)
			DFS(g, temp->data, visited);
		temp = temp->nextElement;
	}
}
int findMotherVertex(Graph g) {
	//visited[] is used for DFS. Initially all are
	// initialized as not visited

	bool* visited = new bool[g.getVertices()];
	//To store last finished vertex (or mother vertex)
	int lastV = 0;

	//Do a DFS traversal and find the last finished vertex
	for (int i = 0; i < g.getVertices(); i++) {
		if (visited[i] == false) {
			DFS(g, i, visited);
			lastV = i;
		}
	}


	// If there exist mother vertex (or vetices) in given graph, then v must be one (or one of them)
	// Now check if v is actually a mother vertex (or graph has a mother vertex).
	//We basically check if every vertex is reachable from v or not.

	//Reset all values in visited[] as false and do
	//DFS beginning from v to check if all vertices are
	//reachable from it or not.

	for (int i = 0; i < g.getVertices(); i++)
	{
		visited[i] = false;

	}

	DFS(g, lastV, visited);
	for (int i = 0; i < g.getVertices(); i++) {
		if (visited[i] == false)
			return -1;

	}
	delete[] visited;
	visited = NULL;
	return lastV;

}
/**
 * 计算无向图总边数
 */
int numEdges(Graph g) {
	// For undirected graph, just sum up the size of
	// all the adjacency lists for each vertex and then divide it by 2.
	// It will give us total number of edges in the graph.
	int sum = 0;
	Node* temp;
	for (int i = 0; i < g.getVertices(); i++) {

		temp = (g.getArray())[i].getHead();

		while (temp != NULL) {
			sum++;
			temp = temp->nextElement;
		}
	}
	return sum / 2;
}
/**
 * 查看两个节点间是否存在路径
 */
bool checkPath(Graph g, int source, int destination) {
	//Perfrom DFS Traversal starting from source and if you reach destination
	//then it means that there exist a path between source and destination
	//so return true and if you traverse the graph but can't reach destination
	//then simply return false.
	if (source == destination) {
		return true;
	}
	//Bool Array to hold the history of visited nodes
	//Make a node visited whenever you push it into stack
	bool* visited = new bool[g.getVertices()];

	//Create Stack
	myStack stack(g.getVertices());

	stack.push(source);
	visited[source] = true;

	//Traverse while stack is not empty
	int current_node;
	Node* temp;
	while (!stack.isEmpty()) {

		//Pop a vertex/node from stack
		current_node = stack.pop();

		//Get adjacent vertices to the current_node from the array,
		//and if only push unvisited adjacent vertices into stack
		//Before pushing into stack, check if it's the destination.
		temp = (g.getArray())[current_node].getHead();

		while (temp != NULL) {

			if (!visited[temp->data]) {

				if (temp->data == destination) {
					return true;
				}

				stack.push(temp->data);
				visited[temp->data] = true;

			}

			temp = temp->nextElement;
		}

	} //end of while
	delete[] visited;
	visited = NULL;
	return false;
}
/**
 * 判断无向图是否是树
 */
bool checkCycle(Graph g, int vertex, bool* visited, int parent)
{
	// Mark the current vertex as visited
	visited[vertex] = true;

	// Recursive calls for all the vertices adjacent to this vertex
	Node* temp = (g.getArray())[vertex].getHead();

	while (temp != NULL) {
		// If an adjacent is not visited, then make recursive call on the adjacent
		if (!visited[temp->data]) {
			if (checkCycle(g, temp->data, visited, vertex))
				return true;
		}
		else if (temp->data != parent)
			return true;
		//^ If an adjacent is visited and not parent of current
		// vertex, then there is a cycle.
		temp = temp->nextElement;
	}

	return false;
}
bool isTree(Graph g)
{

	bool* visited = new bool[g.getVertices()];
	for (int i = 0; i < g.getVertices(); i++)
		visited[i] = false;


	if (checkCycle(g, 0, visited, -1))
		return false;

	for (int i = 0; i < g.getVertices(); i++) {
		if (!visited[i])
			return false;
	}
	delete[] visited;
	visited = NULL;
	return true;
}
/**
 * 两个顶点最短路径
 */
int findMin(Graph g, int source, int destination) {
	if (source == destination) {
		return 0;
	}

	int result = 0;
	int num_of_vertices = g.getVertices();

	//Bool Array to hold the history of visited nodes (by default-false)
	//Make a node visited whenever you enqueue it into queue
	bool* visited = new bool[num_of_vertices];

	//For keeping track of distance of current_node from source
	int* distance = new int[num_of_vertices];

	//Create Queue for Breadth First Traversal and enqueue source in it
	myQueue queue(num_of_vertices);

	queue.enqueue(source);
	visited[source] = true;
	int current_node;
	Node* temp;
	//Traverse while queue is not empty
	while (!queue.isEmpty()) {

		//Dequeue a vertex/node from queue and add it to result
		current_node = queue.dequeue();

		//Get adjacent vertices to the current_node from the array,
		//and if they are not already visited then enqueue them in the Queue
		//and also update their distance from source by adding 1 in current_nodes's distance
		temp = (g.getArray())[current_node].getHead();

		while (temp != NULL) {

			if (!visited[temp->data]) {
				queue.enqueue(temp->data);
				visited[temp->data] = true;
				distance[temp->data] = distance[current_node] + 1;
			}
			if (temp->data == destination) {
				return distance[destination];
			}
			temp = temp->nextElement;
		}
	}
	delete[] visited;
	visited = NULL;
	delete[] distance;
	visited = NULL;
	return -1;
}
/**
 * 移除两个顶点的边
 */
void removeEdge(Graph* g, int source, int destination) {
	(g->getArray())[source].deleteByValue(destination);
}


int main()
{
	std::cout << "Hello World!\n";
}

