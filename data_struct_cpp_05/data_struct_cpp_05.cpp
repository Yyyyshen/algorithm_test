// data_struct_cpp_05.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
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

int main()
{
	std::cout << "Hello World!\n";
}

