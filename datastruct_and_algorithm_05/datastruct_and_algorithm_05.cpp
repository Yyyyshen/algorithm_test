﻿// datastruct_and_algorithm_05.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>

//
//实战和练习
//

//
//Redis常用数据类型的结构
// 
//非关系型数据库
// 只包含键、值两部分，通过键查询值（mysql关系型数据库包含多个字段，通过sql语句查询）
// 主要作为内存数据库使用（也支持存在硬盘）
// 键的类型是字符串
// 值的类型有多种，常用：字符串、列表、字典、集合、有序集合
// 
//列表
// 存储一组数据，实现方式有两种
// 压缩列表 和 双向循环链表
// 
// 数据量小时，可以使用压缩列表
//  单个数据小于64字节
//  列表中数据个数小于512个
// 是redis自己设计的数据存储结构
// 通过连续内存空间存储数据，类似数组但可以存储大小不同的数据
// [data_num][data1_len][data1][data2_len][data2]...
// 例 3-2-ab-5-abcde-3-abc...
// 若用普通数组，每个字符串就都需要5字节，有一定的内存浪费，并且不支持不同类型
// 
// 数据量大，需要用双向循环链表
typedef struct redis_listnode
{
	struct redis_listnode* prev;
	struct redis_listnode* next;
	void* value;
} redis_listNode;
typedef struct redis_list
{
	redis_listNode* head;//记录头尾、长度等信息，使用更方便些
	redis_listNode* tail;
	unsigned long len;
	//...
}redis_List;
// 
//字典
// 每个数据又包含键值两部分
// 也是两种实现方式，压缩列表、散列表
// 
// 压缩列表实现和限制条件与列表相同
// 
// 数据量大使用散列表
// 哈希函数用的是MurmurHash
// https://github.com/aappleby/smhasher/
// 装载因子大于1时，扩容2倍；小于0.1时，缩容
// 
//集合
// 存储一组不重复数据
// 
// 满足条件
//  存储数据是整数
//  元素个数不超过512
// 采取有序数组
// 
// 否则使用散列表
// 
//有序集合
// 除了之前说的跳表，数据量小也可以使用压缩列表
// 
//持久化
// 其实就是存储到磁盘
// 当机器断电，存储数据不会丢失，重启后重新读取到内存即可
// 将数据存储到硬盘时，主要两种思路
// 
// 清除原有存储结构
// 只讲数据存储到磁盘
// 还原时，再组织成原结构（redis就是这种）
// 但例如散列表这样的数据读取时，相当于每个数据需要重新计算hash，数据量大时，这个过程耗时很高
// 
// 另一种是保留原有存储格式
// 还是用散列表举例，可以将大小、散列到的槽的编号都同时保存
// 读取时，直接还原，不需要重新计算
// 
//总结
// 压缩列表、有序数组、链表、散列表、跳表
// redis就是这些常用数据结构的封装
// 
// 较小数据量下，采用压缩列表，减小内存占用，并且cpu友好，有利于使用l2缓存，是升级版数组
// 但不支持随机访问（元素大小不一样），需要遍历，且需要连续空间，所以
// 数据量大用散列表或其他数据结构
// 
//思考
// 二叉树存储
// 填充叶子节点形成完全二叉树，然后以数组形式存储到硬盘
// （还有一个结合中序和前序遍历存储，然后根据两种顺序还原唯一树结构，但是不是需要两倍的空间）
//



//
//搜索引擎中的数据结构和算法
// 
//在一台8G内存100G硬盘的机器上实现小型搜索引擎
// 
//四个部分
// 搜集、分析、索引、查询
// 
//搜集
// 就是爬虫爬取和分析
// 搜索引擎把互联网看作有向图，把页面看作顶点，某页面包含另一个页面链接则是一条有向边
// 利用图的遍历搜索，遍历整个互联网中的网页
// 先找一些大型的网站主页，作为种子网页链接放到队列，使用广度优先策略，不断取出链接并解析出包含的链接加入队列
// 
// 实现细节
// 
// 待爬取网页链接文件 links.bin
// 每次取出队列中一个页面时，可能会解析出越来越多的链接，全放入队列可能会不够用
// 所以使用一个磁盘中的文件作为队列
// 每次从文件中取出对应页面，并将解析到的链接直接存到links.bin文件中
// 
// 网页判重文件 bloom_filter.bin
// 使用布隆过滤器，快速并节约内存地实现网页去重
// 但要考虑容灾，如果机器宕机，过滤器就被清空了
// 可以定期的将过滤器持久化到磁盘中
// 
// 原始网页存储 doc_raw.bin
// 爬到网页后，存储下来，以备后续分析、索引使用
// 将海量网页都存储为单独文件，文件数会非常多（单目录文件过多会有性能瓶颈，https://mp.weixin.qq.com/s/g-fFoYsBJkonV3ezdGDJKA）
// 使用一定的协议，例如 
// doc1_id \t doc1_size \t doc1 \r\n
// 分隔每个文件
// 单文件过大时，再分一个新文件
// （文件还是过多时，可以通过哈希函数，散列存储到不同文件夹）
// 
// 网页链接及其编号的对应文件 doc_id.bin
// 可以按网页爬取先后，从小到大依次编号，作为网页的唯一id
// 除了原始存储，额外将id和网页链接的对应关系存到一个文件中
// 
//分析
// 爬取网页后，需要离线分析，包含两个步骤
// 
// 抽取网页文本信息
// 网页是半结构化数据，夹杂各种标签、js、css等，对于搜索引擎可以只关心文本信息
// 依靠HTML规范，将需要的标签抽取出来
// 例如 AC自动机多模式串匹配<script>等不需要的标签，找到后往后遍历，直到</script>，然后删除这部分内容
// 
// 分词创建临时索引
// 英文网页中，分词只需要空格、标点等分割开
// 中文，一种较简单的思路是基于字典和规则的分词方法（利用词库和最长匹配规则）
// 分词完成后，得到一组单词列表，写入临时索引文件中
// tmp_index.bin
// term1_id \t doc_id \r\n 单词编号与网页编号对应的格式
// 具体单词内容存入散列表
// 单词与编号的对应关系写入磁盘 term_id.bin
// 
//索引
// 将分析阶段产生的临时索引构建成倒排索引
// （倒排索引：记录每个单词及其包含的网页列表）（倒排-》单词被哪些文档包含；正排-》文档包含哪些单词）
// term_id \t doc_id1,doc_id2...doc_idx \r\n
// 这个过程一般用多路归并排序
// 先堆临时索引文件根据词id大小排序，最后合并多路结果
// 相同编号的单词也就是相同单词就排列到一起，遍历一遍就能取出对应列表了
// 
// 另外，需要一个记录每个单词编号在倒排索引中偏移位置的文件
// term1_id \t offset1 \r\n
// 存入 term_offset.bin
// 
//查询
// 前面的工作得到一些文件
// doc_id.bin 记录网页链接和编号对应关系
// term_id.bin 记录单词和编号之间对应关系
// index.bin 倒排索引
// term_offset.bin 每个单词编号在倒排索引文件中的偏移位置
// 其中倒排索引较大，其他的都较小，所以可以将其他三个文件直接加载到内存使用
// 
// 过程
// 用户在搜索框输入某个文本
// 对用户输入进行分词处理，得到k个单词
// 将k个单词取term_id.bin对应的散列表查找单词编号
// 用k个单词编号在term_offset.bin对应散列表查找每个编号在倒排索引中的偏移位置
// 用k个偏移位置，到index.bin倒排索引文件中查找k个单词对应的网页编号列表
// 将k个网页编号列表，统计每个编号出现次数作为权重，得到一组排好序的网页编号
// 将这组排好序的网页编号，在doc_id.bin中查找对应网页链接，分页展示
// 
//总结
// 涉及 图、散列表、trie树、布隆过滤器、但模式字符串匹配算法、AC自动机、广度优先遍历、归并排序
// java实现
// https://github.com/kkzfl22/searchEngine
//



//
//高性能内存消息队列Disruptor背后的数据结构和算法
// 
//线程之间用于消息传递的队列，在Apache Storm、Camel、Log4j 2等项目中有应用
// 
//基于循环队列的“生产——消费者模型”
// 例 队列满生产者轮询等待、队列空消费者轮询等待
class demo_queue final
{
public://循环队列
	demo_queue(size_t s)
		:size(s)
	{
		data = new long[size];
	}
	~demo_queue()
	{
		delete[] data;
	}
public:
	bool add(long element) noexcept
	{
		if ((tail + 1) % size == head) return false;//队列满了
		data[tail] = element;
		tail = (tail + 1) % size;//用取模将线性变成环形概念
		return true;
	}
	long poll() noexcept
	{
		if (head == tail) return -1;
		long ret = data[head];
		head = (head + 1) % size;
		return ret;
	}

private:
	long* data = nullptr;
	int size = 0;
	int head = 0, tail = 0;
};
class demo_producer final
{
public://生产者
	using queue_type = demo_queue;
	using data_type = long;
public:
	demo_producer(queue_type* queue)
		: m_queue(queue)
	{}
public:
	void produce(data_type data)
	{
		if (m_queue == nullptr) return;
		while (!m_queue->add(data))
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//队列满了就轮询重试
	}

private:
	queue_type* m_queue;
};
class demo_consumer final
{
public://消费者
	using queue_type = demo_queue;
	using data_type = long;
public:
	demo_consumer(queue_type* queue)
		: m_queue(queue)
	{}
public:
	void consume()
	{
		if (m_queue == nullptr) return;
		while (true)
		{
			data_type data = m_queue->poll();
			if (data == -1) //队列空则等待
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			else
			{
				//消费数据逻辑
				//...
			}
		}
	}

private:
	queue_type* m_queue;
};
// 实际多线程使用时，生产消费需要在操作队列前加锁
// 
//基于无锁的并发“生产——消费模型”
// Disruptor换了一种实现思路
// 对于生产者，往队列中添加数据之前，先申请可用空闲存储单元
// 批量的申请n个存储单元，后续往队列中添加元素就不用加锁，因为这组单元是此线程独享
// （但申请存储单元的过程是加锁的，其实就是减小锁的粒度）
// 消费者类似，每次申请一批连续可读存储单元（加锁），后续每次读就不用加锁了
// 
// 问题
// 前面的内存没有操作完时，不能操作后续的部分
// 例如，生产者A申请3~6，生产者B申请7~9，在3~6没有写入数据之前，7~9无法读取，是一个弊端
// 解释
// 生产者A和生产者B同时申请3~6和7~9，写入时没有问题
// 假设某时刻，生产者A写入到5的位置、6为空，生产者B写入到8的位置、9为空
// 从disruptor队列的设计角度来看，6为空，所以消费者读到的最大可读位置是5，有空位则后续的位置只能等待
//



//
//微服务鉴权限流的数据结构和算法
// 
//背景
// 复杂的大应用，解耦拆成几个小应用
// 调用关系变复杂，出错概率和debug难度提高
// 管理微服务很重要
// 涉及 鉴权、限流、降级、熔断、监控告警
// 
//鉴权
// 假设一个微服务为用户服务，提供登录、注册等
// 具体哪个用户拥有什么接口权限，可以通过url匹配
// 也就是字符串匹配KMP、BM、BF等
// 还可以用Trie树，做前缀匹配
// 
//限流
// 根据不同服务限流粒度
// 例如每秒钟不能超过1000次调用
// 
// 最简单的限流是固定时间窗口限流算法
// 选定一个时间起点，每当请求到来，计数器加一，在当前时间窗口（例如1s）
// 出现累加访问次数超过限流值（例如100次）
// 则拒绝后续访问
// 进入下一个时间窗口后，计数器清零重新计算
// 瓶颈：两个1s窗口中，前一窗口100次集中在后10ms，后一窗口集中在前10ms，20ms内发生200次集中请求
// 
// 滑动窗口限流
// 为了保证任意窗口内，都不超过最大允许限流值
// 维护一个队列，长度为一个窗口内限制大小K+1，记录一个窗口内的请求
// 当新的请求到来，将与这个新请求时间间隔超过1s的请求从队列中出队
// 有空闲位置则新请求入队，没有则拒绝
// 
// 两个都不能避免更细粒度的高访问频率（如1ms访问100次）
//



//
//短网址系统
// 
//实例
// 微博发布带网址信息，会自动转化为更短的网址
// http://t.cn/123455
// 用户点击短网址，会将浏览器重定向为原网址
// 
//生成短网址
// 哈希算法
// 将长字符串转化成长度固定哈希值
// 比较著名且广泛应用的 MurmurHash
// 提供两种长度哈希32bits和128bits
// 短网址要尽可能短，选择32bits
// 
// 但还可以更短
// 将10进制哈希值，转为更高的进制
// 例如16进制用A~F代表10~15
// 网址url中合法字符有0~9，a~z、A~Z
// 共62个字符，可以将10进制转成62进制
// 
//解决哈希冲突
// 保存短网址和原始网址的对应关系
// 例如存在数据库
// 生成短网址之后，到数据库查询，如果不存在，则存进库里并返回给用户使用
// 若存在，则对比已经存在的网址，如果一样，说明已经有人生成过，可以复用
// 如果存在且不同，说明真的冲突了，可以拼接一些特殊字符串，再次哈希
// 直到没有冲突，存进库中
// 下次访问时，如果查询到结果发现结尾有特殊字符，则去掉即可
// 
//提升性能
// 若短网址非常多，数据库查询会比较慢
// 可以给短网址字段添加B+树索引
// 还可以用已生成的短网址构建布隆过滤器，减少sql语句和网络请求次数
// 
//ID自增器
// 除了数据库自增字段，也可以自己维护一个计数器
// 但在大量并发请求中保证ID不重复需要加锁
// 可以借助Disruptor思路，提前将号码的一些段封装成多个前置发号器，每个发号器应付一定量的请求
// 或者直接生成多个ID自增器，自增范围不同，也是一样的
// 例
//  请求			请求			请求
// ↓↓↓	       ↓↓↓		   ↓↓↓
// 发号器		   发号器		   发号器
// 1~100		   101~200		   201~300
//

/*********************************************************************************************/

//
//练习
// 
// 参考
// https://github.com/wangzheng0822/algo
//



//
//数组和链表
// 
//数组
// 实现动态扩容数组
//	容量不够时双别扩容，参考vector实现
// 实现大小固定有序数组，支持动态增删改查
//	array.hpp
// 实现两个有序数组合并为一个有序数组
//	两个指针位置对比，哪个小放入新的总数组并后移，循环这个逻辑
//	最后记得把更长数组的剩余元素放进结果数组
// 
//链表
// 实现单链表、循环链表、双向链表，支持增删改查
// 实现单链表反转
// 实现两个有序链表合并一个有序链表
// 实现求链表中间节点
//	single_linked_list.hpp
// 
//LeetCode
// 数组
// 三数之和 /problems/3sum/
// 求众数	/problems/majority-element/
// 求缺失的第一个正数 /problems/first-missing-positive/
// 
// 链表
// 环形链表 /problems/linked-list-cycle/
// 合并k个排序链表 /problems/merge-k-sorted-lists/
// 
// practice.hpp
//



//
//栈、队列、递归
// 
//栈
// 用数组实现一个顺序栈
// 用链表实现一个链式栈
// 编程模拟实现一个浏览器的前进、后退功能
// stack.hpp
// 
//队列
// 用数组实现一个顺序队列
// 用链表实现一个链式队列
// 实现一个循环队列
// queue.hpp
// 
//递归
// 编程实现斐波那契数列求值 f(n) = f(n - 1) + f(n - 2)
// 编程实现求阶乘 n!
// 编程实现一组数据集合的全排列
// 
//LeetCode
// 栈
// Valid Parentheses（有效的括号）/problems/valid-parentheses/
// Longest Valid Parentheses（最长有效的括号）/problems/longest-valid-parentheses/
// Evaluate Reverse Polish Notatio（逆波兰表达式求值）/problems/evaluate-reverse-polish-notation/
// 
// 队列
// Design Circular Deque（设计一个双端队列）/problems/design-circular-deque/
// Sliding Window Maximum（滑动窗口最大值）/problems/sliding-window-maximum/
// 
// 递归
// Climbing Stairs（爬楼梯）/problems/climbing-stairs/
// 
// practice_02.hpp
//



//
//排序和二分查找
// 
//排序
// 实现归并排序、快速排序、插入排序、冒泡排序、选择排序
// 编程实现 O(n) 时间复杂度内找到一组数据的第 K 大元素
// sort.hpp
// 
//二分查找
// 实现一个有序数组的二分查找算法
// 实现模糊二分查找算法（比如大于等于给定值的第一个元素）
// binary_search.hpp
// 
//LeetCode
// Kth Largest （第k大元素）/problems/kth-largest-element-in-an-array/
// Sqrt(x) （x的平方根）/problems/sqrtx/
// 
// practice_03.hpp
//



//
//散列表和字符串
// 
//散列表
// 实现一个基于链表法解决冲突问题的散列表
// 实现一个 LRU 缓存淘汰算法
// hashtable.hpp
// 
//字符串
// 实现一个字符集，只包含 a～z 这 26 个英文字母的 Trie 树
// 实现朴素的字符串匹配算法
// strings.hpp
// 
//LeetCode
// 字符串
// Reverse String（反转字符串）/problems/reverse-string/
// Reverse Words in a String（翻转字符串里的单词）/problems/reverse-words-in-a-string/
// String to Integer(atoi)（字符串转换整数(atoi)）/problems/string-to-integer-atoi/
//



//
//二叉树和堆
// 
//二叉树
// 实现一个二叉查找树，并且支持插入、删除、查找操作
// 实现查找二叉查找树中某个节点的后继、前驱节点
// 实现二叉树前、中、后序以及按层遍历
// tree.hpp
// 
//堆
// 实现一个小顶堆、大顶堆、优先级队列
// 实现堆排序
// 利用优先级队列合并 K 个有序数组
// 求一组动态数据集合的最大 Top K
// heap.hpp
//
//LeetCode
// Invert Binary Tree（翻转二叉树）/problems/invert-binary-tree/
// Maximum Depth of Binary Tree（二叉树的最大深度）/problems/maximum-depth-of-binary-tree/
// Validate Binary Search Tree（验证二叉查找树）/problems/validate-binary-search-tree/
// Path Sum（路径总和）/problems/path-sum/
// 
// practice_05.hpp
//



//
//图
// 
// 实现有向图、无向图、有权图、无权图的邻接矩阵和邻接表表示方法
// 实现图的深度优先搜索、广度优先搜索
// 实现 Dijkstra 算法、A* 算法
// 实现拓扑排序的 Kahn 算法、DFS 算法
// graph.hpp
// 
//LeetCode
// Number of Islands（岛屿的个数）/problems/number-of-islands/description/
// Valid Sudoku（有效的数独）/problems/valid-sudoku/
// 
// practice_06.hpp
//



//
//贪心、分治、回溯、动态规划
// 
//回溯
// 利用回溯算法求解八皇后问题
// 利用回溯算法求解 0 - 1 背包问题
// 
//分治
// 利用分治算法求一组数据的逆序对个数
// 
//动态规划
// 0 - 1 背包问题
// 最小路径和（详细可看 @Smallfly 整理的 Minimum Path Sum）
// 编程实现莱文斯坦最短编辑距离
// 编程实现查找两个字符串的最长公共子序列
// 编程实现一个数据序列的最长递增子序列
// 
//LeetCode
// Regular Expression Matching（正则表达式匹配）/problems/regular-expression-matching/
// Minimum Path Sum（最小路径和）/problems/minimum-path-sum/
// Coin Change （零钱兑换）/problems/coin-change/
// Best Time to Buy and Sell Stock（买卖股票的最佳时机）/problems/best-time-to-buy-and-sell-stock/
// Maximum Product Subarray（乘积最大子序列）/problems/maximum-product-subarray/
// Triangle（三角形最小路径和）/problems/triangle/
// 
// practice_07.hpp
//

int main()
{
	return 0;
}
