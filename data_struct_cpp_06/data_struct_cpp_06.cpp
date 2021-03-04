// data_struct_cpp_06.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <assert.h>
#include <string>
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
	//删除节点实现
	bool Delete(Node* currentNode, int value) {
		//空树直接返回
		if (root == NULL) {
			return false;
		}
		//遍历找值
		Node* parent; //To Store parent of currentNode
		while (currentNode != NULL && (currentNode->value != value)) {
			parent = currentNode;
			if (currentNode->value > value)
				currentNode = currentNode->leftChild;
			else
				currentNode = currentNode->rightChild;

		}
		//没找到直接返回
		if (currentNode == NULL) {
			return false;
		}
		else if (currentNode->leftChild == NULL && currentNode->rightChild == NULL) { //要删除的节点无子树
			//1. Node is Leaf Node
			//if that leaf node is the root (a tree with just root)
			if (root->value == currentNode->value) {
				delete root;
				root = NULL;
				return true;
			}
			else if (currentNode->value < parent->value) {
				delete parent->leftChild;
				parent->leftChild = NULL;
				return true;
			}
			else {
				delete parent->rightChild;
				parent->rightChild = NULL;
				return true;
			}
		}
		else if (currentNode->rightChild == NULL) { //要删除的节点只有左子树

			if (root->value == currentNode->value) {
				delete root;
				root = currentNode->leftChild;
				return true;
			}
			else if (currentNode->value < parent->value) {

				delete parent->leftChild;
				parent->leftChild = currentNode->leftChild;
				return true;
			}
			else {
				delete parent->rightChild;
				parent->rightChild = currentNode->leftChild;
				return true;
			}

		}
		else if (currentNode->leftChild == NULL) { //要删除的节点只有右子树

			if (root->value == currentNode->value) {
				delete root;
				root = currentNode->rightChild;
				return true;
			}
			else if (currentNode->value < parent->value) {
				delete parent->leftChild;
				parent->leftChild = currentNode->rightChild;
				return true;
			}
			else {
				delete parent->rightChild;
				parent->rightChild = currentNode->rightChild;
				return true;
			}

		}
		else { //要删除的节点有左右子树
			//Find Least Value Node in right-subtree of current Node
			//找到右子树最小值节点（或左侧子树中值最大的节点），交换后删除，或记录值后删除再赋值
			//这样操作的原因是：该节点是可以替换要删除的节点并仍然保留BST属性的节点之一
			Node* leastNode = findLeastNode(currentNode->rightChild);
			//Set CurrentNode's Data to the least value in its right-subtree
			int tmp = leastNode->value;
			Delete(root, tmp);
			currentNode->value = tmp;
			//Delete the leafNode which had the least value
			return true;
		}

	}
	//找到当前节点下最小节点
	Node* findLeastNode(Node* currentNode) {

		Node* temp = currentNode;
		while (temp->leftChild != NULL) {
			temp = temp->leftChild;
		}

		return temp;
	}
	//删除节点
	bool deleteBST(int value) {
		return Delete(root, value);
	}
	//先序遍历，从根节点开始，先访问左子节点再访问右子节点；按照“中-左-右”顺序遍历
	void preOrderPrint(Node* currentNode) {
		if (currentNode != NULL) {
			cout << currentNode->value << endl;
			preOrderPrint(currentNode->leftChild);
			preOrderPrint(currentNode->rightChild);
		}
	}
	//后序遍历，按照“左-右-中”顺序遍历
	void postOrderPrint(Node* currentNode) {
		if (currentNode != NULL) {
			postOrderPrint(currentNode->leftChild);
			postOrderPrint(currentNode->rightChild);
			cout << currentNode->value << endl;
		}
	}
	//中序遍历，按照“左-中-右”顺序遍历
	void inOrderPrint(Node* currentNode) {
		if (currentNode != NULL)
		{
			inOrderPrint(currentNode->leftChild);
			cout << currentNode->value << endl;
			inOrderPrint(currentNode->rightChild);
		}
	}
};
/**
 * AVL平衡树，是最佳情况的二叉搜索树
 * 搜索复杂度为O(log(n))
 *
 * AVL插入方式与BST相同，但经常会导致不平衡，需要执行旋转
 * 旋转右左旋和右旋
 *
Node U – an unbalanced node
Node C – child node of node U
Node G – grandchild node of node U
四种情况：
Left-Left: Node C is the left-child of Node U, and Node G is left-child of Node C
Left-Right: Node C is the left-child of Node U, and Node G is right-child of Node C
Right-Right: Node C is the right-child of Node U, and Node G is right-child of Node C
Right-Left: Node C is right-child of Node U, and Node G is left-child of Node C

删除节点同理
算法删除
1.删​​除给定的节点号
删除给定的方法与删除BST中的方法相同。
此时，树将变得不平衡，并且要重新平衡树，我们需要执行某种旋转（向左或向右）。
首先，我们需要定义AVL树的结构以及相对于currentNode的一些节点，使用第一步将其插入。
2.导线向上
从给定的节点开始向上遍历，直到找到第一个不平衡节点。
节点U-一个不平衡的节点
节点C-节点U的子节点
节点G-节点U的孙节点
3.重新平衡树
为了重新平衡树，我们将在子树上执行旋转，其中U是根节点。旋转有两种类型（左，右）。根据节点U，C和G的安排，我们遇到了四种不同的情况。
左-左：节点C是节点U的左子节点，节点G是节点C的左子节点
左右：节点C是节点U的左子节点，节点G是节点C的右子节点
右右：节点C是节点U的右子节点，节点G是节点C的右子节点
右左：节点C是节点U的右子节点，节点G是节点C的左子节点

成功完成第一个不平衡节点U的旋转后，向上移动并找到下一个不平衡节点，并执行相同的一系列操作以进行平衡。
继续平衡从第一个Node U到Node U祖先的不平衡节点，直到到达根为止。
在那之后，我们将拥有一个遵循其属性的完全平衡的AVL树。

 */
int val_3 = 3;
/**
 * 红黑树
 * 是自平衡二进制搜索树的另一种类型
 * 但有一些附加功能：
 * 红黑树中的节点被着色为红色或黑色。彩色节点有助于在插入或删除后重新平衡树
 * 属性：
 * 每个节点的颜色为红色或黑色
 * 根始终是彩色的，黑色
 * 两个红色节点不能相邻，即，没有红色父节点可以有一个红色子节点，反之亦然
 * 从根到无的每个路径都包含相同数量的黑色节点
 * NULL节点的颜色被认为是黑色
 * 
 * 对比AVL
 * 尽管从技术上讲，AVL树比“红黑树”更“平衡”，但与红黑树相比，AVL树在插入和删除操作期间需要更多的旋转。
 * 因此，如果搜索密集型应用程序不经常进行插入和删除，使用AVL树，否则使用红黑树。
 */
class Node_RB
{
	int value;
	Node_RB* leftChild;
	Node_RB* rightChild;
	bool isRed;
};
/**
 * 2-3树
 * 2-3树是搜索树的另一种形式，但与BST不同，2-3树是平衡且有序的搜索树，它提供了一种非常有效的存储机制来保证快速操作
 * 一项关键功能是，无论执行多少插入或删除操作，它都能保持平衡。
 * 叶节点始终存在于同一级别上，并且数量很少。
 * 这是为了确保高度不会增加到一定水平，因为所有操作的时间复杂度主要取决于高度。
 * 理想情况下，我们希望高度以对数形式表示，因为随着树的变大，将需要更多时间来执行操作。
 * 在2-3棵树中，树的高度是对数。
 * 2-3-4树，每个节点可以容纳更多key，是2-3树的更高级形式
 */
int val_4 = 0;
/**
 * 取BST中最小值
 */
int findMin(Node* rootNode) {
	// So keep traversing (in order) towards left till you reach leaf node,
	//and then return leaf node's value
	if (rootNode == NULL)
		return -1;

	while (rootNode->leftChild != NULL) {
		rootNode = rootNode->leftChild;
	}
	return rootNode->value;
}
//递归
int findMin_Re(Node* rootNode) {
	// So keep traversing (in order) towards left till you reach leaf node,
	//and then return leaf node's value
	if (rootNode == NULL)
		return -1;
	else if (rootNode->leftChild == NULL)
		return rootNode->value;
	else
		return findMin_Re(rootNode->leftChild);
}
/**
 * 取BTS中第k个最小值
 */
class ArrayList {
private:
	int* arr;
	int num_elements;
	int capacity;
public:
	ArrayList(int size) {
		arr = new int[size];
		num_elements = 0;
		capacity = size;
	}

	void insert(int val) {
		if (num_elements <= capacity) {
			arr[num_elements] = val;
			num_elements++;
		}
		else {
			resize();
			arr[num_elements] = val;
			num_elements++;
		}
	}

	void resize() {
		int* tempArr = new int[capacity * 2];
		capacity *= 2;

		for (int i = 0; i < num_elements; i++) {
			tempArr[i] = arr[i];
		}
		delete arr;
		arr = tempArr;
	}

	int length() {
		return num_elements;
	}

	void print() {
		for (int i = 0; i < num_elements; i++)
			cout << arr[i] << " ";
		cout << endl;
	}

	int getAt(int index) {
		return arr[index];
	}
};
//中序遍历有序填入数组
void inOrderTraversal(Node* rootNode, ArrayList* result) {

	if (rootNode != NULL) {

		inOrderTraversal(rootNode->leftChild, result);
		result->insert(rootNode->value);
		inOrderTraversal(rootNode->rightChild, result);

	}
}
//排序树，放入数组
int findKthMax(Node* rootNode, int k, int nodes) {
	if (k <= 0) {
		return -1;
	}
	//Perform In-Order Traversal to get sorted array. (ascending order)
	//Return value at index [length - k]
	ArrayList* result = new ArrayList(nodes);
	inOrderTraversal(rootNode, result);
	return result->getAt(nodes - k);
}
//递归
static int  counter = 0; //全局计数，找到最大值后往前遍历并计数
Node* findKthMaxRecursive(Node* root, int k) {
	if (root == nullptr || counter >= k) {
		return nullptr;
	}
	//Recursively reach the right-most node (which has the highest value)
	Node* node = findKthMaxRecursive(root->rightChild, k);

	if (counter != k) {
		//Increment counter if kth element is not found
		counter++;
		node = root;
	}
	//Base condition reached as kth largest is found
	if (counter == k) {
		return node;
	}
	else {
		//Traverse left child if kth element is not reached
		return findKthMaxRecursive(root->leftChild, k);
	}
}
//used to call for the recursive algorithm
int findKthMax_Re(Node* root, int k) {
	Node* node = findKthMaxRecursive(root, k);
	if (node != nullptr)
		return node->value;
	return -1;
}
/**
 * 在BST中寻找指定节点所有祖先节点
 */
bool recur(Node* rootNode, int k, string* result) {

	//base cases
	if (rootNode == NULL)
		return false;
	else if (rootNode->value == k)
		return true;
	else {
		//To check if target is present in either left or right subtree of currentNode
		if (recur(rootNode->leftChild, k, result) || recur(rootNode->rightChild, k, result))
		{
			*(result) = *(result)+to_string(rootNode->value) + ",";
			return true;
		}
	}

	return false;
}
//递归
string findAncestors(Node* rootNode, int k) {
	string* result = new string;
	recur(rootNode, k, result);
	return *(result);
}
//迭代
string findAncestors(Node* rootNode, int k) {

	if (rootNode == NULL)
		return "";

	string ancestors = "";
	Node* currentNode = rootNode;

	while (currentNode != NULL) {
		if (k > currentNode->value) {
			ancestors += to_string(currentNode->value) + ",";
			currentNode = currentNode->rightChild;
		}
		else if (k < currentNode->value) {
			ancestors += to_string(currentNode->value) + ",";
			currentNode = currentNode->leftChild;
		}
		else  // when k == currentNode.value
			return ancestors;
	}
	return "";
}
/**
 * 求BST高度
 */
int findHeight(Node* rootNode) {
	if (rootNode == NULL)
		return -1;
	else {
		// Find Height of left subtree and then right subtree
		// Return greater height value of left or right subtree (plus 1)
		int leftHeight = findHeight(rootNode->leftChild);
		int rightHeight = findHeight(rootNode->rightChild);

		if (leftHeight > rightHeight)
			return leftHeight + 1;
		else
			return rightHeight + 1;
	}
}
/**
 * 找出与根节点距离为k的所有节点
 */
void findK(Node* root, int k, string* result) {

	if (root == NULL)
		return;

	if (k == 0) {
		*(result) = *(result)+to_string(root->value) + ",";
	}
	else {
		//Decrement k at each step till you reach at the leaf node
		// or when k == 0 then append the Node's data into result string
		findK(root->leftChild, k - 1, result);
		findK(root->rightChild, k - 1, result);
	}
}
string findKNodes(Node* root, int k) {

	string* result = new string;
	findK(root, k, result);

	return *(result);
}

int main()
{
	std::cout << "Hello World!\n";
}
