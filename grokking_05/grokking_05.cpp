// grokking_05.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
using namespace std;

//
//二分搜索变种
// 
//按位异或
// 
//Top-K问题
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
//按位异或
//

int main()
{
	std::cout << "Hello World!\n";
}
