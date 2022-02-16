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

int main()
{
	std::cout << "Hello World!\n";
}
