﻿// datastruct_and_algorithm_02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//
//第二阶段
// 散列表
// 二叉树
// 堆和堆排序
// BF / RK字符串匹配算法
// Trie树
// 图的表示
// 深度广度优先搜索
// 

//
//散列表
// 
//问题引入：word拼写检查功能
// 
//散列思想
// 散列表利用的是数组支持按下标随机访问数据的特性（时间复杂度O(1)）
// 通过散列函数，把元素键值映射为下标，然后将数据存储在数组对应的下标
// 查询时，同样从散列函数，将键值转为下标，从对应数组下标位置取数据
// 
//散列函数
// 三个基本需求
// 计算的散列值是一个非负整数（要作为下标）
// 当key1与key2相等，hash(key1)==hash(key2) （准确查询）
// 键值不相等，哈希值也不相等
// 
// 前两个基本需求很好理解，也比较容易实现
// 但第三点几乎不可能
// 
//散列冲突
// 再好的散列函数也无法避免散列冲突，要设计一些解决方案
// 
// 开放寻址
// 如果出现散列冲突，就重新探测一个空闲位置
// 线性探测
// 如果某个数据经过散列后存储位置已经被占用，则从当前位置开始找，看是否有空闲，直到找到
// 二次探测
// 是线性探测的改进，每次探测的步长从1也就是hash(key)+n变为hash(key)+n^2
// 双重散列
// 用一组散列函数，如果第一个散列函数计算的位置被占用则再用第二个，直到找到空闲
// 综合看
// 开放寻址这样的方法，当空闲位置不多时，散列冲突概率会提高
// 为了保证效率，需要保证表内有一定比例的空闲槽位
// 
// 链表法
// 散列表中的每个元素不再直接是元素数据，而是一个桶，对应一个链表，所有散列值相同的元素放在同一个槽位的链表中
// 
//问题解决：
// 常用英文单词存储在一个散列表中，占的内存根据单词数量也只占几M到几十M
// 用户输入单词后，去散列表中查找，找到则拼写正确，反之给提示可能错误
// 
//思考
// 10w条url数据，根据访问次数排序
//  先利用散列表统计次数，再看次数统计的最大值是否大于url记录数，不大于则直接桶排序，超过10w很多则可以快排
// 两个10w条字符串的数组，快速找出两个数组中相同的字符串
//  以其中一个数组构建散列表，再遍历另一个数组在散列表中查找
// 
// 
//工业级散列表
// 
//问题引入：散列表的效率受很多设计因素影响
// 极端情况下，恶意攻击者可以构造数据，使所有数据经过散列后都到同一个槽中（散列表碰撞攻击）
// 这样的话散列表就退化成了链表，查询复杂度从O(1)退化到O(n)
// 如何设计对应各种异常的散列表？（抵抗碰撞，提高性能）
// 
//散列函数设计
// 首先，散列函数本身不能过于复杂，否则时间都消耗在了hash过程中
// 其次，生成的值尽可能随机并均匀的分布
// 例：word拼写检查中，可以将单词每个字母ascii码进位相加，再跟散列表大小取余取模等
// 
// 针对装载因子
// 当空余槽位太少，或空间不够时，与数组一样需要动态扩容
// 动态扩容后，由于散列函数可能涉及到数组空间作为计算参数，则在数据搬移时，每个数据也都需要按照加入散列表的规则重新放入
// 此时的时间复杂度
// 由于搬移数据，为O(n)，但并不是每次插入都需要扩容，所以分摊计算；又由于最好的插入情况为O(1)，所以最终，带动态扩容情况的插入依然复杂度为O(1)
// 
// 避免低效扩容
// 当数据量过大时，扩容一次的效率会很低，因为涉及到大量数据的重新计算入表，导致个别插入操作缓慢
// 可以将扩容操作穿插在插入操作中，分批完成
// 也就是 渐进式rehash
// 扩容时不直接搬移数据
// 同时使用两个哈希表，ht0和ht1
// 查找从两个表中各自进行一次，删除和更新都是；只有新增操作是只放入ht1，这样下来，ht0只减不增，并随着rehash进行，最终ht0变为空表
// 
// 冲突解决方案的选择
// 数据量小时，可以使用开放寻址
// 对于链表法，可以将简单的链表改造为跳表、红黑树等高效结构，这样就算所有数据都分配到一个槽，退化后查找时间也就是O(logn)，有效避免碰撞攻击
// 
//JAVA的HashMap设计
// 初始大小 可设置，默认16
// 装载因子 默认0.75，当元素个数超过0.75*capacity，则扩容为两倍
// 散列冲突 使用链表法，在1.8之后，当链表长度太长（默认8）时，链表转为红黑树，元素少（6）时再转回来（维护平衡的性能与元素个数遍历的性能衡量）
// 散列函数 使用对象自己的hashcode函数计算一个值，再统一处理一次 (h^(h>>>16))&(capicity-1)
// 
// 
//散列表和链表
// 
//从之前的LRU缓存淘汰算法开始
// 一个按访问时间从大到小有序排列的链表，当缓存空间不够时，将链表头部节点删除
// 取某数据时，缓存中没有，则将数据放入链表尾部，如果有，直接使用，并将其移动到链表尾部
// 单纯使用链表实现的LRU，时间复杂度为O(n)
// 
// 缓存系统中的几个操作，添加、删除、查找
// 而每个操作其实都涉及查找，可以结合散列表使用
// 以双链表存储数据，每个节点新增一个字段hnext作为散列表每个槽位中链表的后继指针
// 也就是每个节点存在于两条链中，双链表用于处理缓存的淘汰时间，每个槽位的拉链用于快速查找节点位置
//



//
//树
// 
//基本概念
// 高度 节点到叶子节点的最长路径（边数）
// 深度 根节点到节点的边个数
// 层数 深度+1（跟深度同理，但深度从0开始，而层数从1开始计数）
// 
//二叉树
// 每个节点最多有两个子节点
// 满二叉树 除叶子节点之外，每个节点都有两个子节点
// 完全二叉树 除最后一层之外都是满的，并且最后一层叶子节点是从左到右依次连续存在的（用数组表示树时更节约空间）
// 
//存储方式
// 链式
// 每个节点用三个字段，分别是数据、左子节点指针和右子节点指针
// 数组
// 将根节点存储在索引为 i=1 的位置，左子节点为 2i ，右子节点为 2i+1 
// 
//遍历
// 前序 对任意节点开始，先操作自身，然后是左子树，最后右子树（根-》左-》右）
// 中序 先左子树，再自身，最后右子树（左-》根-》右）
// 后序 先左子树，再右子树，最后是自身（左-》右-》根）
/* 遍历通用伪代码模板，递归思想，时间复杂度O(n)

void tree_order(Node* root)
{
	if (root == nullptr) return;

							   // 《—— do_something(root); 对当前节点的操作（如printf）插在这里就是前序遍历
	tree_order(root->left);    // 递归操作左子树
							   // 《—— 对当前节点的操作插在这里就是中序遍历
	tree_order(root->right);   // 递归操作右子树
							   // 《—— 对当前节点的操作插在这里就是后序遍历
}

*/
// 
//二叉搜索树
// 树中任意节点左子树每个节点值都小于此节点值，右子树节点都大于这个节点值
class tree_node {
public:
	tree_node(int data)
		: m_data(data),
		m_left(nullptr),
		m_right(nullptr)
	{}

public:
	int m_data;
	tree_node* m_left;
	tree_node* m_right;
};
class binary_search_tree {
public:
	using node_type = tree_node;
	using data_type = int;
public:
	//查找操作，根据特性，像是二分查找
	//小于当前节点往左子树找，大于往右找，相等找到，没找但返回空
	node_type* find(data_type value)
	{
		if (root == nullptr) return nullptr;//不判空也行，后面逻辑带判空

		node_type* temp = root;
		while (temp != nullptr)
		{
			if (temp->m_data == value)
				return temp;
			else if (temp->m_data > value)
				temp = temp->m_left;
			else
				temp = temp->m_right;
		}
		return nullptr;
	}
	//插入操作，也涉及查找的过程，先需要查找插入位置
	//大于一个节点往右插，小于往左插，直到找到一个空节点
	void insert(data_type value)
	{
		if (root == nullptr)
		{
			root = new node_type(value);
			return;//空树直接作为根节点插入
		}

		node_type* temp = root;
		while (temp)
		{
			if (temp->m_data < value)
			{
				//新节点值大于当前节点，判断右子节点是否为空，是则插入
				if (temp->m_right == nullptr)
				{
					temp->m_right = new node_type(value);
					return;
				}
				//不为空继续找
				temp = temp->m_right;
			}
			else
			{
				if (temp->m_left == nullptr)
				{
					temp->m_left = new node_type(value);
					return;
				}

				temp = temp->m_left;
			}
		}
	}
	//删除操作，三种情况
	void delete_node(data_type value)
	{
		node_type* temp = root, * parent = nullptr;
		//第一步，找到要删除的节点
		while (temp != nullptr && temp->m_data != value)
		{
			parent = temp;//记录父节点
			if (value <= temp->m_data)
				temp = temp->m_left;
			else
				temp = temp->m_right;
		}
		//没找到，直接返回
		if (temp == nullptr) return;
		//最复杂的情况，删除的节点有两个子节点
		if (temp->m_left != nullptr && temp->m_right != nullptr)
		{
			//需要在右子树找最小节点，因为右子树min>左子树max，是最适合作为左子树新的父节点的
			node_type* min = temp->m_right, * minp = temp;//记录右子树最小节点和最小节点的父节点
			//找最小，一路向左找
			while (min->m_left)
			{
				minp = min;
				min = min->m_left;
			}
			//最小节点值替换到原本要删除的位置
			temp->m_data = min->m_data;
			//删除位置改变，复杂情况退化成删除叶子节点
			temp = min;
			parent = minp;
		}

		//第二种，删除的节点是叶子节点，或只有一个子节点，则把子节点接到父节点上
		node_type* child;//若有子节点，记录
		if (temp->m_left) child = temp->m_left;
		else if (temp->m_right) child = temp->m_right;
		else child = nullptr;

		//最后判断下删除的是不是根节点
		if (parent == nullptr)
			root = child;//nullptr
		//调整要删除节点的父节点
		else if (parent->m_left == temp)
			parent->m_left = child;
		else
			parent->m_right = child;

		//删除节点
		delete temp;
	}

	//其他操作
	//快速查询最大最小节点，则是向右或向左遍历到底
	//前驱后继节点，则是左子树向右遍历到底或右子树向左遍历到底

	//特性
	//中序遍历，可以输出一个有序数据序列，时间复杂度O(n)

private:
	node_type* root;
};
// 
//支持重复数据的二叉搜索树
// 对于节点值重复的节点，一个办法是通过链表或动态扩容数组等存在一个节点上，但不优雅
// 另一种方法是
// 若相同，当作大于此重复节点的节点，也就是当作后继节点插入
// 在查找时，找到相同的节点时不停止，而是直到遇到叶子节点才停止，就找到了所有相同值节点
// 删除同理
// 
//时间复杂度分析
// 极端情况，构建树时，全都偏向一边，则退化成链表，查找复杂度变成O(n)
// 在较均衡（平衡二叉树、完全二叉树、满二叉树等）情况下，树高度接近logn，则操作的时间复杂度也为O(logn)
// 
//与散列表的对比
// 散列表各操作能做到O(1)为什么还需要二叉树
//	在需要排序的数据中，二叉树只要中序遍历便是有序的，而散列表时无序存储，需要自己排序
//	散列表扩容、散列冲突情况下，性能不够稳定；而平时使用的树一般是平衡的，较稳定
//	哈希冲突的存在，使得常量级的操作并不一定比logn小，实际速度也不一定比树快
//	散列表结构要更复杂，设计上要考虑的更多；而树只需要做好平衡这一点就可以适应大部分情况
//	装载因子的存在使得散列表中总是有一部分空间是浪费的
// 所以，要根据自己需求，选择数据结构
//



//
//堆和堆排序
//
//定义
// 堆是一个完全二叉树
// 堆中每个节点值都必须大于等于（小于等于）其子树中每个节点值（比二叉搜索树要求更宽松）
// 
//数组存储
// 从索引1开始，下标为i的左子节点就是2i位置的节点，右子节点为2i+1下标的节点
// 父节点就是下标为i/2的节点
// 
//操作
class heap {
public:
	heap(int cap)
		: m_cap(cap),
		m_count(0)
	{
		m_arr = new int[m_cap + 1];//0要空出来，所以+1
	}

	//插入
	//新元素先放到堆的最后，因为要满足完全二叉树特性
	//一般来说，插入后新元素位置需要调整（堆化）
	//插入一般使用从下向上的堆化，比较新节点与父节点值大小，如果不满足大小关系，则互换
	void insert(int value)
	{
		if (m_count >= m_cap) return; //满了

		++m_count;
		m_arr[m_count] = value;//先放到结尾
		int hole = m_count;//从当前位置开始向上堆化
		while (hole / 2 > 0 && m_arr[hole] > m_arr[hole / 2]) //到根节点或新值已小于当前父节点（此例为大顶堆）
		{
			int temp = m_arr[hole];
			m_arr[hole] = m_arr[hole / 2];
			m_arr[hole / 2] = temp;
			hole /= 2;
		}
	}

	//删除
	//从堆顶删除
	//用最后一个元素放到堆顶（覆盖了堆顶相当于删除了）
	//然后用此元素进行从上向下的堆化，比较与子节点的大小，直到它换到正确的位置
	int remove_top()
	{
		if (m_count == 0) return -1;//堆空
		m_arr[1] = m_arr[m_count--];//把最后一个数据拿上来

		//向下堆化抽象成通用函数，还需要用到
		heapify(m_arr, m_count, 1);
	}
	void heapify(int* arr, int count, int index)
	{
		while (true)
		{
			int pos = index;
			//看左边大还是右边大
			if (index * 2 <= count && arr[index] < arr[index * 2]) pos = index * 2;//左子比本节点大
			if (index * 2 + 1 <= count && arr[pos] < arr[index * 2 + 1]) pos = index * 2 + 1;//右子比左子或本节点大
			if (pos == index) break;//自己就是最大，跳出循环
			//交换
			int temp = arr[pos];
			arr[pos] = arr[index];
			arr[index] = temp;
			index = pos;//继续往下
		}
	}
	//插入删除时间复杂度O(logn)

	//建堆
	//一个现成数组，只需要从数组中间开始，把前半部分依次向下堆化，则可以快速建一个堆
	void build_heap(int* arr, size_t n)
	{
		for (int i = n / 2; i >= 1; --i)
			heapify(arr, n, i);
	}

	//排序
	//类似删除堆顶元素
	//每次把堆顶与最后一个元素交换，将剩下n-1个元素重新构建堆，重复过程，直到只剩一个元素
	void heap_sort(int* arr, size_t n)
	{
		build_heap(arr, n);
		int k = n;
		while (k > 1)
		{
			int temp = arr[1];
			arr[1] = arr[k];
			arr[k] = temp;
			--k;
			heapify(arr, k, 1);//继续对堆顶向下堆化
		}
	}
	//对比快排，堆排序访问数据是跳着访问，对CPU缓存不友好；交换次数更多；并且可能打乱数据原有的相对顺序（可能原本有顺序的数组在第一步建堆过程中变无序）

private:
	int* m_arr;	//存储容器
	int m_cap;	//容量
	int m_count;//已存放元素个数
};
// 
//堆应用
// 一个包含10亿个搜索关键词的日志文件，如何快速获取Top10关键词
// 
// 优先级队列 可以用堆来实现（C++ priority_queue）
// 简单应用
// 
// 100个100M的文件，每个文件存储有序字符串，需要合并为一个有序的大文件
// （暴力解：每个文件取第一个字符串，放入数组比较大小，最小的放入大文件，再从最小字符串所在文件去一个出来，重新比较；每次都是遍历整个数组，效率低）
// 可以从每个文件取第一个（最小字符串）建立最小堆，作为队列
// 然后依次从堆顶出队，每次出队时从所在文件删除，放入大文件，并从当前小文件取下一个字符串入队
// 以此类推，处理完所有文件
// 
// 求中位数
// 利用两个堆，一个最大堆一个最小堆，分别存储一半数据，小顶堆数据都大于大顶堆（小顶堆堆顶大于大顶堆堆顶）
// 如果是偶数个数据，两个堆分别存n/2个数据，奇数个则大顶堆存n/2+1个，小顶堆存n/2
// 这样，大顶堆的堆顶就是需要的结果
// 如果是动态添加的数据，则根据大小分别入堆，并且，需要实时调整两个堆的数量大小（堆顶元素互相移动）以满足平分数量的约定
// （求百分比数据也类似，中位数相当于50%的数据；例如求80%数据，则一个堆存n*0.8，另一个存n*0.2）
// 
// 解答10亿搜索关键词
// 散列表统计相同词出现次数，然后用堆求TopN（建立N个元素的小顶堆），依次与堆顶对比，比堆顶大的删除堆顶并入堆
// 但占用内存可能极大，可以分10个文件，将关键字哈希后与文件数取模分组；之后分别求top10，最后从100个关键词再求一次top10
//



//
//图
// 
//问题引入：微博、微信等社交网络的好友关系如何存储
// 
//定义
// 图是类似于树但更复杂的一种非线性结构
// 树元素称为节点，而图中元素为 顶点
// 一个顶点可以与任意其他顶点建立连接关系（称为 边）
// 一个顶点跟其他顶点连接的边的条数称为 度
// 
// 微信就像是这种无向图，都是顶点间的单纯的相互对应关系
// 
// 类似微博社交关系中，一个人可以单向关注另一个人，则需要引入 边的方向 概念
// 边有方向的图为有向图
// 而对于度，则根据方向分为 入度 和 出度 （入度相当于粉丝数，出度相当于关注数）
// 
// 类似QQ社交关系中，还有亲密度的概念，每条边都需要加一个权重
// 这种为带权图
// 
//存储方式
// 邻接矩阵
// 依赖一个二维数组，如果顶点i和j之间有边
// 则
// 无向图中，将arr[i][j]和arr[j][i]都标记为1
// 有向图中，例如边的方向为i到j，则标记arr[i][j]为1
// 带权图中，标记方式相同，但不再标记为1，而是标记为权重值
// 邻接矩阵的优点
// 直观、简单
// 获取两顶点关系很高效（基于数组访问快）
// 方便计算
// 缺点是
// 浪费空间
// 无向图其实只需要用对角线划分的一半即可表示
// 另外如果是稀疏图（微信几亿用户，每人几百好友，这样顶点多而边不多的情况）浪费的就更多了
// 
// 邻接表
// 针对空间浪费，将每个顶点对应一个链表，链中连接与这个顶点相连的其他顶点
// 但相对的，基于链表，访问的时间消耗就更多了
// 
// 逆邻接表
// 对于有向图，邻接表只能存储出度
// 所以，定义一个逆邻接表，存储入度
// 结合逆邻接表和邻接表，就可以实现微博这种关注/粉丝体系
//



//
//深度和广度优先搜索
// 
//问题引入：“可能认识的人”功能如何实现
// 
//搜索算法
// 在图中找出 从一个顶点出发，到另一个顶点的路径
// 
//无向图中的搜索
#include <vector>
#include <list>
#include <queue>
class graph {
public:
	using data_type = int;
public:
	graph(int v)
		: m_v(v)
	{
		m_adj.resize(v);
	}

	void add_edge(data_type s, data_type t)
	{
		//这里直接以顶点值作为下标，方便理解（s和t应都不超过v）
		m_adj[s].push_back(t);
		m_adj[t].push_back(s);//无向图，一条边分别在两个顶点中存储
	}

	//广度优先算法 BFS
	// 从距离起始顶点最近的顶点开始，往外搜索，层层推进
	// 时间复杂度O(V+E)，V是顶点个数，E是边数，空间复杂度O(V)（借助了数组和队列辅助，但都不超过顶点数V）
	void bfs(data_type s, data_type t)
	{
		if (s == t) return;
		std::vector<int> visited(m_v, 0);//用于记录已被访问过的节点，因为是无向图，要略过前一层
		//（专栏里用的bool数组，但是C++中vector<bool>有特殊性是bit存储，效率低，这里改用int的0和1标记）
		std::queue<int> queue;//用于记录层层推进时，每一层中下一层的顶点
		//从起点开始
		visited[s] = 1;
		queue.push(s);
		//记录搜索路径
		std::vector<int> prev(m_v, -1);//prew[i]指，顶点i是从哪个前驱顶点遍历来的，例如顶点2到顶点3，则prev[3]为2

		while (queue.size() != 0)
		{
			int w = queue.front();
			queue.pop();

			for (auto iter = m_adj[w].begin(); iter != m_adj[w].end(); ++iter)
			{
				int q = *iter;
				if (visited[q] == 1)
					continue;

				prev[q] = w;//记录路径
				if (q == t)
				{
					print(prev, s, t);//到达终点，递归打印
					std::cout << std::endl;
					return;
				}

				visited[q] = 1;//标记已访问
				queue.push(q);//每个顶点入队，以便下一轮循环访问下一层
			}
		}
	}
	void print(std::vector<int>& prev, int s, int t)
	{
		if (prev[t] != -1 && t != s)//prev是逆着的
			print(prev, s, prev[t]);
		std::cout << t << " ";
	}

	//深度优先搜索 DFS
	// 从一个岔路走到头，走不通时，退回上一个岔路，重新选择
	// 从顶点V触发，访问未被访问的邻接顶点，再对邻接顶点深度优先遍历，直到所有邻接顶点被访问
	// 使用了回溯思想，适合用递归
	// 时间复杂度O(E)，E为边数，每个边最多访问两次（遍历和回退），空间复杂度O(V)
	bool found = false;
	void dfs(int s, int t)
	{
		found = false;
		//用于记录的数组；队列直接就是用递归的方式代替了
		std::vector<int> visited(m_v, 0);
		std::vector<int> prev(m_v, -1);

		dfs_recur(s, t, visited, prev);
		print(prev, s, t);
	}
	void dfs_recur(int w, int t, std::vector<int>& visited, std::vector<int>& prev)
	{
		if (found) return;
		visited[w] = 1;

		if (w == t)
		{
			found = true;
			return;
		}

		for (auto iter = m_adj[w].begin(); iter != m_adj[w].end(); ++iter)
		{
			int q = *iter;
			if (visited[q] == 1)
				continue;

			prev[q] = w;
			dfs_recur(q, t, visited, prev);//从一条路径先直接走到底
		}
	}

private:
	int m_v;//顶点个数
	std::vector<std::list<data_type>> m_adj;//邻接表
};
// 
//

int main()
{
	std::cout << "Hello World!\n";
}
