#pragma once
#include <vector>
#include <unordered_map>
/**
 * 两数之和：
 * 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 的那 两个 整数，并返回它们的数组下标。
 * 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。
 * 你可以按任意顺序返回答案。
 */
extern
std::vector<int>
twoSum(std::vector<int>& nums, int target) {
	std::vector<int> ret;

	//暴力解法，枚举；时间复杂度N^2，空间复杂度1

	//for (auto it_fir = nums.begin(); it_fir != nums.end(); it_fir++)
	//{
	//	for (auto it_sec = it_fir + 1; it_sec != nums.end(); it_sec++)
	//	{
	//		if (*it_fir + *it_sec == target)
	//		{
	//			ret.push_back(it_fir - nums.begin());
	//			ret.push_back(it_sec - nums.begin());
	//			break;
	//		}
	//	}
	//}

	//以上耗时136ms，用迭代器有点夸张了
	//之前用java写，耗时还没有这么高，不过c++内存占的少
	//直接当成数组来解更快

	//for (int i = 0; i < nums.size(); i++) {
	//	for (int j = i + 1; j < nums.size(); j++) {
	//		if (nums[i] + nums[j] == target) {
	//			ret.push_back(i);
	//			ret.push_back(j);
	//			break;
	//		}
	//	}
	//}

	//哈希表法，遍历一次，遍历中对每个元素寻找target-x，找到则返回两个索引，否则存入哈希表
	//时间复杂度N，空间复杂度N
	std::unordered_map<int, int> hashtable;
	for (int i = 0;i<nums.size();i++)
	{
		auto it = hashtable.find(target - nums[i]);
		if (it != hashtable.end()) {
			ret.push_back(i);
			ret.push_back(it->second);
			break;
		}
		hashtable[nums[i]] = i;
	}

	return ret;
}