// explore_learn_array_and_string.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <algorithm>
#include <vector>

//
//leetcode-explore-learn-array_and_string
//

using namespace std;

//Introduction to Array
//
// 一维数组
// 
void
test_arr()
{
	// 1. Initialize
	int a0[5];
	int a1[5] = { 1, 2, 3 };  // other element will be set as the default value
	// 2. Get Length
	int size = sizeof(a1) / sizeof(*a1);
	cout << "The size of a1 is: " << size << endl;
	// 3. Access Element
	cout << "The first element is: " << a1[0] << endl;
	// 4. Iterate all Elements
	cout << "[Version 1] The contents of a1 are:";
	for (int i = 0; i < size; ++i) {
		cout << " " << a1[i];
	}
	cout << endl;
	cout << "[Version 2] The contents of a1 are:";
	for (int& item : a1) {
		cout << " " << item;
	}
	cout << endl;
	// 5. Modify Element
	a1[0] = 4;
	// 6. Sort
	sort(a1, a1 + size);
}
// 
//

//
//数组有固定长度，一般要使用可以动态扩容的可变长度数组
// C++里是vector，JAVA里是ArrayList
void
test_vec()
{
	// 1. initialize
	vector<int> v0;
	vector<int> v1(5, 0);
	// 2. make a copy
	vector<int> v2(v1.begin(), v1.end());
	vector<int> v3(v2);
	// 2. cast an array to a vector
	int a[5] = { 0, 1, 2, 3, 4 };
	vector<int> v4(a, *(&a + 1));//&a取当前数组指针的指针，+1指到数组结尾，再*取出结尾地址值，等同与 a + 5 也就是 a + sizeof(a) / sizeof(*a)
	// 3. get length
	cout << "The size of v4 is: " << v4.size() << endl;
	// 4. access element
	cout << "The first element in v4 is: " << v4[0] << endl;
	// 5. iterate the vector
	cout << "[Version 1] The contents of v4 are:";
	for (int i = 0; i < v4.size(); ++i) {
		cout << " " << v4[i];
	}
	cout << endl;
	cout << "[Version 2] The contents of v4 are:";
	for (int& item : v4) {
		cout << " " << item;
	}
	cout << endl;
	cout << "[Version 3] The contents of v4 are:";
	for (auto item = v4.begin(); item != v4.end(); ++item) {
		cout << " " << *item;
	}
	cout << endl;
	// 6. modify element
	v4[0] = 5;
	// 7. sort
	sort(v4.begin(), v4.end());
	// 8. add new element at the end of the vector
	v4.push_back(-1);
	// 9. delete the last element
	v4.pop_back();
}
// 
//

//Given an array of integers nums, calculate the pivot index of this array.
// The pivot index is the index where the sum of all the numbers 
// strictly to the left of the index is equal to the sum of all the numbers strictly to the index's right.
//
class Solution1_1 {
public:
	int pivotIndex(vector<int>& nums) {
		/*	嵌套暴力解
				int size = nums.size();
				int ret = -1;
				for (int i = 0; i < size; ++i) {
					int left = 0, right = 0;
					for (int i_l = 0; i_l < i; ++i_l)
						left += nums[i_l];
					for (int i_r = i + 1; i_r < size; ++i_r)
						right += nums[i_r];
					if (left == right)
					{
						ret = i;
						break;
					}
				}
				return ret;
		*/
		//先算和，再做减法即可
		int sum = 0, left = 0;
		for (auto& item : nums) sum += item;
		for (int i = 0; i < nums.size(); ++i) {
			if (sum - left - nums[i] == left)
				return i;
			left += nums[i];
		}
		return -1;
	}
};
// 
//

//Largest Number At Least Twice of Others
// Determine whether the largest element in the array is at least twice as much as every other number in the array. 
// If it is, return the index of the largest element, or return -1 otherwise.
// 
class Solution1_2 {
public:
	int dominantIndex(vector<int>& nums) {
		//只需要比第二大的大两倍就可以了
		int max = 0, size = nums.size(), max_i = 0;
		bool is_find_b = false;
		for (int i = 0; i < size; i++)
		{
			int num = nums[i];
			if (num > max)
			{
				is_find_b = false;
				if (num >= max * 2) is_find_b = true;
				max = num;
				max_i = i;
			}
			else {
				if (num * 2 > max) is_find_b = false;
			}
		}
		if (is_find_b) return max_i;
		return -1;

		//或者两次遍历，第一次找最大，第二次验证二倍关系
	}
};
// 
//

//Plus One
// You are given a large integer represented as an integer array digits, 
// where each digits[i] is the ith digit of the integer. 
// The digits are ordered from most significant to least significant in left-to-right order. 
// The large integer does not contain any leading 0's.
// Increment the large integer by oneand return the resulting array of digits.
class Solution1_3 {
public:
	vector<int> plusOne(vector<int>& digits) {
		reverse(digits.begin(), digits.end());
		if (++digits[0] < 10)
		{
			reverse(digits.begin(), digits.end());
			return digits;
		}
		digits[0] %= 10;
		int num = 0, carry = 1, size = digits.size();
		for (int i = 1; i < size; ++i)
		{
			int sum = digits[i] + carry;
			num = sum % 10;
			carry = sum / 10;
			digits[i] = num;
		}
		if (carry > 0) digits.push_back(carry);
		reverse(digits.begin(), digits.end());
		return digits;

		//想多了，可以直接倒过来遍历的
		int n = digits.size();
		for (int i = n - 1; i >= 0; i--) {
			if (digits[i] == 9) {
				digits[i] = 0;
			}
			else {
				digits[i]++;
				return digits;

			}
		}

		digits.push_back(0);
		digits[0] = 1;
		return digits;
	}
};
// 
//

int main()
{
	std::cout << "Hello World!\n";
	test_arr();
	test_vec();
}
