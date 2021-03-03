// data_struct_cpp_06.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <assert.h>
/**
 * 树
 */
using namespace std;
/**
基本特性、术语

根节点：没有父节点的节点。
子节点：链接到上层节点（父节点）的节点。
父节点：链接到一个或多个子节点的节点。
兄弟节点：共享同一父节点的节点。
叶子节点：没有任何子节点的节点。
祖先节点：从节点d到根节点的路径上的 节点。祖先节点包括节点d的父母，祖父母等。

子树：子树是树的一部分，可以单独视为完整的树。树中的任何节点以及它下面的所有连接节点组成原始树的子树。
节点的度数：节点的子级总数。
路径的长度：路径中的边数。
节点n的深度：从节点n到根节点的路径长度。根节点的深度为0。
节点的级别n：（节点的深度）+1。
节点的高度n：从n到最深后代的路径长度。因此，树本身的高度是根节点的高度，叶节点的高度始终为0。
树的高度：其根节点的高度。
 */
int val_0 = 0;
/**
 * 二叉树
 * 完全（complete）二叉树，除了最后一级节点，都被填充
 * 完整（full）二叉树，每个节点有0或2个子节点
 * 完美（perfect）二叉树，除最后一级节点，都有两个子节点
 */
int val_1 = 1;
/**
 * 树的平衡
对于树中的每个节点，右子树和左子树的高度之差最大为一，则二叉树是高度平衡的

高级算法来确定一棵树的高度平衡

从叶节点开始，然后移向根。
在遍历树的同时，计算每个节点的左子树和右子树的高度。叶节点的高度始终为0。
在每个节点处，检查左右子树的高度差是否大于1，如果大于1，则表明该树不平衡。
如果您已经完全遍历了树并且没有满足上述条件，则树是平衡的。
 */
int val_2 = 2;
/**
 * 二叉搜索树
 * 左子树中节点的值应等于或小于当前节点的值。同样，右子树中所有节点的值应等于或大于当前节点的值。
 */
class Node {
public:
	int value;
	Node* leftChild;
	Node* rightChild;
	//树节点
	Node() {
		value = 0;
		leftChild = NULL;
		rightChild = NULL;
	}
	Node(int val)
	{
		value = val;
		leftChild = NULL;
		rightChild = NULL;
	}
};
//基本结构
class BinarySearchTree {
	Node* root;
public:
	BinarySearchTree(int rootValue) {
		root = new Node(rootValue);
	}
	BinarySearchTree() {
		root = NULL;
	}
	void inOrderPrint(Node* currentNode) {
		if (currentNode != NULL) {
			inOrderPrint(currentNode->leftChild);
			cout << currentNode->value << endl;
			inOrderPrint(currentNode->rightChild);
		}
	}
	Node* getRoot() {
		return root;
	}
	/*插入值
	从根节点开始
	检查要插入的值是否大于根/当前节点的值
	如果是，则对当前子节点的右子树重复上述步骤，否则对当前节点的左子树重复上述步骤。
	重复直到找到没有右/左子节点的节点。在此处插入给定值，并相应地更新父节点。
	*/
	Node* insert(Node* currentNode, int val) {
		if (currentNode == NULL) {
			return new Node(val);
		}
		else if (currentNode->value > val) {

			currentNode->leftChild = insert(currentNode->leftChild, val);

		}
		else {
			currentNode->rightChild = insert(currentNode->rightChild, val);
		}

		return currentNode;

	}
	//递归
	void insertBST_re(int value) {
		if (getRoot() == NULL) {
			root = new Node(value);
			return;
		}
		insert(this->getRoot(), value);
	}
	//迭代
	void insertBST_it(int val) {
		if (getRoot() == NULL) {
			root = new Node(val);
			return;
		}
		//starting from the root
		Node* currentNode = root;
		Node* parent;
		//while we get to the null node
		while (currentNode) {
			parent = currentNode; //update the parent
			if (val < currentNode->value) {
				//if newValue < currentNode.val,
				//iterate to the left subtree
				currentNode = currentNode->leftChild;
			}
			else {
				//if newValue >= currentNode.val,
				//iterate to the right subtree
				currentNode = currentNode->rightChild;
			}
		}
		//by now, we will have the parent of the null
		//node where we have to insert the newValue
		if (val < parent->value) {
			//if newValue < parent.val
			//insert into the leftChild
			parent->leftChild = new Node(val);
		}
		else {
			//if newValue >= parent.val
			//insert into the rightChild
			parent->rightChild = new Node(val);
		}

	}
	//搜索指定值
	Node* searchBST(int value) {
		//let's start with the root 
		Node* currentNode = root;
		while (currentNode && (currentNode->value != value)) {
			//the loop will run until the currentNode IS NOT null
			//and until we get to our value
			if (value < currentNode->value) {
				//traverse to the left subtree
				currentNode = currentNode->leftChild;
			}
			else { //traverse to the right subtree
				currentNode = currentNode->rightChild;

			}

		}
		//after the loop, we'll have either the searched value
		//or null in case the value was not found
		return currentNode;
	}
};

int main()
{
	std::cout << "Hello World!\n";
}
