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
//
//动态规划理论 一个模型，三个特征
// 
// 一个模型——多阶段决策最优解模型
// 指的是动态规划适合解决的问题模型 
// 用动态规划解决最优问题，而解决问题的过程经历多个决策阶段
// 每个决策阶段对应一组状态，然后寻找一组决策序列，能够产生最优值
// 
// 三个特征——最优子结构、无后效性、重复子问题
// 问题最优解包含子问题的最优解；也就是后面阶段的状态可以通过前面阶段的状态推导出来
// 推导后面阶段的状态时，只关心前一阶段状态，不关心过程；某阶段状态一旦确定，就不受之后阶段决策影响
// 不同的决策序列，到达某个相同阶段时，可能回产生重复的状态；也就是重复状态可合并
// 
//解题思路
// 状态转移表
// 先用回溯算法，暴力枚举所有可能，然后画出递归树
// 在递归树中总结是否存在重复子问题，以及重复子问题如何产生
// 寻找规律，看如何处理
// 一是用 回溯+备忘录，避免重复子问题
// 二就是 动态规划的状态转移表
// 也就是上面例子中的方法，用多维数组表示一组状态，可以先画图自己推，然后翻译成代码
// 例 求矩阵中左上角到右上角的最短路径
int matrix[4][4] = {
	{1,3,5,9},
	{2,1,3,4},
	{5,2,6,7},
	{6,8,4,3}
};
// 先用回溯
int matrix_size = 4;
int min_dist = 0;
void min_dist_f(
	int i,//行
	int j,//列
	int dist//走到当前位置的路径长
)
{
	if (i == matrix_size && j == matrix_size)//走到(n-1,n-1)这个位置，说明到了终点
	{
		if (dist < min_dist)
			min_dist = dist;//如果当前情况路径更短，则记录
		return;
	}
	//每一步决策只有两种可能
	//往下
	if (i < matrix_size)
		min_dist_f(i + 1, j, dist + matrix[i][j]);
	//往右
	if (j < matrix_size)
		min_dist_f(i, j + 1, dist + matrix[i][j]);

	/*
	分析递归树
	f(0,0,1)
	f(1,0,3)			f(0,1,4)
	f(2,0,8) f(1,1,4)	f(1,1,5) f(0,2,9)
	到此处，已经发现，对于i,j都是1的情况有两种
	而此时，我们其实只需要计算更小的情况即可，也就是f(1,1,5)分支之后的可以舍弃了

	画一个二维状态表，行列表示棋子所在位置，数值表示从起点到这个点的最短路径
	states[0] = { 1, 4, 9, 18 } //第一行为与前面累加
	states[1] = { 3, min(3+1,4+1) = 4, min(4+3,9+3) = 7, min(7+4,18+4) = 11}//后面行开始，每格状态为从左边或从上面走过来的路径最小值）
	states[2] = { 8, 6, 12, 18 }
	states[3] = { 14, 14, 16, 19 }
				//第一列为与前面累加
	*/
}
// 将上述分析过程，翻译成动态规划代码
#define min(a,b) (((a) < (b)) ? (a) : (b))
int min_dist_f()
{
	int states[4][4] = { 0 };
	//初始化第一行和第一列值
	states[0][0] = matrix[0][0];
	for (int i = 1; i < 4; ++i)
	{
		states[0][i] = states[0][i - 1] + matrix[0][i];
		states[i][0] = states[i - 1][0] + matrix[i][0];
	}
	//动态规划填写后面的状态
	for (int i = 1; i < 4; ++i)
		for (int j = 1; j < 4; ++j)
			states[i][j] = matrix[i][j] + min(states[i - 1][j], states[i][j - 1]);
	//打印结果看下
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			std::cout << states[i][j] << " ";
		std::cout << std::endl;
	}

	//返回结果
	return states[3][3];
}
//
// 状态转移方程法
// 利用递归，分析某问题如何分解子问题（非常类似于回溯的递归+备忘录）
// 还有一种是迭代递推
// 例如上面问题，抽象为方程
// min_dist(i,j) = matrix[i][j] + min(min_dist(i,j-1), min_dist(i-1,j))
int mem[4][4] = { 0 };
int min_dist_f_mem(int i, int j)//调用入口min_dist_f(n-1,n-1);向前递归
{
	if (i == 0 && j == 0) return matrix[0][0];//起点值作为递归终点
	if (mem[i][j] > 0) return mem[i][j];//计算过的值无须重复计算
	int min_left = 0;
	if (j - 1 >= 0)
		min_left = min_dist_f_mem(i, j - 1);//寻找左边的路
	int min_up = 0;
	if (i - 1 >= 0)
		min_up = min_dist_f_mem(i - 1, j);//寻找上边的路

	//计算当前位置从左边或从上边过来最短的路径
	int min_dist = matrix[i][j] + min(min_left, min_up);
	mem[i][j] = min_dist;
	return min_dist;
}
// 
//四种算法对比
// 贪心、回溯、动态规划其实都可以化为一类
// 都是需要多阶段决策，然后求最优解
// 分治算法可以单独分为一类
// 回溯比较通用，因为是一种暴力枚举，但时间复杂度为指数级
// 动态规划更高效，但不一定所有问题都能抽象出一个规律
// 贪心是动态规划的一种特殊情况，最高效，但不一定是最优解
// 
// 
//动态规划实战
// 实现搜索引擎中的拼写纠错功能
// 
// 量化两个字符串的相似度——编辑距离
// 指的是 
// 将一个字符串转化成另一个字符串，需要的最少编辑操作次数（增加、删除、替换一个字符）
// 编辑距离越大，说明两个字符串相似度越小，反之则越大
// 两个相同字符串编辑距离为0
// 
// 编辑距离的两种计算方式
// 莱文斯坦距离 允许增加、删除、替换三个编辑操作，表示两个字符串差异大小
// 最长公共子串长度 允许增加、删除两种编辑操作，表示两个字符串相似程度大小
// 例 mitcmu 与 mtacnu
// 莱文斯坦距离 是前者去掉i，后者去掉a并将n替换为m 距离为3
// 最长公共子串 是看两个串中公共的部分 mtcu 长度为4
// 
// 代码求解莱文斯坦距离
// 分析
// 相当于把一个字符串a变成。、另一个字符串b，需要的最少编辑次数
// 整个过程涉及多个决策阶段
// 依次比较a[i]b[j]
// 匹配则继续考察a[i+1]b[j+1]
// 不匹配有多种处理方式
// 删除a[i]，继续考察a[i+1]和b[j]
// 删除b[j]，继续考察a[i]和b[j+1]
// 可以在a[i]前添加一个与b[j]相同字符，继续递归考察a[i]和b[j+1]
// 在b[j]前添加一个与a[i]相同字符，继续考察a[i+1]和b[j]
// 可以将a[i]替换成b[j]，或者b[j]替换成a[i]，然后递归考察a[i+1]和b[j+1]
// （实际编写中，并不真的操作，只是假设，然后累加距离）
// 先使用回溯求解
char a[6] = { 'm','i','t','c','m','u' };
char b[6] = { 'm','t','a','c','n','u' };
int n = 6, m = 6, min_dist = 0;
void lwst(int i, int j, int edist)
{
	if (i == n || j == m)//其中一个字符串考察结束
	{
		if (i < n) edist += n - i;//剩下的字符数都算进差异距离中
		if (j < m) edist += m - j;
		if (edist < min_dist) min_dist = edist;
		return;
	}
	//两字符匹配
	if (a[i] == b[j])
		lwst(i + 1, j + 1, edist);
	else
	{
		lwst(i + 1, j, edist + 1);//假设删除a[i]或b[j]前加字符
		lwst(i, j + 1, edist + 1);//假设删除b[j]或a[i]前加字符
		lwst(i + 1, j + 1, edist + 1);//假设a[i]或b[j]替换对方
	}

	/*
	分析递归树
	(0,0,0)
	(1,1,0) 第一个字符相同
	(2,1,1) 字符串a后移一位 (1,2,1)字符串b后移一位 (2,2,1)替换其一
	(3,2,1) 字符a[2]与b[1]相同 ...				   (3,2,2)从(2,2,1)情况，继续后移a
	到此可见有重复操作(3,2)，可只保留dist最小的(3,2,1)
	*/
}
// 此例状态转移相对复杂
// (i,j,min_dist)由三种状态转移过来
// (i-1,j,min_dist)(i,j-1,min_dist)(i-1,j-1,min_dist)
// 那么，状态转移方程
// min_dist(i,j) = min(min_dist(i-1,j)+1,min_edist(i,j-1)+1,min_dist(i-1,j-1)+1) （如果ij相同，则第三个数是min_dist(i-1,j-1)）
// 填充状态表
//		m	t	a	c	n	u
// m	0	1	2	3	4	5
// i	1	1	2	3	4	5
// t	2	1	2	3	4	5
// c	3	2	2	2	3	4
// m	4	3	3	3	3	4
// u	5	4	4	4	4	3
// 根据推导的方程和表格，翻译成动态规划代码
int min3(int x, int y, int z)//三数比较辅助函数
{
	int ret = x;
	if (y < ret) ret = y;
	if (z < ret) ret = z;
	return ret;
}
int lwst()
{
	std::vector<std::vector<int>> states(n, std::vector<int>(m, 0));
	//初始化第一行编辑距离状态
	for (int i = 0; i < m; ++i)
	{
		if (a[0] == b[i]) states[0][i] = i;//相当于直接移除b[i]前面的字符，距离就是i
		else if (i != 0) states[0][i] = states[0][i - 1] + 1;//字符不相同，就是前面距离加1
		else states[0][i] = 1;//对应第一个字符就不相同的情况，也就是将states[0][0]填充为1
	}
	//第一列，与第一行同理
	for (int i = 0; i < n; ++i)
	{
		if (a[i] == b[0]) states[i][0] = i;
		else if (i != 0) states[i][0] = states[i - 1][0] + 1;
		else states[i][0] = 1;
	}
	//填写剩下的状态，从三个之前的路径中找最小
	for (int i = 1; i < n; ++i)
	{
		for (int j = 1; j < m; ++j)
		{
			//当前比较字符是否相同，分两种情况
			if (a[i] == b[j])
				states[i][j] = min3(states[i - 1][j] + 1, states[i][j - 1] + 1, states[i - 1][j - 1]);
			else
				states[i][j] = min3(states[i - 1][j] + 1, states[i][j - 1] + 1, states[i - 1][j - 1] + 1);
		}
	}
	//取出结果
	return states[n - 1][m - 1];
}
//
//



//
//跳表
// 类似数组的二分查找，可以实现一种结构，对链表进行二分查找
// 
//理解
// 对于单链表，即使是有序数据，想要查询某个数据，也只能从头到尾遍历，复杂度O(n)
// 可以对链表建立一级索引，每两个节点提取一个，每个提取出来的节点新增一个指针指向下级节点
// 在一级索引之上，可以再建立索引层，直到只有两个节点（此时就是链的头节点和中间位置节点，起到二分的作用）
// 
// 1 ——————》  3
// 1 ——》 2 ——》 3 ——》 4 ——》 5
// ...
//
//复杂度分析
// k级索引结点数为n/2^k
// 跳表高度为log2n
// 由于每级索引都是每两个节点建立一个，所以每一层最多只需要遍历3个节点
// 那么查询时间就是 3*log2n
// 时间复杂度O(logn)
// 
//内存
// 几级索引的节点数为
// n/2+n/4+...+4+2 = n - 2
// 就相当于额外还需要一个链表长度的空间
// 空间复杂度O(n)
// 但其实，索引不需要直接存储对象，只要存用于比较大小的关键值和两个指针就好
// 所以如果对象比较大，空间的浪费也并不多
// 
//动态更新索引
// 插入操作较多时，如果只插入，在一个区间中有很多节点，那么再查询时，几乎相当于退化成了链表
// 可以通过一个随机函数，选择性将插入的数据也建立索引到随机函数结果所在索引层（具体实现先略过了）
//

//
//拓扑排序
// 
//问题引入：如何确定代码源文件的编译依赖关系
// 比如A.cpp依赖B.cpp，那么需要先编译B，再编译A
// 编译器通过编译配置文件（如makefile）来获取局部依赖关系
// 之后通过局部依赖关系，确定一个全局的编译顺序
// 如 A依赖B B依赖C D依赖B
// 则 编译顺序为
//	C-》B-》A-》D 或
//	C-》B-》D-》A
// 此类问题，一般通过 图 这种结构的 拓扑排序算法 实现
// 基于 有向无环图
// 比如上面A依赖B，则在B到A之间建立一条有向边
// 
//两种实现
// Kahn算法
// 实际上是贪心算法
// 在两个顶点间，如果有依赖关系，则建立一条有向边
// 若某顶点的入度为0，则可以作为开始执行的起点（第一个编译的文件）
// 逐轮遍历图，每轮将入度为0的点入队并执行
/*
伪代码
void kahn()
{
	int in_degree[v];//v为顶点数
	for (int i = 0; i < v; ++i)//邻接表形式（数组存链表形式）
		for (int j = 0; j < adj[i].size(); ++j)
			in_degree[adj[i][j]]++;//计算所有顶点的入度

	queue q;
	for (int i = 0; i < v; ++i)
		if (in_degree[i] == 0)
			q.push(i);//入度为0的入队
	//开始执行
	while (!queue.empty())
	{
		int i = q.top();
		q.pop();//模拟执行入度为0的顶点
		std::cout << "->" << i;
		//执行的同时，继续将被依赖的已执行节点后的图顶点入队
		for(int j = 0; j < adj[i].size(); ++j)
		{
			int k = adj[i][j];
			//其余的节点，先都降低入度，表示前面的依赖已经完成
			--in_degree[k];
			if (in_degree[k] == 0)
				q.push(k);//新一轮入度为0的可执行顶点入队
		}
	}
}
*/
// 
// DFS深度优先搜索
// 通过邻接表构造逆邻接表
// 递归处理每个顶点，先输出可达的所有顶点，最后输出自己
//

//
//最短路径
// 
//问题引入：地图软件的路线规划是如何实现的
// 
//分析
// 路线最优规划一般分几类 路线最短、最少用时、最少红绿灯
// 抽象模型
// 地图抽象为图结构，每个岔路口看作一个顶点，岔路口之间的路作为边
// 单行道则顶点间画一条有向边，双行道则是两条边
// 边又有路径长度
// 则整个地图可抽象为——有向有权图
// 
//经典的最短路径算法（单源最短路径，也就是一个顶点到一个顶点）
// Dijkstra算法
// 使用小顶堆，把起始顶点入堆
// 接着，将起始顶点出队，并考察起始顶点可达的所有顶点
// 根据权重，一路考察，直到终点t或队列为空
//

//
//A*搜索
// 
//问题引入：游戏自动寻路
// 
//对Dijkstra算法的改造
// 主要区别
// 优先队列构建方式不同 A*根据估价函数 Dijkstra根据距离dist
// Dijkstra在终点出队时结束，A*是只要遍历到终点就结束
// 
// A*的目的是更快的选出一条近似最佳路径的路径
// 
// 对于最短路径问题
//	回溯穷举所有情况，然后选出最短
//	Dijkstra在此基础上，相当于用了动态规划思想，剪枝，只保留起点到某顶点最短（但也是考察了所有路线，得到最优解）
//	A*就是在Dijkstra基础上，把while循环的结束条件改为了遇到一种情况时就结束，即不一定最优的路径
// 
//启发式搜索算法
// 除了A*，还有IDA*、蚁群、遗传、模拟退火等
// 依赖于 估价函数，可以避免“跑偏”（虽然当前路径最短但距离终点更远的情况）
//



//
//B+树
// 
//问题引入：数据库索引如何实现
// 
//散列表查询性能好，但不能支持区间查找
//平衡二叉树也是
//跳表可以解决
//
//B+树类似跳表，是由二叉查找树演化
/*
数据 6、10、15、23、27、33、42

建立二叉搜索树

				23
		10				33
	6		13		27		42
改造为B+树，树节点不存放数据本身，而是作为索引，并把所有叶子节点串在链上
						27
			15						42
		10		23				33		42
	  6	  10 15		23		27	  33		42
很像跳表
	就是将跳表抽索引的思想建立成树
查询时
	如果查找区间值[7,30]
	则把起始值在树中查找，找到某叶子节点，此处为6
	则从6开始，顺着叶子节点串成的链表开始遍历，直到链表中节点大于区间终止值
	也就是 27 -》 15 -》 10 -》 6 -》 [ 10 -》 15 -》 23 -》 27 ] -》 33
*/
// 在上亿数据构建索引，如果是存储在内存中，占用过多
// 可以将索引放在硬盘中（只有根放内存）
// 但硬盘的问题就是速度太慢，需要减少IO操作
// 对于索引的查找，每一层只会访问一个节点，之后就根据当前节点值往左或往右进行下一层了
// 所以减少IO操作就是要减少树的高度
// 此时
// 可以把索引构建成m叉树
constexpr int M = 5; //5叉树
class BPlusTreeNode {
public://索引节点
	int keywords[M - 1];//键值，划分数据区间
	BPlusTreeNode* children[M];//子节点
	/*
	关于keywords，例如 3，5，8，10
	则4个键值将数据分为5个区间
	5个子节点对应区间 (-inf,3)[3,5)[5,8)[8,10)[10,inf)
	*/
};
constexpr int K = 3;//K为计算值，依据是让所有信息大小刚好等于页大小
// * PAGE_SIZE = k*4[keyw..大小]+k*8[dataAd..大小]+8[prev大小]+8[next大小]
class BPlusTreeLeafNode {
public://叶子节点，也就是具体数据节点
	int keywords[K];//数据的键值
	long dataAddress[K];//数据地址
	BPlusTreeLeafNode* prev;
	BPlusTreeLeafNode* next;//串成双链表
};
// M越大，层越小，但如何确定M多大合适
// 操作系统按页进行IO读取（内存和磁盘一般都是4K）
// 一次至少读一页，超过会触发多次读多页
// 所以，要预先测算，尽量让每个节点大小等于一个页大小
// 则读取一个节点时，就只需要一次磁盘IO，提高效率
// 
//另外，平时使用时会发现，索引会让数据写入变慢
// 主要就是因为数据写入时，涉及索引更新
// M根据页大小实现计算好，而写入过程中，使索引中某些节点子节点数超过了m
// 那么可能超过一个页大小，导致多次磁盘IO
// 可以分裂此节点（导致父节点子节点变多，继续往上依次分裂）
// 
//除了B+树
// 还有B树或B-树（不是减，只是破折号）
// 它们是B树的低级版本，或者说B+树是它们的改进版
// B树的非叶子节点也存储数据，并不只是索引
// B树的叶子节点也没有用链表串联
//

int main()
{
	//cal_n_queens(0);
	//std::cout << "cal_n_queens get: " << result_num << " results" << std::endl;

	//int ret = knapsack(weight, 5, 9);
	//std::cout << "knapsack ret: " << ret << std::endl;

	int ret = min_dist_f();
	std::cout << "min_dist_f ret: " << ret << std::endl;
}
