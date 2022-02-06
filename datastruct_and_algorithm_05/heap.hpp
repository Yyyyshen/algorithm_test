#ifndef HEAP_HPP
#define HEAP_HPP

#include "public_header.hpp"

BEGIN_NAMESPACE(yyyyshen)

//�󶥶�/С����/���ȼ�����
class heap final
{
public:
	heap(int cap = 10)
		: m_cap(cap)
	{
		m_arr = new int[m_cap + 1];//0�ǿճ�����
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
		m_arr[m_count] = val;//�ŵ����λ��
		//���϶ѻ�
		int hole = m_count;
		while (hole / 2 > 0 && m_arr[hole] > m_arr[hole / 2]/*�󶥶�*/)
		{
			std::swap(m_arr[hole], m_arr[hole / 2]);//���Ͻ���
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
		//�����һ��Ԫ�ػ�����
		m_arr[1] = m_arr[m_count--];//�������٣���ɾ��
		//�ѵ�һ��Ԫ�����¶ѻ�
		heapify(m_arr, m_count, 1);
	}

public:
	//���������齨����
	static void build_heap(int* arr, size_t n)
	{
		if (arr == nullptr || n == 0 || n == 1) return;
		//������ǰ�벿���������¶ѻ�����
		for (int i = n / 2; i > 0; --i)
			heapify(arr, n, i);
	}
	//������
	static void heap_sort(int* arr, size_t n)
	{
		build_heap(arr, n);//�Ƚ���
		int k = n;
		while (k > 1)
		{
			//ÿ�ְѶѶ��ŵ���󣬲��ѻ�ʣ�ಿ��
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
			//��count��Χ�ڣ���index���½���
			int pos = index;//��¼����λ��
			if (index * 2 <= count && arr[index * 2] > arr[index])
				pos = index * 2;//�Ƚ����ӽڵ�
			if (index * 2 + 1 <= count && arr[index * 2 + 1] > arr[pos])
				pos = index * 2 + 1;//�Ƚ����ӽڵ�
			if (pos == index) break;//�ȽϺ�û������ѻ����

			std::swap(arr[index], arr[pos]);
			index = pos;//�������±Ƚ�
		}
	}
private:
	int* m_arr = nullptr;
	size_t m_cap = 0;
	size_t m_count = 0;
};

END_NAMESPACE(yyyyshen)

#endif // !HEAP_HPP
