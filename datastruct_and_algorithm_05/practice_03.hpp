#pragma once

#include <vector>
#include <queue>
using namespace std;

//LeetCode

//Kth Largest ����k��Ԫ�أ�/problems/kth-largest-element-in-an-array/
int findKthLargest(vector<int>& nums, int k) {
	//��������k��
	sort(nums.begin(), nums.end());
	return nums[nums.size() - k];
	//��С��
	priority_queue<int, vector<int>, greater<int>> q;
	for (auto nums : nums)
	{
		q.push(nums);
		if (q.size() > k) q.pop();//ֻ��k��
	}
	return q.top();
}

//Sqrt(x) ��x��ƽ������/problems/sqrtx/
int mySqrt(int x) {
	if (x <= 0) return 0;
	//����˼��
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