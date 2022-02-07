#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//回溯

//利用回溯算法求解八皇后问题
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

//利用回溯算法求解 0 - 1 背包问题
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

//分治

//利用分治算法求一组数据的逆序对个数
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


//动态规划

//0 - 1 背包问题
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
}//回溯加备忘录
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
}//动态规划，状态转移表
//转移表优化为一维
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

//编程实现莱文斯坦最短编辑距离
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

//编程实现查找两个字符串的最长公共子序列 /problems/longest-common-subsequence/
int longestCommonSubsequence(string text1, string text2) {
	int n = text1.size(), m = text2.size();
	vector<vector<int>> memo(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (text1[i] == text2[j])
				memo[i][j] = i == 0 || j == 0 ? 1 : 1 + memo[i - 1][j - 1];//也可以手动初始化第一行第一列
			else
				memo[i][j] = max(i == 0 ? 0 : memo[i - 1][j], j == 0 ? 0 : memo[i][j - 1]);
		}
	}
	return memo[n - 1][m - 1];

	//或者提前空出一行一列
	string a, b;
	int n1 = a.size();
	int n2 = b.size();
	vector<vector<int>>dp(n1 + 1, vector<int>(n2 + 1, 0));
	for (int i = 1; i <= n1; i++) {
		for (int j = 1; j <= n2; j++) {
			if (a[i - 1] == b[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;//相同的长度加一
			}
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);//不同的按左和上两条路径看哪个最大
			}
		}
	}
	return dp[n1][n2];
}

//编程实现一个数据序列的最长递增子序列 /problems/longest-increasing-subsequence/
int lengthOfLIS(vector<int>& nums) {
	int n = nums.size();
	vector<int> dp(n, 1);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < i; ++j)
			if (nums[i] > nums[j] && dp[i] < dp[j] + 1)
				dp[i] = dp[j] + 1;
	return *max_element(dp.begin(), dp.end());
}


//LeetCode

//Regular Expression Matching（正则表达式匹配）/problems/regular-expression-matching/
bool isMatch(string s, string p) {
	/**
	 * f[i][j]: if s[0..i-1] matches p[0..j-1]
	 * if p[j - 1] != '*'
	 *      f[i][j] = f[i - 1][j - 1] && s[i - 1] == p[j - 1]
	 * if p[j - 1] == '*', denote p[j - 2] with x
	 *      f[i][j] is true iff any of the following is true
	 *      1) "x*" repeats 0 time and matches empty: f[i][j - 2]
	 *      2) "x*" repeats >= 1 times and matches "x*x": s[i - 1] == x && f[i - 1][j]
	 * '.' matches any single character
	 */
	int m = s.size(), n = p.size();
	vector<vector<bool>> f(m + 1, vector<bool>(n + 1, false));

	f[0][0] = true;
	for (int i = 1; i <= m; i++)
		f[i][0] = false;
	// p[0.., j - 3, j - 2, j - 1] matches empty iff p[j - 1] is '*' and p[0..j - 3] matches empty
	for (int j = 1; j <= n; j++)
		f[0][j] = j > 1 && '*' == p[j - 1] && f[0][j - 2];

	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			if (p[j - 1] != '*')
				f[i][j] = f[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '.' == p[j - 1]);
			else
				// p[0] cannot be '*' so no need to check "j > 1" here
				f[i][j] = f[i][j - 2] || (s[i - 1] == p[j - 2] || '.' == p[j - 2]) && f[i - 1][j];

	return f[m][n];
}

//Minimum Path Sum（最小路径和）/problems/minimum-path-sum/
int minPathSum(vector<vector<int>>& grid) {
	int m = grid.size();
	int n = grid[0].size();
	vector<vector<int>> dp(m, vector<int>(n, 0));
	dp[0][0] = grid[0][0];
	for (int i = 1; i < m; i++)
		dp[i][0] = dp[i - 1][0] + grid[i][0];
	for (int j = 1; j < n; j++)
		dp[0][j] = dp[0][j - 1] + grid[0][j];
	for (int i = 1; i < m; i++)
		for (int j = 1; j < n; j++)
			dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
	return dp[m - 1][n - 1];
}

//Coin Change （零钱兑换）/problems/coin-change/（背包问题）
//回溯
int helper(vector<int>& coins, int n, int sum) {
	//why INT_MAX-1 => Because later we are adding 1 while returning the value, so if we return INT_MAX here, doing INT_MAX+1 will cross the range of integer.
	if (n <= 0) return INT_MAX - 1;
	if (sum == 0) return 0;

	//Unbounded Knapsack Code
	if (coins[n - 1] <= sum) {
		return min(1 + helper(coins, n, sum - coins[n - 1]), helper(coins, n - 1, sum));
	}
	else return helper(coins, n - 1, sum);
}
int coinChange(vector<int>& coins, int sum) {
	int n = coins.size();
	int res = helper(coins, n, sum);
	return (res == INT_MAX || res == INT_MAX - 1) ? -1 : res;


	//动态规划
	int n = coins.size();
	vector<vector<int>> t(n + 1, vector<int>(sum + 1));

	//Initialization
	for (int i = 0; i < sum + 1; i++) t[0][i] = INT_MAX - 1;
	for (int j = 1; j < n + 1; j++) t[j][0] = 0;

	//Unbounded Knapsack
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < sum + 1; j++) {
			if (coins[i - 1] <= j) {
				t[i][j] = min(1 + t[i][j - coins[i - 1]], t[i - 1][j]);
			}
			else {
				t[i][j] = t[i - 1][j];
			}
		}
	}
	return (t[n][sum] == INT_MAX || t[n][sum] == INT_MAX - 1) ? -1 : t[n][sum];
}

//Best Time to Buy and Sell Stock（买卖股票的最佳时机）/problems/best-time-to-buy-and-sell-stock/
int maxProfit(vector<int>& prices) {

	int profit = 0;
	int minvalue = INT_MAX;

	for (int i = 0; i < prices.size(); i++)
	{
		minvalue = min(minvalue, prices[i]);
		profit = max(profit, prices[i] - minvalue);
	}

	return profit;

}

//Maximum Product Subarray（乘积最大子序列）/problems/maximum-product-subarray/
int maxProduct(vector<int>& A) {
	vector<int> dpMin(A), dpMax(A);
	int ans = A[0];
	for (int i = 1; i < size(A); i++) {
		dpMin[i] = min(A[i], A[i] * (A[i] >= 0 ? dpMin[i - 1] : dpMax[i - 1]));
		dpMax[i] = max(A[i], A[i] * (A[i] >= 0 ? dpMax[i - 1] : dpMin[i - 1]));
		ans = max(ans, dpMax[i]);
	}
	return ans;
}
//优化空间
int maxProduct(vector<int>& A) {
	int ans = A[0], dpMin = A[0], dpMax = A[0];
	for (int i = 1; i < size(A); i++) {
		auto prevDpMin = dpMin, prevDpMax = dpMax;
		dpMin = min(A[i], A[i] * (A[i] >= 0 ? prevDpMin : prevDpMax));
		dpMax = max(A[i], A[i] * (A[i] >= 0 ? prevDpMax : prevDpMin));
		ans = max(ans, dpMax);
	}
	return ans;
}

//Triangle（三角形最小路径和）/problems/triangle/
int minimumTotal(vector<vector<int>>& triangle) {
	int n = triangle.size();
	for (int i = n - 2; i >= 0; i--) {
		for (int j = 0; j < triangle[i].size(); j++) {
			triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
		}
	}
	return triangle[0][0];
}