﻿// datastruct_and_algorithm_03.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//
//第三阶段
// 四种算法思想：贪心、分治、回溯、动态规划
// 跳表
// 拓扑排序、Dijkstra算法、A* 算法
// B + 树
// 位图
//

//
//贪心算法
// 
//背包问题
// 一个容纳100kg的背包，有无五种物品，每种物品总量和总价值不同
// 物品1  100kg   100元
// 物品2  30kg    90元
// 物品3  60kg    120元
// 物品4  20kg    80元
// 物品5  50kg    75元
// 怎样选择，让背包所装物品总价最高
// 当然是 20kg 4 + 30kg 2 + 50kg 3
// 本质上是贪心算法
// 
//分析
// 针对一组数据，定义限制值和期望值，从中选取数据，在限制条件下期望值最高；这类问题考虑贪心算法
// 每次选择当前情况下，对限制值同等贡献量情况下，最期望值贡献量最大的数据
// 举例验证，看贪心产生的结果是否最优
// （并不总能给出最优解，某些问题中，局部最优选择会影响之后的选择，就无法获得全局最优了）
// 
//例
// 分糖 m个糖，n个孩子，m < n
// 每个糖大小不等，大小为s1，s2 ... sm
// 每个孩子对糖大小有要求g1，g2 ... gn
// 只有糖大小大于孩子要求时，才能满足孩子
// 如何分配，满足尽可能多的孩子
// 限制为糖果数m，对于期望值贡献，只要满足一个孩子，贡献值就是相同的，所以无所谓满足更大需求的孩子
// 每次从剩下的孩子中，找出需求最小的，然后发给他剩余糖果中最小能满足他的糖，最终就是最多的方案
// 
// 钱币找零 假设有1、2、5、10、20、50、100面额的纸币，要支付K元，最少需要多少张纸币
// 每次都先用最大面额，超出或不够的部分再选小一点面额的，循环，直到累加到K
// 因为，各面值贡献的张数期望值都是一样的（一张），所以希望每张多贡献一些金额数量
// 
// 区间覆盖 有n个区间，区间为[s1,e1]...[sn,en]，选出一部分区间（区间要求不相交），最多能选多少个区间
// 先计算出左端点最小和右端点最大，也就是区间最大范围 [smin,emax]
// 每次选择中，左端点选未重合的，右端点选尽量小的
// 
//应用
//一个1000字符的文件，存储需要8000bit，有没有更节约的存储方式
// 
// 方法一
// 统计字符，例如发现只有a,b,c,d,e,f六种不同字符，则3bit数可以覆盖所有字符的表示
// 则可以使用3000bit存储完这个文件
// 
// 霍夫曼编码
// 除了统计字符范围，还会统计字符出现频率
// 并依据贪心算法，将频率高的字符用更短的编码，且要求各个字符的编码不会出现某编码是另一个编码前缀的情况（防止解压复杂）
// 例如 出现频率  编码      总占位
// a    450       1         450
// b    350       01        700
// c    90        001       270
// d    60        0001      240
// e    30        00001     150
// f    20        00000     100
// 每次读取时，按最长能解读的二进制串解压（五位，碰到1或全0结束），则原本8000bit的数据只需要1910bit
// 而获取编码的方式，需要根据频率建立优先级队列，在树形结构中，将左权标为0，右权标为1，到每个字符的路径则是编码
// 
//非负整数a中，移除k个数字，让剩下的最小
// 从左到右，比较相邻两位，左边大时，移除左边，否则用右边与下一个相邻数比较，直到移除k个
// 如果一趟操作下来删掉的不足k，则返回第一个再做一次
// 实现时，可用栈，高位开始入栈，大于栈顶直接入栈
// 下个数若小于栈顶，则弹出栈顶直到栈顶元素小于入栈元素（或栈空）同时k-1
// 直到k为0
// 
//窗口服务中，n个人在等，只有一个窗口，每个人被服务时间长度不同，如何安排
// 最小服务时间优先
// 可以建立小顶堆，每次服务堆顶的人
//

//
//分治算法
// 
//核心 
// 分而治之，将原问题划分成n个规模小，并且结构与原问题相似的子问题
// 递归解决子问题，然后合并其结果
// 
//递归实现
// 每一层递归都涉及三个操作
// 分解 原问题分解成子问题
// 解决 递归求解子问题，问题足够小时直接求解
// 合并 将子问题结果合并成原问题
// 
//场景
// 原问题与分解成的子问题有相同的模式
// 原问题分解的子问题可以独立求解，子问题之间无关联（与动态规划的明显区别）
// 有分解终止条件，问题足够小时直接求解
// 子问题可合并，并且合并操作复杂度不能过高，否则分治就没有意义了
// 
//例
// 求一组数据的有序对个数或逆序对个数
// 以逆序对为例，暴力解法是每个数字与后面所有数字比较，记录更小的，最后把每个数字这样检查一遍，相加计数
// 但时间复杂度为O(n^2)
// 可以用分治思想，使用归并排序的方法，在排序中记录逆序对个数
int num;//计数
void merge_sort_counting(int* a, int p, int r);//划分区间
void merge(int* a, int p, int q, int r);//最小区间内执行的逻辑
int count(int* a, size_t n)//逆序对计算
{
	n = 0;
	merge_sort_counting(a, 0, n - 1);
	return num;
}
void merge_sort_counting(int* a, int p, int r)
{
	if (p >= r) return;//区间划分终止点
	int q = (p + r) / 2;//划分区间，和归并一样
	merge_sort_counting(a, p, q);//递归分到最小
	merge_sort_counting(a, q + 1, r);
	//执行每区间内处理逻辑，以及合并子划分区间结果
	merge(a, p, q, r);
}
void merge(int* a, int p, int q, int r)
{
	int i = p, j = q + 1, k = 0;//从两区间开头开始处理，k作为缓存数组的下标记录
	int* tmp = new int[r - p + 1];//存放合并数据
	while (i <= q && j <= r)//处理同长度部分
	{
		if (a[i] <= a[j])//顺序对直接存入缓存数组
			tmp[k++] = a[i++];
		else
		{
			num += (q - i + 1);//统计pq之间，比a[j]大的元素个数，这也是此例与归并排序的唯一区别
			//（因为是子区间都已经是有序了，所以此时如果a[i]>a[j]则i到q之间一定都大于a[j]了
			tmp[k++] = a[j++];
		}
	}
	//处理（若有）每个数组剩下的部分
	while (i <= q)
		tmp[k++] = a[i++];
	while (j <= r)
		tmp[k++] = a[j++];

	//将排序过的部分，拷贝回原数组
	for (int i = 0; i <= r - q; ++i)
		a[p + i] = tmp[i];

	delete[] tmp;//删除缓存
}
// 
// 
//应用
// 10G文件在2G内存的计算机中排序
// 可以扫描一遍，根据排序的范围，划分几个区间，每个小区间内的放到一个文件（分布不均匀的可以继续分片）
// 然后分别处理每个文件，最终合并
// 
//谷歌MapReduce大数据处理模型
// 就是一个分治的任务调度器，底层依赖GFS存储，依赖Borg管理机器
// 从GFS拿数据，然后交给Borg中的机器执行，并监控进度
// 机器出现宕机或其他问题，则重新调度一台机机器执行
// 
//鸡汤
// 创新并非离我们很远，创新源泉来自对事物本身的认识
// 无数优秀架构涉及的思想来源都是基础的数据结构和算法
//

//
//回溯算法
// 
//贪心算法中，每一步都选择当前最优；但有时，局部最优不一定全局最优，可以选择回溯思想
//
//经典问题：八皇后
// 8*8的棋盘，放8个棋子，每个棋子所在行、列、对角线都不能有另一个棋子
// 找到所有满足这种要求的放棋子方式
#define N_QUEENS 8
int* result = new int[N_QUEENS];//存放结果，下标作为行，值表示Queen放在哪个列
int result_num = 0;
bool is_ok(int row, int col);//核心逻辑函数，判断在此位置放置Queen是否合法
void print_queens();
void cal_n_queens(int row)	//入口调用cal_n_queens(0)从第一行开始
{
	if (row == N_QUEENS)//最后一行也放好了，打印，退出
	{
		print_queens();
		++result_num;
		return;
	}

	//检查放到每一列的情况
	for (int col = 0; col < N_QUEENS; ++col)
	{
		if (is_ok(row, col))//放在此位置合法
		{
			result[row] = col;//记录一下，如果之后某一行无法继续，回溯回来找到满足条件的新位置后，也会进行覆盖
			cal_n_queens(row + 1);//从当前情况继续考察下一行
			//若之后某一次不满足，回一步步退回，再继续从循环中找符合条件的情况
			//若之后找到了一种满足情况，也会返回来继续找其他可能结果
		}
	}
}
bool is_ok(int row, int col)
{
	int leftup = col - 1, rightup = col + 1;
	//由于是逐行检查，只需要往上考察之前的每一行
	for (int i = row - 1; i >= 0; --i)
	{
		//当前行不需要考察，因为设定上就是每行只放一个
		if (result[i] == col) return false;//上一行当前列有棋子则不满足
		//检查对角线
		//左上
		if (leftup >= 0)
			if (result[i] == leftup)
				return false;
		//右上
		if (rightup < N_QUEENS)
			if (result[i] == rightup)
				return false;
		//为更上一行对角线比较做准备
		--leftup; ++rightup;
	}
	//检查都符合，返回true
	return true;
}
void print_queens()
{
	for (int row = 0; row < N_QUEENS; ++row)
	{
		for (int col = 0; col < N_QUEENS; ++col)
		{
			if (result[row] == col)
				std::cout << "Q ";//打印放置Queen的位置
			else
				std::cout << "* ";//打印普通棋子
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
// （看到一句比较精髓的话：回溯就是循环内递归。确实只有这样才能在调用到某一步无法继续递归时，回返回之前的递归层，再走循环选另一条路）
// 
//经典应用：0-1背包（最经典解法是动态规划，但回溯也能解）
// 背包总承载量W，有n个物品，重量不等且不可分割，如何让背包中物品总重量最大
// （与贪心中的背包问题区别是，此处物品不可分割，只能装或者不装，所以叫0-1背包）
// 可以使用回溯，把物品依次排好，然后每次选择一个物品装或者不装，递归进行，当总重超过W时，停止这一轮递归
#define W_BAG 100//背包承重
#define N_ITEM 10//备选物品数量
int* items = new int[N_ITEM];//存放每个物品重量的数组
int maxW = 0;//记录可装最大值
void bag_0_1(	//调用入口 bag_0_1(0,0);
	int i,//表示进行到哪个物品
	int cw//当前已经装了多少重量
)
{
	if (cw == W_BAG || i == N_ITEM)//装满或已放完所有物品，作为一次结果的结束条件
	{
		if (cw > maxW)
			maxW = cw;//大于之前记录过的结果，则记录
		return;
	}

	//每个物品分为两种情况，相当于枚举2^n种情况
	//不装
	bag_0_1(i + 1, cw);//重量不累加
	//装，且是总重量还没超过时才装
	if (cw + items[i] <= W_BAG)
		bag_0_1(i + 1, cw + items[i]);
}
// 
//经典应用：正则表达式匹配
// 
//思想
// 大部分情况下，解决广义搜索问题，也就是从所有可能解中，选出一个最好（或满足要求）的解
// 一般用递归实现，并且利用剪枝操作提高回溯效率
// 之前的深度优先搜索也是回溯思想
// 本质就是枚举，但优点是可以少走些冤枉路
//

//
//动态规划
// 
//问题引入：凑满减，让选出商品总价最大程度接近满减条件
// 
//0-1背包
// 在回溯中，相当于枚举所有可能性，然后选出一个最好的，时间复杂度较高（指数级）
// 可以进行改进
// 仔细看计算过程，其实有很多步骤是重复进行的，可以借助“备忘录”思想，记录下已经计算过的情况，减少重复分支
int maxRet = 0;//记录最大结果
int weight[] = { 2,2,4,6,3 };//各物品重量
int n = 5;//物品个数
int w = 9;//背包承重
bool mem[5][10] = { false };//备忘录
void bag_0_1_mem(
	int i,//表示检查到第几个物品
	int cw//表示已经累加了多少重量
)
{
	if (cw == w || i == n)
	{
		//装满或者所有物品考察完毕
		//比之前记录过的大，则记录
		if (cw > maxRet) maxRet = cw;
		return;
	}
	//检查备忘录
	if (mem[i][cw]) return;//检查到第i个物品且已累加重量与之前的情况重复了，则从i之后的各种情况也是重复的，就不用再算一遍了
	//后面还是一样
	bag_0_1_mem(i + 1, cw);//不装当前物品
	if (cw + weight[i] <= w)
		bag_0_1_mem(i + 1, cw + weight[i]);//装当前物品
}
// 这种递归+备忘录的方式已经接近动态规划的效率
// 
// 再看下动态规划的解法
/*

 也是以一个能覆盖所有情况的数组states[n][w+1]来记录每一层能达到的状态
 比如
 第1个物品（下标0）重量2，装或者不装入背包，有两种状态，即总重量为0或2；我们用1（或true）表示一种状态被标记
 则状态数组 states[0] = { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 }
 每一层决策计算好后，下一层基于上一层的状态集合，推导本层状态集合
 第2个物品（下标1）重量2，装或者不装背包，加上第一层的两种情况一共4种，0+0，0+2，2+0，2+2 （看到这，感觉就像广度优先，而回溯是深度优先）
 但此时有两种状态的结果是重复的，就可以进行合并了，以此达到减少分支的状况
 状态数组   states[1] = { 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 }
 之后，逐层推进
 状态数组   states[2] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }
			states[3] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }//这一层，很明显的所有状态都重合，减少了非常多的重复计算
 最后一层   states[4] = { 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 }
 那么最终，最后一层的所有状态推导后，我们要找最大的结果，即states[4][9]状态所代表的结果，最大值为9

*/
#include <vector>
int knapsack(
	int* weight,//物品重量数组
	size_t n,	//物品个数
	int w		//背包承重
)
{
	//存放状态
	std::vector<std::vector<int>> states(n, std::vector<int>(w + 1, 0));

	//第一层手动处理，作为基准
	states[0][0] = 1;//第一个物品不装
	if (weight[0] <= w)//第一个物品在满足不大于w的情况下装
		states[0][weight[0]] = 1;

	//遍历其他层
	for (int i = 1; i < n; ++i)
	{
		//每一层和第一层一样，两种情况
		//不装
		for (int j = 0; j <= w; ++j)
			if (states[i - 1][j] == 1)
				//也就是继承上一层的所有状态（感觉不用判断直接逐个拷贝过来也是一样的）
				states[i][j] = states[i - 1][j];
		//装
		for (int j = 0; j <= w - weight[i]/* 只需要考虑加上此物品后，不会超过承重的部分 */; ++j)
			if (states[i - 1][j] == 1)
				states[i][j + weight[i]] = 1;
	}

	//打印状态，测试用
	std::cout << "states: " << std::endl;
	for (int i = 0; i < states.size(); ++i)
	{
		for (int j = 0; j < states[i].size(); ++j)
			std::cout << states[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;

	//取出结果
	for (int i = w; i >= 0; --i)
		if (states[n - 1][i] == 1)
			return i;//找到最后一层中满足状态的最大值

	return 0;
}
// 动态规划解决这个问题的时间复杂度为O(n*w)，只是两层for循环，而回溯是O(2^n)
// 空间消耗较多，因为需要一个 n*(w+1) 的二维数组
// 优化
// 上面例子中，我们记录了每一层的状态，实际上，我们最终需要的只是最后一层的状态
// 可以只用一个 w+1 的一维数组记录
int knapsack2(
	int* weight,//物品重量数组
	size_t n,	//物品个数
	int w		//背包承重
)
{
	//只用一维数组记录状态
	std::vector<int> states(w + 1, 0);
	//第一行数据手动计算，作为基础状态
	states[0] = 1;
	if (weight[0] <= w)
		states[weight[0]] = 1;
	//动态规划
	for (int i = 1; i < n; ++i)
		//不装是直接继承，而只用一个一维数组相当于自动继承了前一层的临时状态，所以只需要考虑装的情况
		for (int j = w - weight[i]; j >= 0; --j)
			if (states[j] == 1)
				states[j + weight[i]] = 1;
	//输出结果
	for (int i = n - 1; i >= 0; --i)
		if (states[i] == 1)
			return i;
	return 0;
}
// 此时，要注意的就是，记录状态的数组在前面的几层都作为临时数据
// 每一层都需要倒着来循环计算
// 因为如果正向计算，可能出现某状态还未被使用就被覆盖的情况，信息丢失（或者说重复计算）
// 而动态规划 无后效性 ，后面的状态不影响前面，从后向前计算就不会发生这个情况
// 
// 问题升级：每个物品除了有重量属性，还加上了价值属性
// 在满足背包承重前提下，求可装入物品的最大总价值
// 其实依然很简单，把标记为1的状态改为标记总价值即可
int value[] = { 3,4,8,9,6 };
int knapsack3(
	int* weight,//物品重量数组
	int* value,	//物品价值数组
	size_t n,	//物品个数
	int w		//背包承重
)
{
	//存放状态
	std::vector<std::vector<int>> states(n, std::vector<int>(w + 1, -1));
	//第一层手动处理
	states[0][0] = 0;//不装，价值为0
	if (weight[0] <= w)
		states[0][weight[0]] = value[0];//装，记录价格
	//动态规划，状态转移
	for (int i = 1; i < n; ++i)
	{
		//不装，相当于继承所有上一层的状态
		for (int j = 0; j <= w; ++j)
			if (states[i - 1][j] >= 0)
				states[i][j] = states[i - 1][j];
		//装，则累加价值
		for (int j = 0; j <= w - weight[i]; ++j)
		{
			if (states[i - 1][j] >= 0)
			{
				int v = states[i - 1][j] + value[i];
				//注意的是，继承下来的状态中，可能已经有存在价值的情况，我们只保留价值最大的情况
				if (v > states[i][j + weight[i]])
					states[i][j + weight[i]] = v;
			}
		}
	}
	//在最后一层状态中找出结果
	int max = -1;
	for (int i = 0; i <= w; ++i)
		if (states[n - 1][i] > max)
			max = states[n - 1][i];
	return max;
}
// 时间空间复杂度，都还是O(n*w)
// 同样可以用一个一维数组优化空间
// 
//对比
// 贪心 一条路走到黑，每一次选择当前最优
// 回溯 一条路走到黑，但可以重来走完所有情况，再做选择
// 动态规划 上帝时间，直接推算出所有情况，选择最优
//

int main()
{
	//cal_n_queens(0);
	//std::cout << "cal_n_queens get: " << result_num << " results" << std::endl;

	int ret = knapsack(weight, 5, 9);
	std::cout << "knapsack ret: " << ret << std::endl;
}
