#ifndef BINARY_SEARCH_HPP
#define BINARY_SEARCH_HPP

#include "public_header.hpp"

BEGIN_NAMESPACE(yyyyshen)

//���ֲ���
int binary_search(int* arr, size_t n, int value)
{
	int low = 0, high = n - 1;
	while (low <= high)
	{
		int mid = low + ((high - low) >> 1);//λ�����ֹԽ�磬����ע��+���ȼ�����>>
		if (arr[mid] == value)
			return mid;
		else if (arr[mid] < value)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}

//���֣���һ�����ڵ��ڵ�ֵ�����ڡ�С�ڵ���ͬ��
int binary_search(int* arr, size_t n, int value)
{
	int low = 0, high = n - 1;
	while (low <= high)
	{
		int mid = low + ((high - low) >> 1);
		if (arr[mid] >= value)
		{
			if (mid == 0 || arr[mid - 1] < value)
				return arr[mid];//����λ����ǰ��һ���Ǹ�С�ģ�˵���ǵ�һ�����ֵģ�����
			else
				high = mid - 1;//����ǰ�滹�����������ģ�������
		}
		else
			low = mid + 1;
	}
	return -1;
}

END_NAMESPACE(yyyyshen)

#endif // !BINARY_SEARCH_HPP
