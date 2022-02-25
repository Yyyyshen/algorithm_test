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
	tree_node* parent;
	tree_node(int val) :value(val), left(nullptr), right(nullptr), parent(nullptr) {}
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
//面试题：给一个树节点，找出二叉树中序遍历的下一个节点
// 分析，给定节点包含父节点指针，不知道树根，所以不是用正常的中序递归遍历
class GetNextNode
{
public:
	tree_node* solution(tree_node* node)
	{
		tree_node* next = nullptr;
		//参数检查
		if (node == nullptr)
			return next;
		//最简单情况，有右子树，那么找右子树的最左节点
		if (node->right != nullptr)
		{
			tree_node* tmp = node->right;
			while (tmp->left != nullptr)
				tmp = tmp->left;
			next = tmp;
		}
		//没右子树，则向上找一个是其父节点左子节点的节点，下一个节点就是其父节点
		else if (node->parent != nullptr)
		{
			tree_node* cur = node;
			tree_node* pcur = node->parent;
			//也可能自己就是其父节点的左子节点
			while (pcur != nullptr && cur == pcur->right)
			{
				cur = pcur;
				pcur = cur->parent;
			}
			//找到的父节点就是下一个节点
			next = pcur;
		}
		//如果没有进两种情况，那就是树的最后一个节点，没有下个节点
		return next;
	}
};
//

//
//栈和队列
// 
//面试题：两个栈实现队列
class QueueWithTwoStack final
{
public:
	QueueWithTwoStack() = default;
	~QueueWithTwoStack() = default;
public:
	void push(int val)
	{
		//每次把所有元素压到另一个栈
		while (!q.empty())
		{
			helper.push(q.top());
			q.pop();
		}
		//把新元素压到栈底，也就相当于队列尾
		q.push(val);
		//把辅助栈里所有元素再压回来，每次保证栈顶是队列头
		while (!helper.empty())
		{
			q.push(helper.top());
			helper.pop();
		}
	}
	int pop()
	{
		int top = q.top();
		q.pop();
		return top;
	}
	//上面方法每次都要搬两次所有元素，实质是只用到了一个栈，另一个栈只发挥了临时变量的作用
	//优化，只在有需要的时候搬移一次
	void push2(int val)
	{
		//每次往一个栈里压
		q.push(val);
	}
	int pop2()
	{
		//弹出时，把所有元素往辅助栈搬一次，就是队列的顺序了
		//需要注意的就是，必须辅助栈为空，也就是每轮所有元素都处理完，才搬过来，否则顺序就被改变了
		if (helper.empty())
		{
			while (!q.empty())
			{
				helper.push(q.top());
				q.pop();
			}
		}
		//验证一下栈是否是空
		if (helper.empty())
			throw "queue is empty";
		//正常从辅助栈顶依次返回，直到为空，把下一批数据再压进来，这样减少了很多搬移次数
		int top = helper.top();
		helper.pop();
		return top;
	}
private:
	stack<int> q;
	stack<int> helper;
};
//两个队列实现栈是类似的思路
// 每次往一个队列入队
// 弹栈时，将插入元素的队列元素依次出队并插入另一个队列，直到只剩一个元素
// 再插入时，往已经有元素的队列中插入
// 以这个逻辑进行
//

//
//算法和数据操作
// 归并排序、快速排序、二分查找 熟练
class MergeSort final
{
public:
	//归并是先分再排
	static void run(vector<int>& arr)
	{
		sort_impl(arr, 0, arr.size() - 1);
	}
private:
	//先划分块
	static void sort_impl(vector<int>& arr, int p, int r)
	{
		//不能再分
		if (p >= r)
			return;
		//按中点分割
		int q = (p + r) / 2;
		//继续对两边划分
		sort_impl(arr, p, q);
		sort_impl(arr, q + 1, r);
		//合并
		merge_impl(arr, p, q, r);
	}
	//有序合并两部分数组
	static void merge_impl(vector<int>& arr, int p, int q, int r)
	{
		vector<int> tmp(r - p + 1);
		int i, j, k;
		//相当于两点法合并两个有序数组
		for (i = p, j = q + 1, k = 0; i <= q && j <= r;)
		{
			if (arr[i] < arr[j])
				tmp[k++] = arr[i++];
			else
				tmp[k++] = arr[j++];
		}
		//处理可能某一边多出来的部分
		while (i <= q)
			tmp[k++] = arr[i++];
		while (j <= r)
			tmp[k++] = arr[j++];
		//把合并结果应用回原数组
		copy(tmp.begin(), tmp.end(), arr.begin() + p);
	}
};
class QuickSort final
{
public:
	//快排是先排再分
	static void run(vector<int>& arr)
	{
		sort_impl(arr, 0, arr.size() - 1);
	}
private:
	static void sort_impl(vector<int>& arr, int start, int end)
	{
		//不能再分
		if (start >= end)
			return;
		//简单排序后找分界点
		int div = partition(arr, start, end);
		//在分界点两边再排序
		if (div > start)
			sort_impl(arr, start, div - 1);
		if (div < end)
			sort_impl(arr, div + 1, end);
	}
	static int partition(vector<int>& arr, int start, int end)
	{
		//随机/任取一个分界，以取最后一个为例
		int i = start, div = start;
		for (; i < end; ++i)
		{
			//比标志点小的，往左半边放，交换后大的自动处于后半部分
			if (arr[i] < arr[end])
			{
				swap(arr[i], arr[div]);
				++div;
			}
		}
		//把标志点换到正确位置
		swap(arr[div], arr[end]);
		return div;
	}
};
class BinarySearch final
{
public:
	//二分
	static int run(const vector<int>& arr, int val)
	{
		if (arr.empty()) return -1;
		return search_impl(arr, val);
	}
private:
	static int search_impl(const vector<int>& arr, int val)
	{
		int start = 0, end = arr.size() - 1, mid = 0;
		while (start <= end)
		{
			//找中点，注意加法可能溢出，另外注意位移符优先级
			mid = start + ((end - start) >> 1);
			if (arr[mid] == val)
				return mid;
			//考虑升降序
			if (arr[0] < arr[arr.size() - 1])
			{
				if (arr[mid] > val)
					end = mid - 1;
				else
					start = mid + 1;
			}
			else
			{
				if (arr[mid] > val)
					start = mid + 1;
				else
					end = mid - 1;
			}
		}
		return -1;
	}
};
// 
// 快排是平均效率最好，O(nlogn)
// 但也可能退化，要根据具体情况分析
//可能的面试过程
// 要求实现排序算法，要求效率O(n)
// 此时应问好，什么使用场景，是否可使用辅助内存
// 例如对员工年龄排序，可以使用O(n)大小的空间
// 那么可以分析，员工年龄范围并不大，可以使用桶排序
// 定义一个大小100的数组，每个元素是一个员工对象数组/链表
// 这样数组的索引就自然的将员工年龄排序了
// 只需要遍历一遍员工，根据年龄放到对应索引就排好了
// 
//面试题：旋转数组的最小数字
// 一个递增数组经过旋转，找到其最小元素
// （最基本的是遍历一遍，时间O(n)，但可以更快）
// 分析，旋转后最小元素有一个特性，它是数组中唯一一个比前一个元素小的
// 另外，可以使用二分，根据递增，可知旋转点一定存在于右端点小于左端点的区间
// 时间复杂度降到O(logn)
class FindSmallestInRotatedArray final
{
public:
	static int run(const vector<int>& arr)
	{
		if (arr.empty()) return -1;
		int start = 0, end = arr.size() - 1, mid = 0;
		while (start < end)
		{
			mid = start + ((end - start) >> 1);
			//比较前后各一个元素，可知结果
			if (mid > start && arr[mid] < arr[mid - 1])
				return arr[mid];
			if (mid < end && arr[mid] > arr[mid + 1])
				return arr[mid + 1];
			//重复元素判断
			if (arr[mid] == arr[start] && arr[mid] == arr[end])
			{
				//分别移动一次，但可以顺便看看是否能从移动的两个点找到结果
				if (arr[start] > arr[start + 1])
					return arr[start + 1];
				++start;
				if (arr[end] < arr[end - 1])
					return arr[end];
				--end;
			}
			//判断最小元素所在位置
			else if (arr[start] < arr[mid] || (arr[start] == arr[mid] && arr[mid] > arr[end]))
				start = mid + 1;
			else
				end = mid - 1;
		}
		//没在中间找到，说明是旋转0或数组大小倍数次，最小的是首元素
		return arr[0];
	}
};
//
//递归
// 优点 代码简洁，在树遍历应用中更容易实现
// 缺点 每次调用都是对栈空间的占用，分配、传参等操作也增加时间，层级过多时还会栈溢出
// 
//面试题：斐波那契数列
class Fibonacci final
{
public:
	static int recursive(int n)
	{
		//递归方式简单，但效率低，因为根据递归树，很多支路是重复的
		if (n <= 0) return 0;
		if (n == 1) return 1;
		return recursive(n - 1) + recursive(n - 2);
	}
	//迭代方式
	static int iterative(int n)
	{
		if (n <= 0) return 0;
		if (n == 1) return 1;
		//记录每次结果
		int first = 0, second = 1;
		int fibN = 0;
		for (int i = 2; i <= n; ++i)
		{
			fibN = first + second;
			first = second;
			second = fibN;
		}
		return fibN;
	}
	//变种，跳台阶，N阶台阶，一次走一阶或两阶，多少种走法；本质上还是f(n) = f(n-1)+f(n-2);
	static int jump(int n)
	{
		if (n <= 0) return 0;
		if (n == 1) return 1;
		//也可用额外空间记录前面数字
		vector<int> fib = { 1,1 };//此例应从1开始，而不是0
		for (int i = 2; i <= n; ++i)
			fib.push_back(fib[i - 1] + fib[i - 2]);
		return fib[n];
	}
};
// 
//回溯法
// 对于每个步骤都有多个选项的问题，可以使用回溯进行枚举操作
// 
//面试题：矩阵中的路径
// 判断一个矩阵中是否存在一条包含某字符串所有字符的路径
// 分析
// 在矩阵任选一个格子作为起点，找相邻的几个格子，并做记录已经到达过的格子
class HasPath final
{
public:
	static bool run(const vector<vector<int>>& matrix, const char* str)
	{
		//参数检查，还可以检查各子数组长度是否相等
		if (matrix.empty() || str == nullptr) return false;
		//记录到达过的位置
		vector<vector<bool>> visited(matrix.size(), vector<bool>(matrix[0].size(), false));
		//记录路径长，用于判断字符串各字符
		int len = 0;
		//从所有格子作为起点分别计算一次
		for (int row = 0; row < matrix.size(); ++row)
			for (int col = 0; col < matrix[0].size(); ++col)
				if (core(matrix, row, col, str, len, visited))
					return true;
		return false;
	}
private:
	static bool core(const vector<vector<int>>& matrix, int row, int col,
		const char* str, int& len, vector<vector<bool>>& visited)
	{
		//找到字符串尾，返回true
		if (str[len] == '\0') return true;
		bool ret = false;
		//在矩阵范围内、当前字母所在路径长符合字符串中位置、且未访问过，可以继续
		if (row >= 0 && row < matrix.size() && col >= 0 && col < matrix[0].size()
			&& matrix[row][col] == str[len]
			&& visited[row][col] == false)
		{
			//路径长+1
			++len;
			//本位置记录为已访问
			visited[row][col] = true;
			//往上下左右四个方向找，参数判断会在下一层验证
			ret = core(matrix, row - 1, col, str, len, visited)
				|| core(matrix, row + 1, col, str, len, visited)
				|| core(matrix, row, col - 1, str, len, visited)
				|| core(matrix, row, col + 1, str, len, visited);
			//若没找到，路径长减回来，标记未访问，保证当前栈层状态
			if (ret == false)
			{
				--len;
				visited[row][col] = false;
			}
		}
		return ret;
	}
};
// 
//面试题：机器人运动范围
// m*n的方格，机器人从坐标(0,0)开始，每次可以上下左右走一格
// 但不能进入行列坐标数位之和大于k的格子
// 分析
// 与上题类似，回溯
class RobotMoving final
{
public:
	//并不真正需要矩阵数组，只是给定一个数组范围就可以解此题了
	static int run(int k, int m, int n)
	{
		//参数检查
		if (k < 0 || m <= 0 || n <= 0)
			return 0;
		//标记已到达
		vector<vector<bool>> visited(m, vector<bool>(n, false));
		return count(k, m, n, 0, 0, visited);
	}
private:
	static int count(int k, int m, int n,
		int x, int y, vector<vector<bool>>& visited)
	{
		int ret = 0;
		//满足当前坐标满足条件才继续移动
		if (check(k, m, n, x, y, visited))
		{
			//标记已访问
			visited[x][y] = true;
			cout << "(" << x << "," << y << ")" << endl;
			//往四个方向走
			ret = 1 + count(k, m, n, x - 1, y, visited)
				+ count(k, m, n, x + 1, y, visited)
				+ count(k, m, n, x, y - 1, visited)
				+ count(k, m, n, x, y + 1, visited);
		}
		return ret;
	}
	//检查是否坐标数位和小于等于k
	static bool check(int k, int m, int n,
		int x, int y, vector<vector<bool>>& visited)
	{
		//矩阵范围验证、数位和验证、是否访问过验证
		if (x >= 0 && x < m && y >= 0 && y < n
			&& digit_sum(x) + digit_sum(y) <= k
			&& visited[x][y] == false)
			return true;
		return false;
	}
	//计算数位和
	static int digit_sum(int num)
	{
		int ret = 0;
		while (num > 0)
		{
			ret += num % 10;
			num /= 10;
		}
		return ret;
	}
};
// 
//动态规划和贪婪算法
// 若一个问题是求最优解，且该问题能分解成子问题
// 子问题之间又有重叠，可以考虑动态规划
// 若问题除了动态规划还暗示可以用贪婪，则需要从数学角度证明贪婪的正确性
// 
//面试题：剪绳子
// 长度为n的绳子，剪成若干段，求怎么剪使各段绳子乘积最大
class CutRopeMaxProduct final
{
public:
	//动态规划解法，分解为子问题
	static int run_dp(int length)
	{
		//长度要大于1才会有乘积
		if (length < 2) return 0;
		//长度为2，剪成两段1
		if (length == 2) return 1;
		//长度为3，剪成两段1和2
		if (length == 3) return 2;
		//存放乘积最大结果
		vector<int> products(length + 1, 0);
		//预设一些短绳子长度
		for (int i = 0; i <= 3; ++i)
			products[i] = i;
		//每次剪绳子都是把一段分为两段，求两段的乘积最大
		//抽象为子问题
		for (int i = 4; i <= length; ++i)
			//一分为2，只需要算到一半的数量，后面半边是重复的
			for (int j = 1; j <= i / 2; ++j)
				products[i] = max(products[i], products[j] * products[i - j]);
		//数组每个元素都是记录索引值长度的最大乘积情况
		return products[length];
	}
	//贪婪算法
	static int run_greedy(int length)
	{
		//一样的基本参数检查和简单解
		if (length < 2) return 0;
		if (length == 2) return 1;
		if (length == 3) return 2;
		//n>=5时，尽可能多剪长度为3的绳子，剩下长度4时，剪成两段2
		int len3nums = length / 3;
		//如果能剪到1，那最后一段4应该剪成2*2，而不是3*1
		if (length - len3nums * 3 == 1)
			--len3nums;
		int len2nums = (length - len3nums * 3) / 2;
		return (int)pow(3, len3nums) * (int)pow(2, len2nums);
		//正确性证明
		// n>=5时
		// 2(n-2) 和 3(n-3) 都大于n，所以绳子长度大于等于5时，剪成3或者2的段
		// 又可推出 3(n-3)>=2(n-2)，所以尽可能多剪3
		// 长度为4时，2*2>1*3，剪成2*2最好
	}
};
// 
//位运算
// 与&、或|、异或^、左移<<、右移>>
//
//面试题：二进制中1的个数
// 实现一个函数，输入整数，输出其二进制表示中1的个数
class CountOneInBinary
{
public:
	static int run(int number)
	{
		int ret = 0;
		//先算出数字在二进制中多少位
		int n = number, bits = 0;
		while (n != 0)
		{
			n = n >> 1;
			bits++;
		}
		//用一个标志按位对比
		int flag = 1;
		for (int i = 0; i < bits; ++i)
		{
			if ((number & flag) != 0)
				ret++;
			flag = flag << 1;
		}
		return ret;
	}
	//更巧妙的解法
	// 一个整数不是0的话，二进制中一定有1
	// 假设最右一位是1，这个数字减1，最右就是0
	// 其他位保持不变，最后一位相当于取反操作
	// 继续分析，最后一位是0，假设下一个最右的1在m位
	// 继续减1时，m位变0，m右边位全变1
	// 所以
	// 一个整数减1，在和原数做与运算，会把整数最右边的1变为0
	// 那么有多少个1，就能进行多少次这样的运算
	static int run_smart(int number)
	{
		int ret = 0;
		while (number!=0)
		{
			++ret;
			number = (number - 1) & number;
		}
		return ret;
	}
};
//

//
//本章总结
// 基础知识：编程语言、数据结构、算法
// 语言上注重概念、代码分析、编程
// 数据结构重点为数组和字符串、二叉树、栈和队列
// 算法重点为二分查找、归并和快排、回溯、动态、贪心
// 位运算一般用于巧妙的数字题解法
//

int main()
{

}
