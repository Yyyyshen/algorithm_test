#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//����

//���û����㷨���˻ʺ�����
#define N_QUEENS 8
int* result = new int[N_QUEENS];//��Ž�����±���Ϊ�У�ֵ��ʾQueen�����ĸ���
int result_num = 0;
bool is_ok(int row, int col);//�����߼��������ж��ڴ�λ�÷���Queen�Ƿ�Ϸ�
void print_queens();
void cal_n_queens(int row)	//��ڵ���cal_n_queens(0)�ӵ�һ�п�ʼ
{
	if (row == N_QUEENS)//���һ��Ҳ�ź��ˣ���ӡ���˳�
	{
		print_queens();
		++result_num;
		return;
	}

	//���ŵ�ÿһ�е����
	for (int col = 0; col < N_QUEENS; ++col)
	{
		if (is_ok(row, col))//���ڴ�λ�úϷ�
		{
			result[row] = col;//��¼һ�£����֮��ĳһ���޷����������ݻ����ҵ�������������λ�ú�Ҳ����и���
			cal_n_queens(row + 1);//�ӵ�ǰ�������������һ��
			//��֮��ĳһ�β����㣬��һ�����˻أ��ټ�����ѭ�����ҷ������������
			//��֮���ҵ���һ�����������Ҳ�᷵�����������������ܽ��
		}
	}
}
bool is_ok(int row, int col)
{
	int leftup = col - 1, rightup = col + 1;
	//���������м�飬ֻ��Ҫ���Ͽ���֮ǰ��ÿһ��
	for (int i = row - 1; i >= 0; --i)
	{
		//��ǰ�в���Ҫ���죬��Ϊ�趨�Ͼ���ÿ��ֻ��һ��
		if (result[i] == col) return false;//��һ�е�ǰ��������������
		//���Խ���
		//����
		if (leftup >= 0)
			if (result[i] == leftup)
				return false;
		//����
		if (rightup < N_QUEENS)
			if (result[i] == rightup)
				return false;
		//Ϊ����һ�жԽ��߱Ƚ���׼��
		--leftup; ++rightup;
	}
	//��鶼���ϣ�����true
	return true;
}
void print_queens()
{
	for (int row = 0; row < N_QUEENS; ++row)
	{
		for (int col = 0; col < N_QUEENS; ++col)
		{
			if (result[row] == col)
				std::cout << "Q ";//��ӡ����Queen��λ��
			else
				std::cout << "* ";//��ӡ��ͨ����
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

//���û����㷨��� 0 - 1 ��������
#define W_BAG 100//��������
#define N_ITEM 10//��ѡ��Ʒ����
int* items = new int[N_ITEM];//���ÿ����Ʒ����������
int maxW = 0;//��¼��װ���ֵ
void bag_0_1(	//������� bag_0_1(0,0);
	int i,//��ʾ���е��ĸ���Ʒ
	int cw//��ǰ�Ѿ�װ�˶�������
)
{
	if (cw == W_BAG || i == N_ITEM)//װ�����ѷ���������Ʒ����Ϊһ�ν���Ľ�������
	{
		if (cw > maxW)
			maxW = cw;//����֮ǰ��¼���Ľ�������¼
		return;
	}

	//ÿ����Ʒ��Ϊ����������൱��ö��2^n�����
	//��װ
	bag_0_1(i + 1, cw);//�������ۼ�
	//װ��������������û����ʱ��װ
	if (cw + items[i] <= W_BAG)
		bag_0_1(i + 1, cw + items[i]);
}

//����

//���÷����㷨��һ�����ݵ�����Ը���
int num;//����
void merge_sort_counting(int* a, int p, int r);//��������
void merge(int* a, int p, int q, int r);//��С������ִ�е��߼�
int count(int* a, size_t n)//����Լ���
{
	n = 0;
	merge_sort_counting(a, 0, n - 1);
	return num;
}
void merge_sort_counting(int* a, int p, int r)
{
	if (p >= r) return;//���仮����ֹ��
	int q = (p + r) / 2;//�������䣬�͹鲢һ��
	merge_sort_counting(a, p, q);//�ݹ�ֵ���С
	merge_sort_counting(a, q + 1, r);
	//ִ��ÿ�����ڴ����߼����Լ��ϲ��ӻ���������
	merge(a, p, q, r);
}
void merge(int* a, int p, int q, int r)
{
	int i = p, j = q + 1, k = 0;//�������俪ͷ��ʼ����k��Ϊ����������±��¼
	int* tmp = new int[r - p + 1];//��źϲ�����
	while (i <= q && j <= r)//����ͬ���Ȳ���
	{
		if (a[i] <= a[j])//˳���ֱ�Ӵ��뻺������
			tmp[k++] = a[i++];
		else
		{
			num += (q - i + 1);//ͳ��pq֮�䣬��a[j]���Ԫ�ظ�������Ҳ�Ǵ�����鲢�����Ψһ����
			//����Ϊ�������䶼�Ѿ��������ˣ����Դ�ʱ���a[i]>a[j]��i��q֮��һ��������a[j]��
			tmp[k++] = a[j++];
		}
	}
	//�������У�ÿ������ʣ�µĲ���
	while (i <= q)
		tmp[k++] = a[i++];
	while (j <= r)
		tmp[k++] = a[j++];

	//��������Ĳ��֣�������ԭ����
	for (int i = 0; i <= r - q; ++i)
		a[p + i] = tmp[i];

	delete[] tmp;//ɾ������
}


//��̬�滮

//0 - 1 ��������
int maxRet = 0;//��¼�����
int weight[] = { 2,2,4,6,3 };//����Ʒ����
int n = 5;//��Ʒ����
int w = 9;//��������
bool mem[5][10] = { false };//����¼
void bag_0_1_mem(
	int i,//��ʾ��鵽�ڼ�����Ʒ
	int cw//��ʾ�Ѿ��ۼ��˶�������
)
{
	if (cw == w || i == n)
	{
		//װ������������Ʒ�������
		//��֮ǰ��¼���Ĵ����¼
		if (cw > maxRet) maxRet = cw;
		return;
	}
	//��鱸��¼
	if (mem[i][cw]) return;//��鵽��i����Ʒ�����ۼ�������֮ǰ������ظ��ˣ����i֮��ĸ������Ҳ���ظ��ģ��Ͳ�������һ����
	//���滹��һ��
	bag_0_1_mem(i + 1, cw);//��װ��ǰ��Ʒ
	if (cw + weight[i] <= w)
		bag_0_1_mem(i + 1, cw + weight[i]);//װ��ǰ��Ʒ
}//���ݼӱ���¼
int knapsack(
	int* weight,//��Ʒ��������
	size_t n,	//��Ʒ����
	int w		//��������
)
{
	//���״̬
	std::vector<std::vector<int>> states(n, std::vector<int>(w + 1, 0));

	//��һ���ֶ�������Ϊ��׼
	states[0][0] = 1;//��һ����Ʒ��װ
	if (weight[0] <= w)//��һ����Ʒ�����㲻����w�������װ
		states[0][weight[0]] = 1;

	//����������
	for (int i = 1; i < n; ++i)
	{
		//ÿһ��͵�һ��һ�����������
		//��װ
		for (int j = 0; j <= w; ++j)
			if (states[i - 1][j] == 1)
				//Ҳ���Ǽ̳���һ�������״̬���о������ж�ֱ�������������Ҳ��һ���ģ�
				states[i][j] = states[i - 1][j];
		//װ
		for (int j = 0; j <= w - weight[i]/* ֻ��Ҫ���Ǽ��ϴ���Ʒ�󣬲��ᳬ�����صĲ��� */; ++j)
			if (states[i - 1][j] == 1)
				states[i][j + weight[i]] = 1;
	}

	//��ӡ״̬��������
	std::cout << "states: " << std::endl;
	for (int i = 0; i < states.size(); ++i)
	{
		for (int j = 0; j < states[i].size(); ++j)
			std::cout << states[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;

	//ȡ�����
	for (int i = w; i >= 0; --i)
		if (states[n - 1][i] == 1)
			return i;//�ҵ����һ��������״̬�����ֵ

	return 0;
}//��̬�滮��״̬ת�Ʊ�
//ת�Ʊ��Ż�Ϊһά
int knapsack2(
	int* weight,//��Ʒ��������
	size_t n,	//��Ʒ����
	int w		//��������
)
{
	//ֻ��һά�����¼״̬
	std::vector<int> states(w + 1, 0);
	//��һ�������ֶ����㣬��Ϊ����״̬
	states[0] = 1;
	if (weight[0] <= w)
		states[weight[0]] = 1;
	//��̬�滮
	for (int i = 1; i < n; ++i)
		//��װ��ֱ�Ӽ̳У���ֻ��һ��һά�����൱���Զ��̳���ǰһ�����ʱ״̬������ֻ��Ҫ����װ�����
		for (int j = w - weight[i]; j >= 0; --j)
			if (states[j] == 1)
				states[j + weight[i]] = 1;
	//������
	for (int i = n - 1; i >= 0; --i)
		if (states[i] == 1)
			return i;
	return 0;
}
// ��ʱ��Ҫע��ľ��ǣ���¼״̬��������ǰ��ļ��㶼��Ϊ��ʱ����
// ÿһ�㶼��Ҫ������ѭ������
// ��Ϊ���������㣬���ܳ���ĳ״̬��δ��ʹ�þͱ����ǵ��������Ϣ��ʧ������˵�ظ����㣩
// ����̬�滮 �޺�Ч�� �������״̬��Ӱ��ǰ�棬�Ӻ���ǰ����Ͳ��ᷢ��������

//���ʵ������˹̹��̱༭����
// ����
// �൱�ڰ�һ���ַ���a��ɡ�����һ���ַ���b����Ҫ�����ٱ༭����
// ���������漰������߽׶�
// ���αȽ�a[i]b[j]
// ƥ�����������a[i+1]b[j+1]
// ��ƥ���ж��ִ���ʽ
// ɾ��a[i]����������a[i+1]��b[j]
// ɾ��b[j]����������a[i]��b[j+1]
// ������a[i]ǰ���һ����b[j]��ͬ�ַ��������ݹ鿼��a[i]��b[j+1]
// ��b[j]ǰ���һ����a[i]��ͬ�ַ�����������a[i+1]��b[j]
// ���Խ�a[i]�滻��b[j]������b[j]�滻��a[i]��Ȼ��ݹ鿼��a[i+1]��b[j+1]
// ��ʵ�ʱ�д�У�������Ĳ�����ֻ�Ǽ��裬Ȼ���ۼӾ��룩
// ��ʹ�û������
char a[6] = { 'm','i','t','c','m','u' };
char b[6] = { 'm','t','a','c','n','u' };
int n = 6, m = 6, min_dist = 0;
void lwst(int i, int j, int edist)
{
	if (i == n || j == m)//����һ���ַ����������
	{
		if (i < n) edist += n - i;//ʣ�µ��ַ�����������������
		if (j < m) edist += m - j;
		if (edist < min_dist) min_dist = edist;
		return;
	}
	//���ַ�ƥ��
	if (a[i] == b[j])
		lwst(i + 1, j + 1, edist);
	else
	{
		lwst(i + 1, j, edist + 1);//����ɾ��a[i]��b[j]ǰ���ַ�
		lwst(i, j + 1, edist + 1);//����ɾ��b[j]��a[i]ǰ���ַ�
		lwst(i + 1, j + 1, edist + 1);//����a[i]��b[j]�滻�Է�
	}

	/*
	�����ݹ���
	(0,0,0)
	(1,1,0) ��һ���ַ���ͬ
	(2,1,1) �ַ���a����һλ (1,2,1)�ַ���b����һλ (2,2,1)�滻��һ
	(3,2,1) �ַ�a[2]��b[1]��ͬ ...				   (3,2,2)��(2,2,1)�������������a
	���˿ɼ����ظ�����(3,2)����ֻ����dist��С��(3,2,1)
	*/
}
// ����״̬ת����Ը���
// (i,j,min_dist)������״̬ת�ƹ���
// (i-1,j,min_dist)(i,j-1,min_dist)(i-1,j-1,min_dist)
// ��ô��״̬ת�Ʒ���
// min_dist(i,j) = min(min_dist(i-1,j)+1,min_edist(i,j-1)+1,min_dist(i-1,j-1)+1) �����ij��ͬ�������������min_dist(i-1,j-1)��
// ���״̬��
//		m	t	a	c	n	u
// m	0	1	2	3	4	5
// i	1	1	2	3	4	5
// t	2	1	2	3	4	5
// c	3	2	2	2	3	4
// m	4	3	3	3	3	4
// u	5	4	4	4	4	3
// �����Ƶ��ķ��̺ͱ�񣬷���ɶ�̬�滮����
int min3(int x, int y, int z)//�����Ƚϸ�������
{
	int ret = x;
	if (y < ret) ret = y;
	if (z < ret) ret = z;
	return ret;
}
int lwst()
{
	std::vector<std::vector<int>> states(n, std::vector<int>(m, 0));
	//��ʼ����һ�б༭����״̬
	for (int i = 0; i < m; ++i)
	{
		if (a[0] == b[i]) states[0][i] = i;//�൱��ֱ���Ƴ�b[i]ǰ����ַ����������i
		else if (i != 0) states[0][i] = states[0][i - 1] + 1;//�ַ�����ͬ������ǰ������1
		else states[0][i] = 1;//��Ӧ��һ���ַ��Ͳ���ͬ�������Ҳ���ǽ�states[0][0]���Ϊ1
	}
	//��һ�У����һ��ͬ��
	for (int i = 0; i < n; ++i)
	{
		if (a[i] == b[0]) states[i][0] = i;
		else if (i != 0) states[i][0] = states[i - 1][0] + 1;
		else states[i][0] = 1;
	}
	//��дʣ�µ�״̬��������֮ǰ��·��������С
	for (int i = 1; i < n; ++i)
	{
		for (int j = 1; j < m; ++j)
		{
			//��ǰ�Ƚ��ַ��Ƿ���ͬ�����������
			if (a[i] == b[j])
				states[i][j] = min3(states[i - 1][j] + 1, states[i][j - 1] + 1, states[i - 1][j - 1]);
			else
				states[i][j] = min3(states[i - 1][j] + 1, states[i][j - 1] + 1, states[i - 1][j - 1] + 1);
		}
	}
	//ȡ�����
	return states[n - 1][m - 1];
}

//���ʵ�ֲ��������ַ���������������� /problems/longest-common-subsequence/
int longestCommonSubsequence(string text1, string text2) {
	int n = text1.size(), m = text2.size();
	vector<vector<int>> memo(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (text1[i] == text2[j])
				memo[i][j] = i == 0 || j == 0 ? 1 : 1 + memo[i - 1][j - 1];//Ҳ�����ֶ���ʼ����һ�е�һ��
			else
				memo[i][j] = max(i == 0 ? 0 : memo[i - 1][j], j == 0 ? 0 : memo[i][j - 1]);
		}
	}
	return memo[n - 1][m - 1];

	//������ǰ�ճ�һ��һ��
	string a, b;
	int n1 = a.size();
	int n2 = b.size();
	vector<vector<int>>dp(n1 + 1, vector<int>(n2 + 1, 0));
	for (int i = 1; i <= n1; i++) {
		for (int j = 1; j <= n2; j++) {
			if (a[i - 1] == b[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;//��ͬ�ĳ��ȼ�һ
			}
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);//��ͬ�İ����������·�����ĸ����
			}
		}
	}
	return dp[n1][n2];
}

//���ʵ��һ���������е������������ /problems/longest-increasing-subsequence/
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

//Regular Expression Matching��������ʽƥ�䣩/problems/regular-expression-matching/
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

//Minimum Path Sum����С·���ͣ�/problems/minimum-path-sum/
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

//Coin Change ����Ǯ�һ���/problems/coin-change/���������⣩
//����
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


	//��̬�滮
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

//Best Time to Buy and Sell Stock��������Ʊ�����ʱ����/problems/best-time-to-buy-and-sell-stock/
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

//Maximum Product Subarray���˻���������У�/problems/maximum-product-subarray/
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
//�Ż��ռ�
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

//Triangle����������С·���ͣ�/problems/triangle/
int minimumTotal(vector<vector<int>>& triangle) {
	int n = triangle.size();
	for (int i = n - 2; i >= 0; i--) {
		for (int j = 0; j < triangle[i].size(); j++) {
			triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
		}
	}
	return triangle[0][0];
}