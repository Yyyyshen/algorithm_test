// explore_learn_arrays101.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <algorithm>

//
//leetcode-explore-learn-arrays101
//

using namespace std;

//Introduction
// 
//数组
class DVD
{
public:
	DVD() :name_(""), year_(0) {}
	DVD(string name, int year) :name_(name), year_(year) {}
private:
	string name_;
	int year_;
};
void test_dvd_arr() {
	DVD arr_dvd[5];
	arr_dvd[0] = DVD("111", 1921);
	DVD* arr_dvd_p = new DVD[3];
	delete[] arr_dvd_p;
}
// 
//

//Given a binary array nums, return the maximum number of consecutive 1's in the array.
//
//Example:
//Input: nums = [1, 1, 0, 1, 1, 1]
//Output : 3
//Explanation : The first two digits or the last three digits are consecutive 1s.The maximum number of consecutive 1s is 3.
//
class Solution1_1 {
public:
	int findMaxConsecutiveOnes(vector<int>& nums) {
		int max = 0;
		int temp = 0;
		for (auto iter = nums.begin(); iter != nums.end(); ++iter)
		{
			if (*iter /* == 1 */) // ==1 和 true 基本等价，这个例子里不比较也行
			{
				++temp;
			}
			else
			{
				if (temp > max)
					max = temp;
				temp = 0;
			}
		}
		if (temp > max)
			max = temp;
		return max;
	}
};
// 
//

//Given an array nums of integers, return how many of them contain an even number of digits.
//
//Example:
//Input: nums = [12,345,2,6,7896]
//Output: 2
//Explanation :
//	12 contains 2 digits(even number of digits).
//	345 contains 3 digits(odd number of digits).
//	2 contains 1 digit(odd number of digits).
//	6 contains 1 digit(odd number of digits).
//	7896 contains 4 digits(even number of digits).
//	Therefore only 12 and 7896 contain an even number of digits.
// 
class Solution1_2 {
public:
	int findNumbers(vector<int>& nums) {
		int ret = 0;
		for (auto iter = nums.begin(); iter != nums.end(); ++iter) {
			int num = *iter;
			int digit = 0;
			while (num != 0)
			{
				num /= 10;
				digit++;
			}
			if (digit % 2 == 0)
				++ret;
		}
		return ret;
	}
};
// 
//

//Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.
//
//Example:
//Input: nums = [-4,-1,0,3,10]
//Output: [0, 1, 9, 16, 100]
//Explanation : After squaring, the array becomes[16, 1, 0, 9, 100].
//After sorting, it becomes[0, 1, 9, 16, 100].
// 
class Solution1_3 {
public:
	vector<int> sortedSquares(vector<int>& nums) {
		//vector<int> ret;
		//for (auto iter = nums.begin(); iter != nums.end(); ++iter)
		//{
		//	ret.push_back(pow(*iter, 2));
		//}
		//sort(ret.begin(), ret.end());

		//transform(nums.begin(), nums.end(),nums.begin(), [](int num)->int { return num * num; });
		//sort(nums.begin(), nums.end());

		int i;
		vector<int> ans;
		for (i = 0; i < nums.size(); i++)
		{
			if (nums[i] >= 0)
				break;
		}
		int j = i - 1;
		while (i < nums.size() && j >= 0)
		{
			if (abs(nums[i]) >= abs(nums[j]))
			{
				ans.push_back(nums[j] * nums[j]);
				j--;
			}
			else {
				ans.push_back(nums[i] * nums[i]);
				i++;
			}
		}
		while (i < nums.size())
		{
			ans.push_back(nums[i] * nums[i]);
			i++;
		}
		while (j >= 0)
		{
			ans.push_back(nums[j] * nums[j]);
			j--;
		}
		return ans;
	}
};
// 
//

//Inserting Items Into an Array
// 
//插入分为尾部插入，特定位置插入（包括头部插入）
//尾部插入直接在索引处赋值即可；特定位置插入需要先将索引后元素后移，再赋值
//

//Given a fixed length array arr of integers, duplicate each occurrence of zero, shifting the remaining elements to the right.
//Note that elements beyond the length of the original array are not written.
//Do the above modifications to the input array in place, do not return anything from your function.
// 
//Example:
//Input: [1,0,2,3,0,4,5,0]
//Output: null
//Explanation : After calling your function, the input array is modified to : [1, 0, 0, 2, 3, 0, 0, 4]
// 
class Solution2_1 {
public:
	void duplicateZeros(vector<int>& arr) {
		//暴力解
		//for (int i = 0; i < arr.size(); ++i)
		//{
		//	if (arr[i] == 0)
		//	{
		//		for (int j = arr.size() - 1; j > i; --j)
		//			arr[j] = arr[j - 1];
		//		if (i < arr.size() - 1)
		//			arr[i++ + 1] = 0;
		//	}
		//}

		//不嵌套，但内存占的多些
		int size = arr.size();
		vector<int> flag(size);
		for (int i = 0; i < size; ++i)
			flag[i] = arr[i];
		for (int i = 0, j = 0; i < size; ++i, ++j)
		{
			arr[i] = flag[j];
			if (flag[j] == 0 && i != size - 1)
				arr[++i] = 0;
		}
	}
};
// 
//

//You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n, 
// representing the number of elements in nums1 and nums2 respectively.
//Merge nums1and nums2 into a single array sorted in non - decreasing order.
//The final sorted array should not be returned by the function, but instead be stored inside the array nums1.
// To accommodate this, nums1 has a length of m + n, where the first m elements denote the elements that should be merged, 
// and the last n elements are set to 0 and should be ignored.nums2 has a length of n.
// 
//Example:
//Input: nums1 = [1, 2, 3, 0, 0, 0], m = 3, nums2 = [2, 5, 6], n = 3
//Output : [1, 2, 2, 3, 5, 6]
//Explanation : The arrays we are merging are[1, 2, 3] and [2, 5, 6].
//The result of the merge is[1, 2, 2, 3, 5, 6] with the underlined elements coming from nums1.
// 
class Solution2_2 {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		vector<int> nums1_temp(m);
		for (int i = 0; i < m; ++i)
			nums1_temp[i] = nums1[i];
		int index = 0;
		int i = 0, j = 0;
		for (; i < m && j < n;)
			nums1[index++] = nums1_temp[i] > nums2[j] ? nums2[j++] : nums1_temp[i++];
		for (; i < m; ++i)
			nums1[index++] = nums1_temp[i];
		for (; j < n; ++j)
			nums1[index++] = nums2[j];
	}
};
// 
//

//Delete Item From an Array
// 
//删除操作，同样包含首尾和特定位置删除，需要挪动元素操作
//

//Given an integer array nums and an integer val, remove all occurrences of val in nums in-place. The relative order of the elements may be changed.
// 
//Example:
//Input: nums = [3, 2, 2, 3], val = 3
//Output : 2, nums = [2, 2, _, _]
//Explanation : Your function should return k = 2, with the first two elements of nums being 2.
//It does not matter what you leave beyond the returned k(hence they are underscores).
//
class Solution3_1 {
public:
	int removeElement(vector<int>& nums, int val) {
		//nums.erase(remove(nums.begin(), nums.end(), val), nums.end());
		//return nums.size();

		int index = 0;
		for (int i = 0; i < nums.size(); ++i)
			if (nums[i] != val)
				nums[index++] = nums[i];
		return index;
	}
};
// 
//

//Given an integer array nums sorted in non-decreasing order, remove the duplicates in-place such that each unique element appears only once.
// The relative order of the elements should be kept the same.
//
//Example:
//Input: nums = [0,0,1,1,1,2,2,3,3,4]
//Output: 5, nums = [0, 1, 2, 3, 4, _, _, _, _, _]
//Explanation : Your function should return k = 5, with the first five elements of nums being 0, 1, 2, 3, and 4 respectively.
//It does not matter what you leave beyond the returned k(hence they are underscores).
// 
class Solutions3_2 {
public:
	int removeDuplicates(vector<int>& nums) {
		int size = nums.size();
		if (size == 0 || size == 1)
			return size;
		int index = 1;
		for (int i = 1; i < nums.size(); ++i)
			if (nums[i] != nums[i - 1])
				nums[index++] = nums[i];
		return index;
	}
};
//
//

int main()
{
	test_dvd_arr();
	std::cout << "Hello World!\n";
}
