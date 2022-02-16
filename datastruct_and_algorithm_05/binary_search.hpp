#ifndef BINARY_SEARCH_HPP
#define BINARY_SEARCH_HPP

#include "public_header.hpp"

BEGIN_NAMESPACE(yyyyshen)

//二分查找
int binary_search(int* arr, size_t n, int value)
{
	int low = 0, high = n - 1;
	while (low <= high)
	{
		int mid = low + ((high - low) >> 1);//位运算防止越界，另外注意+优先级大于>>
		if (arr[mid] == value)
			return mid;
		else if (arr[mid] < value)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}

//变种，第一个大于等于的值（等于、小于等于同理）
int binary_search(int* arr, size_t n, int value)
{
	int low = 0, high = n - 1;
	while (low <= high)
	{
		int mid = low + ((high - low) >> 1);
		if (arr[mid] >= value)
		{
			if (mid == 0 || arr[mid - 1] < value)
				return arr[mid];//是首位或往前找一个是更小的，说明是第一个出现的，返回
			else
				high = mid - 1;//否则前面还有满足条件的，接着找
		}
		else
			low = mid + 1;
	}
	return -1;
}

END_NAMESPACE(yyyyshen)

#endif // !BINARY_SEARCH_HPP
