#ifndef SORT_HPP
#define SORT_HPP

#include "public_header.hpp"

#if 0 //关于异或交换 https://blog.csdn.net/weixin_45930241/article/details/109142684

#define SWAP(a,b) \
do{\
	(a) ^= (b);\
	(b) ^= (a);\
	(a) ^= (b);\
}while(0)

#endif //不建议使用，ab相同时计算为0，并且汇编下并不节约代码，只是省了一个局部变量，写法更装杯

BEGIN_NAMESPACE(yyyyshen)

//冒泡
void bubble_sort(int* arr, size_t n)
{
	if (arr == nullptr || n <= 1) return;
	for (int i = 0; i < n; ++i)
	{
		bool has_swap = false;//记录是否交换
		for (int j = 0; j < n - i - 1; ++j)
		{
			//每趟把最大的换到最后去
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j], arr[j + 1]);
				has_swap = true;
			}
		}
		if (has_swap == false)
			break;//本趟比较已经没有交换，说明后续都有序了
	}
}

//插入
void insertion_sort(int* arr, size_t n)
{
	if (arr == nullptr || n <= 1) return;
	for (int i = 1; i < n; ++i)
		for (int j = i; j > 0 && arr[j] < arr[j - 1]; --j)
			std::swap(arr[j], arr[j - 1]);//每趟把最小的换到最前面去
}

//选择
void selection_sort(int* arr, size_t n)
{
	if (arr == nullptr || n <= 1) return;
	for (int i = 0; i < n; ++i)
	{
		int index_min = i;
		for (int j = i; j < n; ++j)
			if (arr[j] < arr[index_min])
				index_min = j;//每趟记录最小索引，换到当前趟第一个位置
		std::swap(arr[i], arr[index_min]);
	}
}

//归并
void merge_impl(int* arr, int p, int q, int r);
void merge_sort_impl(int* arr, int p, int r);
void merge_sort(int* arr, size_t n)
{
	merge_sort_impl(arr, 0, n - 1);
}
void merge_sort_impl(int* arr, int p, int r)
{
	if (p >= r)
		return;
	int q = (p + r) >> 1;
	//先分开排最后汇总
	merge_sort_impl(arr, p, q);
	merge_sort_impl(arr, q + 1, r);
	merge_impl(arr, p, q, r);
}
void merge_impl(int* arr, int p, int q, int r)
{
	int* tmp;
	int i, j, k;
	//创建辅助数组
	tmp = new int[r - p + 1];
	if (tmp == nullptr)
		return;
	//合并两段数组
	for (i = p, j = q + 1, k = 0; i <= q && j <= r;)
	{
		if (arr[i] <= arr[j])
			tmp[k++] = arr[i++];
		else
			tmp[k++] = arr[j++];
	}
	//处理可能多出来的部分
	if (i == q + 1)
		for (; j <= r;)
			tmp[k++] = arr[j++];
	else
		for (; i <= i;)
			tmp[k++] = arr[i++];
	//应用到原数组
	memcpy(arr + p, tmp, (r - p + 1) * sizeof(int));
	//回收额外空间
	delete[] tmp;
}

//快排
int partition(int* arr, int p, int r);
void quick_sort_impl(int* arr, int p, int r);
void quick_sort(int* arr, size_t n)
{
	quick_sort_impl(arr, 0, n - 1);
}
void quick_sort_impl(int* arr, int p, int r)
{
	if (p >= r)
		return;
	int q;
	//先整体排再分开排
	q = partition(arr, p, r);
	quick_sort_impl(arr, p, q - 1);
	quick_sort_impl(arr, q + 1, r);
}
int partition(int* arr, int p, int r)
{
	int ret, i;
	ret = i = p;
	for (; i < r; ++i)
	{
		if (arr[i] < arr[r]) //小的放分界点左边，大的放分界点右边
		{
			std::swap(arr[i], arr[ret]);
			++ret;
		}
	}
	//分界点归位
	std::swap(arr[ret], arr[r]);
	return i;
}

END_NAMESPACE(yyyyshen)

#endif // !SORT_HPP
