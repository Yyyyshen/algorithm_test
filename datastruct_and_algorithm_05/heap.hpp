#ifndef HEAP_HPP
#define HEAP_HPP

#include "public_header.hpp"

BEGIN_NAMESPACE(yyyyshen)

//大顶堆/小顶堆/优先级队列
class heap final
{
public:
	heap(int cap = 10)
		: m_cap(cap)
	{
		m_arr = new int[m_cap + 1];//0是空出来的
		if (m_arr == nullptr)
			throw;
	}
	heap() = delete;
	~heap()
	{
		if (m_arr != nullptr)
			delete[] m_arr;
		m_arr = nullptr;
	}
public:
	void insert(int val)
	{
		if (m_count >= m_cap) return;
		++m_count;
		m_arr[m_count] = val;//放到最后位置
		//向上堆化
		int hole = m_count;
		while (hole / 2 > 0 && m_arr[hole] > m_arr[hole / 2]/*大顶堆*/)
		{
			std::swap(m_arr[hole], m_arr[hole / 2]);//向上交换
			hole /= 2;
		}
	}
	int top()
	{
		if (m_count == 0) return -1;
		return m_arr[1];
	}
	void pop_top()
	{
		if (m_count == 0) return;
		//把最后一个元素换上来
		m_arr[1] = m_arr[m_count--];//计数减少，假删除
		//把第一个元素向下堆化
		heapify(m_arr, m_count, 1);
	}

public:
	//将现有数组建立堆
	static void build_heap(int* arr, size_t n)
	{
		if (arr == nullptr || n == 0 || n == 1) return;
		//把数组前半部分依次向下堆化即可
		for (int i = n / 2; i > 0; --i)
			heapify(arr, n, i);
	}
	//堆排序
	static void heap_sort(int* arr, size_t n)
	{
		build_heap(arr, n);//先建堆
		int k = n;
		while (k > 1)
		{
			//每轮把堆顶放到最后，并堆化剩余部分
			std::swap(arr[1], arr[k]);
			--k;
			heapify(arr, k, 1);
		}
	}
private:
	static void heapify(int* arr, int count, int index)
	{
		while (true)
		{
			//在count范围内，从index向下交换
			int pos = index;//记录交换位置
			if (index * 2 <= count && arr[index * 2] > arr[index])
				pos = index * 2;//比较左子节点
			if (index * 2 + 1 <= count && arr[index * 2 + 1] > arr[pos])
				pos = index * 2 + 1;//比较右子节点
			if (pos == index) break;//比较后没换，则堆化完成

			std::swap(arr[index], arr[pos]);
			index = pos;//继续往下比较
		}
	}
private:
	int* m_arr = nullptr;
	size_t m_cap = 0;
	size_t m_count = 0;
};

END_NAMESPACE(yyyyshen)

#endif // !HEAP_HPP
