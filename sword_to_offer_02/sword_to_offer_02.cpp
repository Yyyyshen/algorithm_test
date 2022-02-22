// sword_to_offer_02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

//
//数据结构
//

//
//数组
// 数组名是一个指针，指向第一个元素
int GetSize(int data[]) { return sizeof(data); }
void
test_raw_arr()
{
	int data[] = { 1,2,3,4,5 };
	int* p_data = data;
	std::cout << "data[] size : " << sizeof(data) << std::endl	//20
		<< "p_data size : " << sizeof(p_data) << std::endl		//4
		<< "GetSize(data[]) : " << GetSize(data) << std::endl;	//4 当数组作为函数参数传递时，自动退化成同类型指针
}
//
//面试题：数组中重复数字（缺失数字）
// 长度n的数组，数字范围0~n-1，某些数字是重复的
class DuplicateNumbers
{
public:
	static vector<int> find_dup_num(/* const */vector<int> nums)
	{
		vector<int> ret;
		//参数检查
		if (nums.empty() || nums.size() <= 1)
			return ret;
		//检查输入是否有问题（若求缺失数字则不需要这一步）
		for (auto num : nums)
			if (num <0 || num > nums.size() - 1)
				return ret;
		//方案1，排序后遍历一遍求结果，时间O(nlogn)，空间O(1)，输入被修改
		sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size() - 1; ++i)
			if (nums[i] == nums[i + 1])
				ret.push_back(nums[i]);
		//方案2，hashmap辅助记录，时间O(n)，空间O(n)，输入未修改
		unordered_map<int, int> memo;
		for (auto num : nums)
		{
			if (memo.find(num) != memo.end())
				ret.push_back(num);
			else
				++memo[num];
		}
		//方案3，根据数值与索引位置原地循环排序，时间O(n)，空间O(1)，输入被修改
		int i = 0;
		while (i < nums.size())
		{
			if (nums[i] >= 0 && nums[i] < nums.size() && nums[i] != nums[nums[i]])
				swap(nums[i], nums[nums[i]]);
			else
				++i;
		}
		for (i = 0; i < nums.size(); ++i)
			if (nums[i] != i)
				ret.push_back(nums[i]);
		//方案4，借助二分思路，取中间数m，计数1~m和m+1~n之间的数字，哪边数字多重复的就在哪边
		//时间O(nlogn)，空间O(1)，输入不被修改
		//问题：如果两范围各重复一个，怎么区分？

		return ret;
	}
};
void test_DuplicateNumbers()
{
	auto ret = DuplicateNumbers::find_dup_num({ 2,3,1,0,2,5,3 });
	cout << "test_DuplicateNumbers ret: ";
	for (auto num : ret)
		cout << num << " ";
	cout << endl;
}
// 
//例
// 二维数组中查找
bool
find_num_in_2d_arr(int* matrix, int rows, int columns, int number)
{
	//正常遍历
	if (matrix == nullptr) return false;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
			if (matrix[i * j + j] == number)
				return true;
	}

	return false;

	//加上条件：每行、每列都是递增排列。
	//普通遍历可行，但可以优化

	//选取数组右上角数字，如果等于要查找的数，过程结束；大于查找数字，其所在列可以忽略；小于则可以忽略所在行

	if (matrix != nullptr && rows > 0 && columns > 0)			//参数检查
	{
		int row = 0, column = columns - 1;
		while (row < rows && column >= 0)
		{
			if (matrix[row * column + column] == number)
				return true;
			else if (matrix[row * column + column] > number)
				--column;
			else
				++row;
		}
	}

	return false;
}
//

//
//字符串
// C/C++每个字符串以'\0'结尾，用于寻找尾部，有额外一字节占用
// 常量字符串放到单独内存区域，指针赋值给相同常量字符串时，指向相同内存
void test_str()
{
	char str1[] = "helloworld";
	char str2[] = "helloworld";
	//此过程中，数组各自分配空间，并且把字符串复制进去，所以不同
	cout << "str1 and str2 is: " << (str1 == str2 ? "same" : "diff") << endl;//diff
	char* str3 = (char*)"helloworld";
	char* str4 = (char*)"helloworld";
	//此过程中，指针无须分配空间，而是把他们指向常量字符串"helloworld"所在内存地址，所以相同
	cout << "str3 and str4 is: " << (str3 == str4 ? "same" : "diff") << endl;//same
}
// 
//面试题：替换空格
// 在Url中，特殊字符（空格、#、<等）需要根据ASCII码替换为%形式的字符
// 例如空格，ASCII码32，转16进制0x20，也就是转换为%20
// 编写一个函数替换一串字符中的空格
// 
// 分析
// 首先明确，原地替换还是可以使用额外空间
// 原地替换的话，空格为一个字符，替换后是三个字符
// 需要字符串后有空余空间，且每次替换后其后字符都要后移
void replace_spaces()
{
	char input[25] = "hello world";//预留后续处理空间
#if 0//暴力解，遍历，遇到空格把后续所有字符后移，之后替换，时间复杂度O(n^2)
	for (int i = 0; i < sizeof(input); ++i)
	{
		if (input[i] == ' ')
		{
			for (int j = strlen(input) + 1; j >= i + 2; --j)
				input[j] = input[j - 2];
			input[i] = '%';
			input[i + 1] = '2';
			input[i + 2] = '0';
		}
	}
	cout << input << endl;
#endif
	//更优解
	// 两点法，计算总共需要后移的位数，一个点指向最终结尾，一个指向当前结尾，从后向前依次拷贝或替换
	// 重点
	// 是否想到字符串替换变长问题，内存越界
	// 是否能想到用从后向前遍历，避免每次处理时都把之后所有字符重复挪动一遍
	// 两个有序数组合并问题，如果要求原地合并，也可以同理，从后向前减少移动次数
	if (input == nullptr /* || length <= 0 */) return;//参数检查
	int count = 0;
	for (int i = 0; i < strlen(input); ++i)
		if (input[i] == ' ')
			count += 2;
	int p1 = strlen(input);
	int p2 = p1 + count;
	if (p1 == p2) return;//没有空格
	//还可以检查一下，p2是否大于给定长度
	/* if (p2 > length) return; */
	while (p1 != p2)
	{
		char cur = input[p1--];
		if (cur == ' ')
		{
			input[p2--] = '0';
			input[p2--] = '2';
			input[p2--] = '%';
		}
		else
			input[p2--] = cur;
	}
	cout << input << endl;
}
//

//
//链表
//
class ListNode
{
public:
	int value;
	ListNode* next;
	ListNode(int val) :value(val), next(nullptr) {}
};
//面试题：从尾到头打印链表
// 分析，问清条件，是否改变输入
// 如果可以，则反转链表，打印后再反转回来
// 若打印过程中要求完全不改变链表结构，则借助一个栈，遍历过程中入栈
class PrintLinkedListReversedOrder
{
public:
	static void print(ListNode* head)
	{
		stack<ListNode*> st;
		ListNode* cur = head;
		while (cur != nullptr)
		{
			st.push(cur);
			cur = cur->next;
		}
		while (!st.empty())
		{
			ListNode* top = st.top();
			cout << top->value << " ";
			st.pop();
		}
		cout << endl;
	}
	//另外，调用栈本身也可以起到相同的作用，也就是递归
	static void printRecursive(ListNode* head)
	{
		if (head == nullptr)
			return;
		printRecursive(head->next);
		cout << head->value << " ";
	}
};
void test_PrintLinkedListReversedOrder()
{
	ListNode* head = new ListNode(0);
	head->next = new ListNode(1);
	head->next->next = new ListNode(2);
	head->next->next->next = new ListNode(3);
	//递归只是代码简洁，但如果层级过深，会栈溢出，还是基于栈的循环实现更好
	PrintLinkedListReversedOrder::printRecursive(head);
}
//  

//
//树
// 基本都是二叉树
// 三种根序遍历方式 前序、中序、后序
// 两种维度遍历 深度优先、广度优先
// 
// 二叉树特例
// 二叉搜索树、堆、红黑树
// 
class tree_node
{
public:
	int value;
	tree_node* left;
	tree_node* right;
	tree_node(int val) :value(val), left(nullptr), right(nullptr) {}
};
//面试题：根据二叉树的前序、中序遍历重建二叉树
// 分析，根据前序遍历，第一个元素为根元素
// 找根元素在中序遍历中的位置，其左侧的所有元素为左子树元素
// 后续依次递归
class CtorBinaryTree
{
public:
	static tree_node* ctor(const vector<int>& preorder, const vector<int>& inorder)
	{
		if (preorder.empty() || inorder.empty() || preorder.size() != inorder.size())
			return nullptr;
		return ctor_core(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size());
	}
	static tree_node* ctor_core(const vector<int>& preorder, const vector<int>& inorder,
		int startpre, int endpre, int startin, int endin)
	{
		//前序遍历第一个元素为根节点
		int rootval = preorder[startpre];
		//构建根节点
		tree_node* root = new tree_node(rootval);
		//已经没有左右子树了（到达叶子节点），返回构建的节点
		if (startpre == endpre)
		{
			if (startin == endin && preorder[startpre] == inorder[startin])
				return root;
			else
				throw std::exception("error input");
		}
		//否则在中序遍历中找根节点的位置
		int rootinorder = startin;
		while (rootinorder <= endin && inorder[rootinorder] != rootval)
			++rootinorder;
		//检查是否找到
		if (rootinorder == endin && inorder[rootinorder] != rootval)
			throw std::exception("error input");
		//确定左右子树两数组的位置
		int leftlen = rootinorder - startin;
		int leftendpre = startpre + leftlen;
		//构建左右子树
		if (leftlen > 0)
			root->left = ctor_core(preorder, inorder, startpre + 1, leftendpre, startin, rootinorder - 1);
		if (leftlen < endpre - startpre)
			root->right = ctor_core(preorder, inorder, leftendpre + 1, endpre, rootinorder + 1, endin);
		//返回最终结果
		return root;
	}
	static void print_tree(tree_node* root)
	{
		//层序遍历输出
		if (root == nullptr) return;
		queue<tree_node*> q;
		q.push(root);
		while (!q.empty())
		{
			int level_size = q.size();
			for (int i = 0; i < level_size; ++i)
			{
				tree_node* node = q.front();
				q.pop();
				cout << node->value << " ";
				if (node->left != nullptr)
					q.push(node->left);
				if (node->right != nullptr)
					q.push(node->right);
			}
			cout << endl;
		}
	}
};
void test_CtorBinaryTree()
{
	tree_node* root = CtorBinaryTree::ctor({ 1,2,4,7,3,5,6,8 }, { 4,7,2,1,5,3,8,6 });
	CtorBinaryTree::print_tree(root);
}
//  
//

int main()
{
	std::cout << "Hello World!\n";
}
