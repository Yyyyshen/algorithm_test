// explore_learn_arrays101.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <algorithm>

//
//leetcode-explore-learn-arrays101
//

using namespace std;

//introduction
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
class Solution1 {
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
class Solution2 {
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
class Solution3 {
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

int main()
{
	test_dvd_arr();
	std::cout << "Hello World!\n";
}
