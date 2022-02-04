#pragma once

#include <vector>
#include <queue>
using namespace std;

//LeetCode

//Kth Largest （第k大元素）/problems/kth-largest-element-in-an-array/
int findKthLargest(vector<int>& nums, int k) {
	//排序后遍历k个
	sort(nums.begin(), nums.end());
	return nums[nums.size() - k];
	//最小堆
	priority_queue<int, vector<int>, greater<int>> q;
	for (auto nums : nums)
	{
		q.push(nums);
		if (q.size() > k) q.pop();//只留k个
	}
	return q.top();
}

//Sqrt(x) （x的平方根）/problems/sqrtx/
int mySqrt(int x) {
	if (x <= 0) return 0;
	//二分思想
	long long int start = 0, end = x;

	while (start <= end)
	{
		long long int mid = start + (end - start) / 2;
		long long int sqrt = mid * mid;
		if (sqrt == x)
			return mid;
		if (sqrt < x)
		{
			if (((mid + 1) * (mid + 1)) > x) return mid;
			start = mid + 1;
		}
		else
			end = mid - 1;
	}
	return -1;
}