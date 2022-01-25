#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "public_header.hpp"

BEGIN_NAMESPACE(yyyyshen)

//大小固定有序数组
class sorted_array
{
public:
	sorted_array(int s)
		: size(s)
	{
		arr = new int[size];
	}
	~sorted_array()
	{
		delete[] arr;
	}
public:
	void dump()//打印数组
	{
		for (int i = 0; i < used; ++i)
			std::cout << "arr[" << i << "]: " << arr[i] << std::endl;
	}

	int insert(int num)
	{
		if (used >= size)//满了
			return -1;

		int idx;
		for (idx = 0; idx < used; ++idx)
			if (arr[idx] > num)
				break;//找插入位置

		if (idx < used)//中间插入，需要后移
			memmove(&arr[idx + 1], &arr[idx], (used - idx) * sizeof(int));

		//在插入位置放入新元素
		arr[idx] = num;
		++used;

		return 0;
	}

	int delete_idx(int idx)
	{
		if (idx < 0 || idx >= used)
			return -1;

		//移动元素
		memmove(&arr[idx], &arr[idx + 1], (used - idx - 1) * sizeof(int));
		--used;
		return 0;
	}

	int search(int val)
	{
		int idx;
		//遍历查找
		for (idx = 0; idx < used; ++idx)
		{
			if (arr[idx] == val)
				return idx;//找到返回
			if (arr[idx] > val)
				return -1;//由于是有序的，发现已经更大了，说明不存在，不需要再找了
		}

		return -1;
	}

	int delete_value(int val)
	{
		//复用一手
		int idx = search(val);
		delete_idx(idx);
		return 0;
	}

	int modify(int idx, int val)
	{
		if (idx < 0 || idx >= used)
			return -1;
		arr[idx] = val;
		return 0;
	}

private:
	int size;
	int used = 0;
	int* arr = nullptr;
};

END_NAMESPACE(yyyyshen)

#endif // !ARRAY_HPP
