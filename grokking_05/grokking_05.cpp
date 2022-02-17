// grokking_05.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;

//
//二分搜索变种
// 
//按位异或
// 
//Top-K问题 *** 有两三道hard题没自己敲
//

//=======================================================================

//
//二分搜索变种
//

//例；给定排序数组和一个数字，找出数字是否在数组中
//另外，升降序未知，且应假设数组中有重复项
//时间复杂度O(logN)，空间O(1)
class BinarySearch {
public:
	static int search(const vector<int>& arr, int key) {
		if (arr.empty()) return -1;
		//确定升降序
		int start = 0, end = arr.size() - 1, mid = 0;
		bool is_ascend = arr[start] < arr[end];
		while (start <= end)
		{
			//这里不能使用 (start+end)/2 因为加法可能会int越界
			//另外，装杯用位移运算 >> 1 代替除法的话要注意优先级
			//mid = start + (end - start) / 2;
			mid = start + ((end - start) >> 1);
			if (arr[mid] == key)
				return mid;
			if (is_ascend)
			{
				if (arr[mid] > key)
					end = mid - 1;
				else
					start = mid + 1;
			}
			else
			{
				if (arr[mid] < key)
					end = mid - 1;
				else
					start = mid + 1;
			}
		}
		return -1;
	}
};

//例：给定升序数组和一个数字，找出大于等于该数字的元素的最小元素索引
//二分变种，相当于lower_bound等接口
//本例中限制还不够多，没有考虑数组中存在相同元素，正常这类题应该找最小元素的最小索引
class CeilingOfANumber {
public:
	static int searchCeilingOfANumber(const vector<int>& arr, int key) {
		if (key > arr[arr.size() - 1]) return -1;
		int start = 0, end = arr.size() - 1, mid = 0;
		while (start <= end)
		{
			mid = start + ((end - start) >> 1);
			if (arr[mid] >= key)
			{
				if (mid == 0 || arr[mid - 1]/*如果能判断后面条件，说明mid>0成立，无须多判断依次*/ < key)
					return mid;//如果已经找到0位置或者前一个小于key，则当前mid就是结果
				//如果走到这，说明前面至少还有一个值大于等于key，继续搜索
				end = mid - 1;
			}
			else
			{
				start = mid + 1;
			}
		}
		return -1;
	}
	//变种，找出小于等于该数字的最大元素索引
	static int searchFloorOfANumber(const vector<int>& arr, int key) {
		if (key < arr[0]) return -1;
		int start = 0, end = arr.size() - 1, mid = 0;
		while (start <= end)
		{
			mid = start + ((end - start) >> 1);
			if (arr[mid] <= key)
			{
				if (mid == arr.size() - 1 || arr[mid + 1] > key) return mid;
				start = mid + 1;
			}
			else
				end = mid - 1;
		}
		return -1;
	}
};

//例：给定升序排列的小写字母数组，找到大于给定键的最小字母
//另外，假定数组是环状的，也就是如果大于数组最后一个字母，则返回第一个
class NextLetter {
public:
	static char searchNextLetter(const vector<char>& letters, char key) {
		if (key >= letters[letters.size() - 1]) return letters[0];
		int start = 0, end = letters.size() - 1, mid = 0;
		while (start <= end)
		{
			mid = start + ((end - start) >> 1);
			if (letters[mid] > key)
			{
				if (mid == 0 || letters[mid - 1] <= key) return letters[mid];
				end = mid - 1;
			}
			else
				start = mid + 1;
		}
		return letters[0];
	}
};

//例：给定升序数组，可能含有重复数据，查找一个数字在数组中出现的范围
class FindRange {
public:
	static pair<int, int> findRange(const vector<int>& arr, int key) {
		int start = 0, end = arr.size() - 1, mid = 0;
		while (start <= end)
		{
			mid = start + ((end - start) >> 1);
			if (arr[mid] == key)
			{
				int left = mid, right = mid;
				while (left > 0 && arr[left] == arr[left - 1]) --left;
				while (right < arr.size() - 1 && arr[right] == arr[right + 1]) ++right;
				return { left,right };
			}
			else if (arr[mid] > key)
				end = mid - 1;
			else
				start = mid + 1;
		}
		return { -1,-1 };
	}
};

//例：给定无穷大小升序数组，查找指定值索引，若没找到则返回-1
//提供一个特定类模拟无穷大小数组，若索引大于数组大小，则返回INT_MAX
//本题限制意味着我们无法确定end，需要先找
class ArrayReader {
private:
	vector<int> arr;
public:
	ArrayReader(const vector<int>& arr) { this->arr = arr; }

	virtual int get(int index) {
		if (index >= arr.size()) {
			return numeric_limits<int>::max();
		}
		return arr[index];
	}
};
class SearchInfiniteSortedArray {
public:
	static int search(ArrayReader* reader, int key) {
		//从0开始找，两倍扩张的速度，确认查找范围，再用基本的二分查找
		if (key < reader->get(0)) return -1;
		int start = 0, end = 1, mid = 0;
		while (reader->get(end) < key)
		{
			//只要小于key，把当前位置记录为开始查找位置，结尾位置指数增长
			int new_start = end + 1;
			end += (end - start + 1) * 2;
			start = new_start;
		}
		while (start <= end)
		{
			mid = start + ((end - start) >> 1);
			if (reader->get(mid) == key)
				return mid;
			else if (reader->get(mid) > key)
				end = mid - 1;
			else
				start = mid + 1;
		}
		return -1;
	}
};

//例：给定升序排序数组，找到数组中与给定值差异最小的元素
//二分查找中记录每个数字与目标值的最小差异，若找到相等的，直接返回
class MinimumDifference {
public:
	static int searchMinDiffElement(const vector<int>& arr, int key) {
		int n = arr.size();
		if (key < arr[0]) return arr[0];
		if (key > arr[n - 1]) return arr[n - 1];
		//pair<int, int> memo{ INT_MAX,0 };
		int start = 0, end = n - 1, mid = 0;
		while (start <= end)
		{
			mid = start + ((end - start) >> 1);
			if (arr[mid] == key)
				return arr[mid];
			else if (arr[mid] > key)
				end = mid - 1;
			else
				start = mid + 1;
			//实际上，不需要中途每一步操作都记录
			//if (memo.first > abs(key - arr[mid]))
			//{
			//	memo.first = abs(key - arr[mid]);
			//	memo.second = mid;
			//}
		}
		//如果没找到相同的，走出循环后 start == end + 1
		//所以，最接近的一定在这两个索引中产生
		return (arr[start] - key) > (key - arr[end]) ? arr[end] : arr[start];
	}
};

//例：给定双调数组，找出最大值
//双调数组为先单调递增后单调递减的数组，也就是没有重复元素
//需要注意开头或者结尾就是峰值的情况
class MaxInBitonicArray {
public:
	static int findMax(const vector<int>& arr) {
		int start = 0, end = arr.size() - 1, mid = 0;
		while (start < end)
		{
			int mid = start + ((end - start) >> 1);
			if (arr[mid] > arr[mid + 1])
				end = mid;
			else
				start = mid + 1;
		}
		//结束时，start==end
		return arr[start];
	}
};

//
//总结
// 给定排序数组或链表时
// 查找元素一般使用二分查找
// 这类问题还有一些变种
//

//练习：给定双调数组和一个数字，找数字是否存在，返回索引
//结合找双调数组峰值以及二分查找，先找峰值，再到两边分别找数字
class SearchBitonicArray {
public:
	static int search(const vector<int>& arr, int key) {
		int topIndex = findTop(arr);
		if (key > arr[topIndex]) return -1;
		int keyIndex = binarySearch(arr, key, 0, topIndex);
		if (keyIndex == -1)
			keyIndex = binarySearch(arr, key, topIndex + 1, arr.size() - 1);
		return keyIndex;
	}
	static int findTop(const vector<int>& arr)
	{
		int start = 0, end = arr.size() - 1, mid = 0;
		while (start < end)
		{
			mid = start + ((end - start) >> 1);
			if (arr[mid] < arr[mid + 1])
				start = mid + 1;
			else
				end = mid;
		}
		return start;
	}
	static int binarySearch(const vector<int>& arr, int key, int start, int end)
	{
		int mid = 0;
		while (start <= end)
		{
			mid = start + ((end - start) >> 1);
			if (arr[mid] == key)
				return mid;
			//需要判断递增或递减
			if (arr[start] < arr[end]) {
				if (arr[mid] > key)
					end = mid - 1;
				else
					start = mid + 1;
			}
			else
			{
				if (arr[mid] > key)
					start = mid + 1;
				else
					end = mid - 1;
			}
		}
		return -1;
	}
};

//练习：给定升序数组，并按一定次数旋转，寻找一个值是否存在与数组中
//旋转概念类似于链表旋转，也就是一个数组有两段不同的递增序列
//二分查找消耗都是logN
//所以，类似问题难点在于优化找分界点过程，最简单的是遍历，消耗N
//如果也用二分方法，就可以整体统一时间复杂度为logN
class SearchRotatedArray {
public:
	static int search(const vector<int>& arr, int key) {
		int start = 0, end = arr.size() - 1, mid = 0;
		while (start <= end)
		{
			mid = start + ((end - start) / 2);
			if (arr[mid] == key)
				return mid;
			//一定有一边是单调递增的
			if (arr[start] <= arr[mid]) {  // left side is sorted in ascending order
				//单调递增中，如果key在这个范围，则在这一半范围中找，否则在另一半范围中找
				if (key >= arr[start] && key < arr[mid]) {
					end = mid - 1;
				}
				else {  // key > arr[mid]
					start = mid + 1;
				}
			}
			else {  // right side is sorted in ascending order
				if (key > arr[mid] && key <= arr[end]) {
					start = mid + 1;
				}
				else {
					end = mid - 1;
				}
			}
		}
		return -1;
	}
};
//变种，有重复数字的情况
class SearchRotatedWithDuplicate {
public:
	static int search(const vector<int>& arr, int key) {
		int start = 0, end = arr.size() - 1;
		while (start <= end) {
			int mid = start + (end - start) / 2;
			if (arr[mid] == key) {
				return mid;
			}
			//与上例唯一的不同是三个点都一样时，选择跳过一些点
			// the only difference from the previous solution,
			// if numbers at indexes start, mid, and end are same, we can't choose a side
			// the best we can do, is to skip one number from both ends as key != arr[mid]
			if ((arr[start] == arr[mid]) && (arr[end] == arr[mid])) {
				++start;
				--end;
			}
			else if (arr[start] <= arr[mid]) {  // left side is sorted in ascending order
				if (key >= arr[start] && key < arr[mid]) {
					end = mid - 1;
				}
				else {  // key > arr[mid]
					start = mid + 1;
				}
			}
			else {  // right side is sorted in ascending order
				if (key > arr[mid] && key <= arr[end]) {
					start = mid + 1;
				}
				else {
					end = mid - 1;
				}
			}
		}

		// we are not able to find the element in the given array
		return -1;
	}
};

//练习：给定一个旋转过的升序数组，求旋转次数
//实际上是找最小元素索引，而最小元素索引是数组中唯一一个比前一个元素小的元素
class RotationCountOfRotatedArray {
public:
	static int countRotations(const vector<int>& arr) {
		if (arr.empty()) return 0;
		int start = 0, end = arr.size() - 1, mid = 0;
		while (start < end)
		{
			mid = start + ((end - start) >> 1);
			//看前后两个元素
			if (mid < end && arr[mid] > arr[mid + 1])
				return mid + 1;
			if (mid > start && arr[mid - 1] > arr[mid])
				return mid;
			//全升序，则转折点一定在另一边
			if (arr[start] < arr[mid])
				start = mid + 1;
			else
				end = mid - 1;
		}
		//没有旋转，返回0
		return 0;
	}
};
//变种，有重复值的情况
class RotationCountWithDuplicates {
public:
	static int countRotations(const vector<int>& arr) {
		int start = 0, end = arr.size() - 1;
		while (start < end) {
			int mid = start + (end - start) / 2;
			if (mid < end &&
				arr[mid] > arr[mid + 1]) {  // if element at mid is greater than the next element
				return mid + 1;
			}
			if (mid > start &&
				arr[mid - 1] > arr[mid]) {  // if element at mid is smaller than the previous element
				return mid;
			}
			//区别是跳过重复的数字，但可能结果在跳过前算出
			// this is the only difference from the previous solution
			// if numbers at indices start, mid, and end are same, we can't choose a side
			// the best we can do is to skip one number from both ends if they are not the smallest number
			if (arr[start] == arr[mid] && arr[end] == arr[mid]) {
				if (arr[start] > arr[start + 1]) {  // if element at start+1 is not the smallest
					return start + 1;
				}
				++start;
				if (arr[end - 1] > arr[end]) {  // if the element at end is not the smallest
					return end;
				}
				--end;
				// left side is sorted, so the pivot is on right side
			}
			else if (arr[start] < arr[mid] || (arr[start] == arr[mid] && arr[mid] > arr[end])) {
				start = mid + 1;
			}
			else {  // right side is sorted, so the pivot is on the left side
				end = mid - 1;
			}
		}

		return 0;  // the array has not been rotated
	}
};

//=======================================================================

//
//按位异或
//

//例：给定一个包含从1到n的n-1个整数的数组，找出缺失的那个数
//最直接的做法是算出1~n的总和，减去所有数字，则是缺失的数字
//但可能在算总和时超出INT_MAX
//之前的题目中，这是一个循环排序类型的问题，将数字换到对应的索引上
//没有对应好的数字就是缺失的数字
//试想，用本节标题所说的异或，是否能做这道题
class MissingNumber {
public:
	static int findMissingNumber(vector<int>& arr) {
		//根据异或的特性，相同的数字相互异或会返回0
		//将每个数字与1~n的所有数字异或，若没有变0的情况，则就是缺失的数字
		//但要注意，可以避免双层for循环
		//计算一次从1到n的异或，再计算一次数组中所有数字的异或，两个结果进行异或
		//则一一对应后，没有缺失的数字都异或为0，而0异或任何数结果都是任何数本身，也就得到了缺失的数字
		if (arr.empty()) return -1;
		int n = arr.size() + 1, xor1 = 1, xor2 = arr[0];
		for (int i = 2; i <= n; ++i)
			xor1 = xor1 ^ i;
		for (int i = 1; i < n - 1; ++i)
			xor2 = xor2 ^ arr[i];
		return xor1 ^ xor2;
		//时间复杂度O(N)，与循环排序一样
	}
};

//例：在一个非空整数组，除了一个数字之外，所有数字都出现了两次，找到这个数字
// 正常可能用一个unordered哈希表记录，没记录在内的添加，记录在内的删除，最后剩下的就是结果
//用异或方法
// 出现两次，则异或自身为0，而0异或任何数还是任何数本身，所以，从头到位异或一遍就是结果
class SingleNumber {
public:
	static int findSingleNumber(const vector<int>& arr) {
		int ret = arr[0];//从0开始也是一样的
		for (int i = 1; i < arr.size(); ++i)
			ret = ret xor arr[i];
		return ret;
	}
};

//例：一个非空数组中，除了两个数字之外，其他数字都出现了两次，找到这两个数字
//整个数组异或一遍，会得到两个结果数字的异或值
class TwoSingleNumbers {
public:
	static vector<int> findSingleNumbers(vector<int>& nums) {
		int n1xn2 = 0;
		for (int i = 0; i < nums.size(); ++i)
			n1xn2 = n1xn2 ^ nums[i];
		//可以取最右边为1的位，根据这个位将数组分为两组
		//分别对两组中所有数字进行异或，两个结果就是我们要的
		int rightmostSetBit = 1;
		while ((rightmostSetBit & n1xn2) == 0)//位与运算，是0就左移一位
			rightmostSetBit = rightmostSetBit << 1;
		int num1 = 0, num2 = 0;
		//为什么任取一个为1的位来区分？******************************
		// 因为num1和num2不同，则他们至少有一位不同
		// 则某一位为1，说明两个数字的这个位是不同的
		// 在这一位上，根据是否为1将数组中所有数字分成两组
		// 相同的数字这一位一定相同，被分配到同一组，且异或后会相互抵消
		// 最终，只有num1和num2这两个不同的数字被留到了不同的组中
		//***********************************************************
		for (auto num : nums)
		{
			if ((num & rightmostSetBit) != 0)
				num1 ^= num;
			else
				num2 ^= num;
		}
		return vector<int>{num1, num2};
	}
};

//例：对于以10为底的给定正数N，求其按位取反后的值
//根据异或性质，给定值与结果异或，是一个所有位都为1的值
//推导
// num ^ ret = all_bits_set; 两边同时异或上原值
// num ^ num ^ ret = num ^ all_bits_set; 相同数字异或抵消为0
// ret = num & all_bits_set; 0异或任何值还是任何值本身
// 所以，只要找到所有位都是1的数字，与给定值异或就得到了结果
//计算all_bits_set
// 首先计算给定值所需的位（右移直到为0，计数）
// 之后，以2为底做做幂计算再-1就是此位数填满1的数
// 比如 8 二进制 1000 四位 2的4次方 16 二进制 10000 减1为15 二进制 1111
// 与原值 8 二进制 1000 异或 结果为 0111 也就是结果 7
//
class CalculateComplement {
public:
	static int bitwiseComplement(int num) {
		// count number of total bits in 'num'
		int bitCount = 0;
		int n = num;
		while (n > 0) {
			bitCount++;
			n = n >> 1;
		}

		// for a number which is a complete power of '2' i.e., it can be written as pow(2, n), if we
		// subtract '1' from such a number, we get a number which has 'n' least significant bits set to
		// '1'. For example, '4' which is a complete power of '2', and '3' (which is one less than 4)
		// has a binary representation of '11' i.e., it has '2' least significant bits set to '1'
		int all_bits_set = pow(2, bitCount) - 1;

		// from the solution description: complement = number ^ all_bits_set
		return num ^ all_bits_set;
	}
};

//
//总结
// 异或是逻辑位运算，两位相同则返回0，不同返回1
// 常用特性有
// 数字异或自身返回0
// 数字异或0返回自身
// 支持交换律和结合律
// 
// 在一些特定问题中，这是一种有趣的解决方案
//

//练习：给定表示图像的二进制矩阵，水平翻转图像然后将其反转
//水平翻转就是二进制矩阵根据中轴，左右两边数交换，具体到每一行，就是[0,0,1]翻为{1,0,0]
//反转图像就是每个数字取反，从0变1、从1变0
class Solution {
public:
	static vector<vector<int>> flipAndInvertImage(vector<vector<int>> arr) {
		//翻转是每行从0和size-1开始挨个交换
		//反转是挨个异或
		int s = arr[0].size();
		for (int row = 0; row < arr.size(); row++) {
			for (int col = 0; col < (s + 1) / 2; ++col) {
				int tmp = arr[row][col] ^ 1;
				arr[row][col] = arr[row][s - 1 - col] ^ 1;
				arr[row][s - 1 - col] = tmp;
			}
		}
		return arr;
	}

	static void print(const vector<vector<int>> arr) {
		for (int i = 0; i < arr.size(); i++) {
			for (int j = 0; j < arr[i].size(); j++) {
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
	}
};

//=======================================================================

//
//Top-K问题
//

//例：给定未排序数组，找出K个最大数字
//暴力解，排序后返回K个数字，时间复杂度O(N*logN)
class KLargestNumbers {
public:
	static vector<int> findKLargestNumbers(const vector<int>& nums, int k) {
		//最大堆，所有都存进去，返回k个
		vector<int> result;
		priority_queue<int> q;
		for (auto num : nums)
			q.push(num);
		for (int i = 0; i < k; ++i)
		{
			result.push_back(q.top());
			q.pop();
		}
		return result;
		//最小堆，最多在堆中存k个元素，每次找到大于堆顶的就去掉堆顶并加入新数字
		//最后堆中的k个元素就是结果
		vector<int> result;
		priority_queue<int, vector<int>, std::greater<int>> q;
		for (int i = 0; i < nums.size(); ++i)
		{
			if (i < k)
				q.push(nums[i]);
			else
			{
				if (nums[i] > q.top())
				{
					q.pop();
					q.push(nums[i]);
				}
			}
		}
		while (!q.empty())
		{
			result.push_back(q.top());
			q.pop();
		}
		return result;
		//用std全局的heap相关函数，可以不用额外空间
		// 时间复杂度O(K*logK+(N-K)*logK)，最坏情况下，接近暴力排序，但是可以动态处理
		// 前k个元素放入
		vector<int> minHeap(nums.begin(), nums.begin() + k);
		// 根据现有数据建堆
		make_heap(minHeap.begin(), minHeap.end(), greater());
		// 每次对比堆顶元素
		for (int i = k; i < nums.size(); i++) {
			if (nums[i] > minHeap.front()) {
				//在make_heap的基础上，调用pop_heap后，会将最小的元素放到尾部，再调用pop_back
				pop_heap(minHeap.begin(), minHeap.end(), greater());
				minHeap.pop_back();
				//先将元素放在结尾，之后调用push_heap，会将当前最后一个元素，也就是刚加入的元素调整到正确的位置
				minHeap.push_back(nums[i]);
				push_heap(minHeap.begin(), minHeap.end(), greater());
			}
		}
		// 就地处理的，没有额外空间
		return minHeap;
		//三个方法主要在于空间复杂度从O(N)到O(K)到O(1)的优化
	}
	struct greater {
		bool operator()(const int& a, const int& b) const { return a > b; }
	};
};

//例：给定未排序数组，找出第K个最小数字
class KthSmallestNumber {
public:
	static int findKthSmallestNumber(const vector<int>& nums, int k) {
		//练习用全局的heap相关函数
		vector<int> maxHeap(nums.begin(), nums.begin() + k);
		make_heap(maxHeap.begin(), maxHeap.end());
		for (int i = k; i < nums.size(); ++i)
		{
			if (nums[i] < maxHeap.front())
			{
				pop_heap(maxHeap.begin(), maxHeap.end());
				maxHeap.pop_back();
				maxHeap.push_back(nums[i]);
				push_heap(maxHeap.begin(), maxHeap.end());
			}
		}
		return maxHeap[0];
		//直接用优先级队列
		priority_queue<int> q;
		for (int i = 0; i < k; ++i)
			q.push(nums[i]);
		for (int i = k; i < nums.size(); ++i)
		{
			if (nums[i] < q.top())
			{
				q.pop();
				q.push(nums[i]);
			}
		}
		return q.top();
	}
};

//例：给定坐标轴上点坐标的数组，找到距离远点最近的K个点
//等同于找值最小的K个点，只是需要自定义一个比较函数，计算点到原点的距离
//时间复杂度O(N*logK)，空间复杂度O(K)
class Point {
public:
	int x = 0;
	int y = 0;

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

	int distFromOrigin() const {
		// ignoring sqrt
		return (x * x) + (y * y);
	}
	//若不定义仿函数，可以重载操作符 < ，heap相关函数默认调用
	bool operator<(const Point& rhs) { return this->distFromOrigin() < rhs.distFromOrigin(); }
};
class KClosestPointsToOrigin {
public:
	struct pointComp {
		bool operator()(const Point& a, const Point& b)
		{
			return a.distFromOrigin() < b.distFromOrigin();
		}
	};
	static vector<Point> findClosestPoints(const vector<Point>& points, int k) {
		if (k >= points.size()) return points;
		vector<Point> result(points.begin(), points.begin() + k);
		make_heap(result.begin(), result.end(), pointComp());
		for (int i = k; i < points.size(); ++i)
		{
			if (points[i].distFromOrigin() < result.front().distFromOrigin())
			{
				pop_heap(result.begin(), result.end(), pointComp());
				result.pop_back();
				result.push_back(points[i]);
				push_heap(result.begin(), result.end(), pointComp());
			}
		}
		return result;
	}
};

//例：给定N根不同长度的绳索，以最低成本连接这些绳子
//连接绳子的成本就是两条绳子的长度之和
//也就是每次选最短的两根连接即可，用最小堆
class ConnectRopes {
public:
	static int minimumCostToConnectRopes(const vector<int>& ropeLengths) {
		int result = 0, temp = 0;
		priority_queue<int, vector<int>, greater<int>> q;
		for (auto rope : ropeLengths)
			q.push(rope);
		while (q.size() != 1)
		{
			temp = q.top();
			q.pop();
			temp += q.top();
			q.pop();
			result += temp;
			q.push(temp);
		}
		return result;
	}
};

//例：给定未排序数组，找出最频繁出现的K个数字
//先用一个hashmap统计，然后把统计的pair存入最大堆
class TopKFrequentNumbers {
	struct valueCompareMax {
		bool operator()(const pair<int, int>& x, const pair<int, int>& y) {
			return x.second < y.second;
		}
	};
	struct valueCompareMin {
		char operator()(const pair<int, int>& x, const pair<int, int>& y) {
			return x.second > y.second;
		}
	};
public:
	static vector<int> findTopKFrequentNumbers(const vector<int>& nums, int k) {
		vector<int> topNumbers;
		//无须排序，unordered效率更高
		unordered_map<int, int> map;
		for (auto num : nums)
			++map[num];
		priority_queue<pair<int, int>, vector<pair<int, int>>, valueCompareMax> maxHeap;
		for (auto pair : map)
			maxHeap.push(pair);
		for (int i = 0; i < k; ++i)
		{
			topNumbers.push_back(maxHeap.top().first);
			maxHeap.pop();
		}
		return topNumbers;

		//也可以使用最小堆
		// find the frequency of each number
		unordered_map<int, int> numFrequencyMap;
		for (int n : nums)
			numFrequencyMap[n]++;
		priority_queue<pair<int, int>, vector<pair<int, int>>, valueCompareMin> minHeap;
		// go through all numbers of the numFrequencyMap and push them in the minHeap, which will have
		// top k frequent numbers. If the heap size is more than k, we remove the smallest (top) number
		for (auto entry : numFrequencyMap) {
			minHeap.push(entry);
			if (minHeap.size() > k) {
				minHeap.pop();
			}
		}
		// create a list of top k numbers
		vector<int> topNumbers;
		while (!minHeap.empty()) {
			topNumbers.push_back(minHeap.top().first);
			minHeap.pop();
		}
		return topNumbers;
	}
};

//例：给定字符串，根据字符频率递减排序
class FrequencySort {
public:
	struct pairComp {
		bool operator()(const pair<char, int>& a, const pair<char, int>& b)
		{
			return a.second < b.second;
		}
	};
	static string sortCharacterByFrequency(const string& str) {
		string sortedString = "";
		priority_queue<pair<char, int>, vector<pair<char, int>>, pairComp> maxHeap;
		unordered_map<char, int> memo;
		for (auto c : str)
			++memo[c];
		for (auto p : memo)
			maxHeap.push(p);
		while (!maxHeap.empty())
		{
			auto ch = maxHeap.top();
			while (ch.second-- > 0)
				sortedString += ch.first;
			maxHeap.pop();
		}

		return sortedString;
	}
};

//例：设计一个类，有效找到字节流中第K个大的元素
//也就是动态数据的TopK问题，也是使用堆
//通过最小堆，保存K个数据，堆顶为第K个大元素
class KthLargestNumberInStream {
public:
	struct numCompare {
		bool operator()(const int& x, const int& y) { return x > y; }
	};
public:
	KthLargestNumberInStream(const vector<int>& nums, int k)
		: m_k(k)
	{
		// add the numbers in the min heap
		for (int i = 0; i < nums.size(); i++)
			add(nums[i]);
	}
	virtual int add(int num) {
		// add the new number in the min heap
		minHeap.push(num);
		// if heap has more than 'k' numbers, remove one number
		if ((int)minHeap.size() > m_k)
			minHeap.pop();
		// return the 'Kth largest number
		return minHeap.top();
	}
private:
	priority_queue<int, vector<int>, numCompare> minHeap;
	const int m_k;
};

//例：给定排序数组和两个整数K和X，再数组中找到K个最接近X的数字，按排序顺序返回数字
class KClosestElements {
public:
	struct numCompare {
		bool operator()(const pair<int, int>& x, const pair<int, int>& y) { return x.first > y.first; }
	};
	static int binarySearch(const vector<int>& arr, int key)
	{
		int start = 0, end = arr.size() - 1, mid = 0;
		while (start <= end)
		{
			mid = start + ((end - start) >> 1);
			if (arr[mid] == key)
				return mid;
			if (arr[mid] < key)
				start = mid + 1;
			else
				end = mid - 1;
		}
		return start > 0 ? start - 1 : start;
	}
	static vector<int> findClosestElements(const vector<int>& arr, int K, int X) {
#if 0
		//先二分法，找到接近X的位置，在此位置往两边寻找接近的数字
		//优化这个过程可使用将周边K个数字填入一个以差异值为比较标准的最小堆
		vector<int> result;
		int index = binarySearch(arr, X);
		int low = index - K, high = index + K;
		low = max(0, low);//不能小于0
		high = min((int)arr.size() - 1, high);//不能大于数组大小
		//在这个范围内，一定能找到K个最接近的，因为数组本身是排序的
		priority_queue<pair<int, int>, vector<pair<int, int>>, numCompare> minHeap;
		for (int i = low; i <= high; ++i)
			minHeap.push({ abs(arr[i] - X),i });
		for (int i = 0; i < K; ++i)
		{
			result.push_back(arr[minHeap.top().second]);
			minHeap.pop();
		}
		sort(result.begin(), result.end());
		//时间复杂度O(logN+K*logK)，分别为二分搜索和插入最小堆的消耗
		return result;
#endif 
		//我一开始想的，一个最大堆和一个最小堆，通过K值将数组分成两半，然后根据差异从堆顶取K次
		//这个方法没有利用到已经排序这个条件，且第一遍遍历就把时间复杂度拉到了O(N)
		//略过

		//另一个方法，两点法，同样是二分法，找到接近X的位置后，用两个指针往左右两边找
		deque<int> result;
		int index = binarySearch(arr, X);
		int leftPointer = index;
		int rightPointer = index + 1;
		for (int i = 0; i < K; i++) {
			if (leftPointer >= 0 && rightPointer < (int)arr.size()) {
				int diff1 = abs(X - arr[leftPointer]);
				int diff2 = abs(X - arr[rightPointer]);
				if (diff1 <= diff2) {
					result.push_front(arr[leftPointer--]);  // append in the beginning
				}
				else {
					result.push_back(arr[rightPointer++]);  // append at the end
				}
			}
			else if (leftPointer >= 0) {
				result.push_front(arr[leftPointer--]);
			}
			else if (rightPointer < (int)arr.size()) {
				result.push_back(arr[rightPointer++]);
			}
		}
		vector<int> resultVec;
		std::move(std::begin(result), std::end(result), std::back_inserter(resultVec));
		//时间复杂度O(logN+K)
		return resultVec;
	}
};

//例：给定数组和数字K，从数组中去掉K个数字，求数组中能够剩下最多不同数字的个数
//统计数字出现次数，删除K个之后，要求的是次数为1的数字个数最大的情况
//每次删除，应该是删除大于1的最小的那个数
class MaximumDistinctElements {
public:
	struct pairComp {
		bool operator()(const pair<int, int>& a, const pair<int, int>& b)
		{
			return a.second > b.second;
		}
	};
	static int findMaximumDistinctElements(const vector<int>& nums, int k) {
		int distinctElementsCount = 0;
		unordered_map<int, int> memo;
		for (auto num : nums)
			++memo[num];
		//以出现次数构建最小堆
		priority_queue<pair<int, int>, vector<pair<int, int>>, pairComp> minHeap;
		//次数为1的不重复，直接计数，其他的放入堆
		for (auto p : memo)
		{
			if (p.second == 1)
				++distinctElementsCount;
			else
				minHeap.push(p);
		}
		//将堆中元素，根据k与出现次数向1抵消
		while (!minHeap.empty() && k > 0)
		{
			auto top = minHeap.top();
			minHeap.pop();
			k -= top.second - 1;
			//抵消后还有次数可用，则增加不同数字的计数
			if (k >= 0)
				distinctElementsCount++;
		}
		//如果出了循环，k还大于0，则只能从现有不重复数字里随意删除剩余个了
		if (k > 0)
			distinctElementsCount -= k;
		//这种难度的题自己写的第一次跟答案一毛一样，舒服了
		//时间复杂度O(N*logN+K*logN)，分别是插入hashmap和堆的消耗和从堆中取的消耗
		return distinctElementsCount;
	}
};

//例：给定数组，求数组中第K1和第K2个最小元素之间的所有数字总和
//最大堆，根据K1和K2大小，存更大个数的元素，然后pop到更小的个数，计算中间的值
class SumOfElements {
public:
	static int findSumOfElements(const vector<int>& nums, int k1, int k2) {
		int elementSum = 0;
		priority_queue<int> maxHeap;
		int k = max(k1, k2);
		for (auto num : nums)
		{
			maxHeap.push(num);
			if (maxHeap.size() > k)
				maxHeap.pop();
		}
		maxHeap.pop();
		for (int i = 0; i < abs(k1 - k2) - 1; ++i)
		{
			elementSum += maxHeap.top();
			maxHeap.pop();
		}
		return elementSum;
		//或者全装进最小堆，根据两个k值pop（此题内置k1<k2)
		priority_queue<int, vector<int>, greater<int>> minHeap;

		// insert all numbers to the min heap
		for (int i = 0; i < nums.size(); i++) {
			minHeap.push(nums[i]);
		}

		// remove k1 small numbers from the min heap
		for (int i = 0; i < k1; i++) {
			minHeap.pop();
		}

		int elementSum = 0;
		// sum next k2-k1-1 numbers
		for (int i = 0; i < k2 - k1 - 1; i++) {
			elementSum += minHeap.top();
			minHeap.pop();
		}

		return elementSum;
	}
};

//例：给定字符串，找出没有相同的字符相邻的排列
//统计出现次数，多次出现的字符可以轮询排列相互抵消次数，只出现一次的字符间隔插入可以抵消剩余同等个数的重复字符
//多次出现的次数按最大堆，最顶上两个相互抵消后剩下的就是还会重复的个数，再看是否有之前只出现一次的字符能抵消
class RearrangeString {
public:
	struct pairComp {
		bool operator()(const pair<char, int>& a, const pair<char, int>& b)
		{
			return a.second < b.second;
		}
	};
	static string rearrangeString(const string& str) {
		string ret = "";
		int once_count = 0;
		unordered_map<char, int> memo;
		priority_queue<pair<char, int>, vector<pair<char, int>>, pairComp> maxHeap;
		for (auto c : str)
			++memo[c];
		for (auto p : memo)
		{
			if (p.second == 1)
				++once_count;
			else
				maxHeap.push(p);
		}
		int max_count = maxHeap.top().second;
		maxHeap.pop();
		if (!maxHeap.empty())
			max_count -= maxHeap.top().second;
		//如果多出来的重复字符为1或小于出现一次字符数用于抵消，则可以找到
		//return (max_count == 1) || (max_count <= once_count);
		if (max_count > 1 && max_count > once_count)
			return "";
		//能找到，再想怎么排
		//把重复的部分挨个排列一次
		while (true)
		{
			int once = 0;
			for (auto& p : memo)
			{
				if (p.second == 1)
					++once;
				else
				{
					ret += p.first;
					--p.second;
				}
			}
			if (once == memo.size())
				break;
		}
		//最后把只剩一次的排列一遍
		bool flag = false;
		for (auto& p : memo)
		{
			if (p.first == ret[ret.size() - 1])
			{
				flag = true;//排除第一个就跟之前排好的最后一个一样
				continue;
			}
			ret += p.first;
		}
		if (flag)
			ret += memo.begin()->first;

		return ret;

		//标准答案
		unordered_map<char, int> charFrequencyMap;
		for (char chr : str) {
			charFrequencyMap[chr]++;
		}

		priority_queue<pair<char, int>, vector<pair<char, int>>, valueCompare> maxHeap;

		// add all characters to the max heap
		for (auto entry : charFrequencyMap) {
			maxHeap.push(entry);
		}

		pair<char, int> previousEntry(-1, -1);
		string resultString = "";
		while (!maxHeap.empty()) {
			pair<char, int> currentEntry = maxHeap.top();
			maxHeap.pop();
			// add the previous entry back in the heap if its frequency is greater than zero
			if (previousEntry.second > 0) {
				maxHeap.push(previousEntry);
			}
			// append the current character to the result string and decrement its count
			resultString += currentEntry.first;
			currentEntry.second--;
			previousEntry = currentEntry;
		}

		// if we were successful in appending all the characters to the result string, return it
		return resultString.length() == str.length() ? resultString : "";

	}
	struct valueCompare {
		char operator()(const pair<int, int>& x, const pair<int, int>& y) {
			return y.second > x.second;
		}
	};
};

//
//总结
// 给定集合中找到 最大/最小/频率 的 前/第 K个元素时
// 最佳的结构时使用堆
// 尤其是动态数据中不断取结果（静态数据用快排取一次结果也很快）
// 一般第K个最大元素用最小堆，第K个最小元素用最大堆，即保证所求结果在堆顶
//

//练习：给定字符串，在上例基础上，附加条件K，要求相同字符之间距离至少为K
//前一例是每次将一个字符重新插入堆中，本题中则应该是K次迭代后重新插入
class RearrangeStringKDistanceApart {
public:
	struct valueCompare {
		char operator()(const pair<int, int>& x, const pair<int, int>& y) {
			return y.second > x.second;
		}
	};

	static string reorganizeString(const string& str, int k) {
		if (k <= 1) return str;

		unordered_map<char, int> charFrequencyMap;
		for (char chr : str) {
			charFrequencyMap[chr]++;
		}

		priority_queue<pair<char, int>, vector<pair<char, int>>, valueCompare> maxHeap;

		// add all characters to the max heap
		for (auto entry : charFrequencyMap) {
			maxHeap.push(entry);
		}

		queue<pair<char, int>> queue;
		string resultString;
		while (!maxHeap.empty()) {
			auto currentEntry = maxHeap.top();
			maxHeap.pop();
			// append the current character to the result string and decrement its count
			resultString += currentEntry.first;
			currentEntry.second--;
			queue.push(currentEntry);
			if (queue.size() == k) {
				auto entry = queue.front();
				queue.pop();
				if (entry.second > 0) {
					maxHeap.push(entry);
				}
			}
		}

		// if we were successful in appending all the characters to the result string, return it
		return resultString.length() == str.length() ? resultString : "";
	}
};

//练习：有一个任务列表，每个任务需要一个CPU间隔来执行，任务完成有冷却期
//如果所有任务冷却期为K，则找出完成所有任务需要的最小CPU间隔
//与上例类似，每次重新安排任务，让相同的任务间隔K
//按照类似的方法，我们将首先使用 Max Heap 来执行频率最高的任务。
//执行任务后，我们降低其频率并将其放入等待列表中。
//在每次迭代中，我们将尝试执行多达 k+1 个任务。
//对于下一次迭代，我们会将所有等待的任务放回 Max Heap。
//如果对于任何一次迭代，我们都无法执行 k+1 个任务，那么 CPU 必须在下一次迭代的剩余时间内保持空闲状态。
class TaskScheduler {
public:
	struct valueCompare {
		char operator()(const pair<int, int>& x, const pair<int, int>& y) {
			return y.second > x.second;
		}
	};

	static int scheduleTasks(vector<char>& tasks, int k) {
		int intervalCount = 0;
		unordered_map<char, int> taskFrequencyMap;
		for (char chr : tasks) {
			taskFrequencyMap[chr]++;
		}

		priority_queue<pair<char, int>, vector<pair<char, int>>, valueCompare> maxHeap;

		// add all tasks to the max heap
		for (auto entry : taskFrequencyMap) {
			maxHeap.push(entry);
		}

		while (!maxHeap.empty()) {
			vector<pair<char, int>> waitList;
			int n = k + 1;  // try to execute as many as 'k+1' tasks from the max-heap
			for (; n > 0 && !maxHeap.empty(); n--) {
				intervalCount++;
				auto currentEntry = maxHeap.top();
				maxHeap.pop();
				if (currentEntry.second > 1) {
					currentEntry.second--;
					waitList.push_back(currentEntry);
				}
			}
			// put all the waiting list back on the heap
			for (auto it = waitList.begin(); it != waitList.end(); it++) {
				maxHeap.push(*it);
			}
			if (!maxHeap.empty()) {
				intervalCount += n;  // we'll be having 'n' idle intervals for the next iteration
			}
		}

		return intervalCount;
	}
};

//练习：设计一个模拟栈数据结构的类，实现两个操作
//push，将数字压栈
//pop，返回栈中出现频率最高的数，相同频率的，返回更晚push的
//需要维护三样东西
// 最高，使用最大堆
// 出现频率，使用hashmap
// 更晚，维护一个序列
class Element {
public:
	int number = 0;
	int frequency = 0;
	int sequenceNumber = 0;

	Element(int number, int frequency, int sequenceNumber) {
		this->number = number;
		this->frequency = frequency;
		this->sequenceNumber = sequenceNumber;
	}
};
class FrequencyStack {
public:
	struct frequencyCompare {
		bool operator()(const Element& e1, const Element& e2) {
			//频率不同比频率，相同则比序号
			if (e1.frequency != e2.frequency) {
				return e2.frequency > e1.frequency;
			}
			// if both elements have same frequency, return the one that was pushed later
			return e2.sequenceNumber > e1.sequenceNumber;
		}
	};

	int sequenceNumber = 0;//自增序列
	priority_queue<Element, vector<Element>, frequencyCompare> maxHeap;//最大堆存数据
	unordered_map<int, int> frequencyMap;//记录出现频率

	virtual void push(int num) {
		frequencyMap[num] += 1;
		//记录当前压栈时的频率，对象相当于是管理他们的附带属性，用于堆排序
		//每个元素还是和压栈一样需要多个同时存在其中的
		maxHeap.push({ num, frequencyMap[num], sequenceNumber++ });
	}

	virtual int pop() {
		//每个元素的附带属性都是压栈当时的状态（主要是频率）
		int num = maxHeap.top().number;
		maxHeap.pop();
		//弹出当前栈顶元素后，减少计数
		// decrement the frequency or remove if this is the last number
		if (frequencyMap[num] > 1) {
			frequencyMap[num] -= 1;
		}
		else {
			frequencyMap.erase(num);
		}

		return num;
	}
};

int main()
{
	std::cout << "Hello World!\n";
}
