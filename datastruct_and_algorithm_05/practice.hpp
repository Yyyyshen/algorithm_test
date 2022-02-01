#pragma once

//leetcode练习

#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
using namespace std;

//三数之和 /problems/3sum/
class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		vector<vector<int>> ret;
		//暴力解
		for (int i = 0; i < nums.size(); ++i)
		{
			for (int j = i + 1; j < nums.size(); ++j)
			{
				for (int k = j + 1; k < nums.size(); ++k)
				{
					if (nums[i] + nums[j] + nums[k] == 0)
					{
						ret.push_back({ nums[i],nums[j],nums[k] });
						//时间复杂度O(n^3)且没去重
					}
				}
			}
		}
		return ret;

		//更好的解法
		// 先将数组排序，重复的元素都连在一起
		// 使用两个指针从两侧遍历数组，并跳过重复元素，就可以自然去重
		// 由于数组有序，可以根据总和大于或小于0来增减索引
		// 
		// 两层循环，三个索引
		// 找三元组
		// 外层循环用一个索引index1遍历数组
		// 内层循环两个索引分别从头尾开始，index2 = index1+1，index3 = n-1
		// 内循环结束条件index2>=index3
		// 去重
		// 外层循环中，如果index1与前一个数字（index1-1）相同，则跳过
		// 内层循环中，如果index3往前移时，如果与前一个（index3+1）相同，则再移一次
		//
		vector<vector<int>> ret;
		int n = nums.size();
		sort(nums.begin(), nums.end());
		for (int index1 = 0; index1 + 2 < n/* 后面还有两个索引，空出来 */; ++index1)
		{
			if (index1 > 0 && nums[index1] == nums[index1 - 1])
				continue;//去重左边部分
			int index2 = index1 + 1, index3 = n - 1;
			while (index2 < index3)
			{
				int sum = nums[index1] + nums[index2] + nums[index3];
				if (sum == 0)
				{
					ret.push_back({ nums[index1],nums[index2],nums[index3] });
					//去重右边部分
					--index3;
					while ((index2 < index3) && (nums[index3] == nums[index3 + 1])) --index3;
				}
				else if (sum < 0)//和太小，说明左边的太小，后移
					++index2;
				else //和太大，说明右边太大，前移
					--index3;
			}
		}

		return ret;
		//还可以拆分成两次 两数之和
		//时间复杂度也是O(n^2)
	}
};

//求众数 /problems/majority-element/
int majorityElement(vector<int>& nums) {
	//方法1：利用一个map记录次数，空间复杂度O(n)
	unordered_map<int, int> temp;//无须排序，用unordered_map效率更高
	for (int i = 0; i < nums.size(); ++i)
		temp[nums[i]]++;

	for (auto element : temp)
		if (element.second > floor(double(nums.size()) / 2))
			return element.first;
	return -1;

	//方法2：设定上，只有两个数字，可以遍历中直接互相抵消，看谁计数更多，空间复杂度O(1)
	int cur_num = -1, count = 0;
	for (int i = 0; i < nums.size(); ++i)
	{
		if (count == 0)
			cur_num = nums[i];
		if (nums[i] == cur_num)
			++count;
		else
			--count;
	}
	return cur_num;

	//两个方法都是单层for遍历，时间复杂度O(n)
}

//求缺失的第一个正数 /problems/first-missing-positive/
class bitmap
{
public:
	bitmap(int bits)
		: nbits(bits)
	{
		int size = nbits / 8 + 1;
		bmp = new char[size];//根据位数构建位图
		for (int i = 0; i < size; ++i)
			bmp[i] = '\0';
	}
	~bitmap()
	{
		delete[] bmp;
	}
public:
	void set(int k)
	{
		if (k > nbits) return;//超过位图范围
		int byteindex = k / 8;//先计算在数组哪个字节
		int bitindex = k % 8;//计算字节中位的偏移
		//用位操作进行标记
		bmp[byteindex] |= (1 << bitindex);
	}
	bool get(int k)
	{
		if (k > nbits) return false;
		int byteindex = k / 8;
		int bitindex = k % 8;
		return (bmp[byteindex] & (1 << bitindex)) != 0;
	}
private:
	int nbits;//位数
	char* bmp;//位图
};
int firstMissingPositive(vector<int>& nums) {
	//位图思路，但是太慢了，leetcode直接超时
	//可能大材小用了，数量级没那么大，不需要专门用位图
	int max = 0;
	for (auto i : nums)
		if (i > max)
			max = i;//遍历一遍找最大
	bitmap bmp(max);
	for (auto i : nums)
		if (i > 0)
			bmp.set(i);
	int i;
	for (i = 1; i <= max; ++i)
		if (!bmp.get(i))
			return i;
	return i;

	//另一个思路，先排序后搜索
	int temp = 1;
	sort(nums.begin(), nums.end());
	for (int i = 0; i < nums.size(); i++) {
		if (temp == nums[i]) {
			temp++;
		}
		else if (nums[i] > temp) break;
	}
	return temp;

	//别人类似位图的思路，比较喜欢
	unsigned int size = nums.size();
	vector<int> Appear(size + 2, 0);//他用了bool，但是曾经了解过vector存布尔值是位操作，改成int应该更快
	int i;
	for (i = size - 1; i >= 0; i--)
	{
		if (nums[i] > 0 && nums[i] <= size)//比较巧妙的在于只在小范围内检查（size正好可以限制住可能出现的数值范围）
			Appear[nums[i]] = 1;
	}
	i = 1;
	while (Appear[i] == 1)
		i++;
	return i;
}


//环形链表 /problems/linked-list-cycle/


//合并k个排序链表 /problems/merge-k-sorted-lists/
