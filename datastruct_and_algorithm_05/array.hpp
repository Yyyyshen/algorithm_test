#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "public_header.hpp"

BEGIN_NAMESPACE(yyyyshen)

//��С�̶���������
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
	void dump()//��ӡ����
	{
		for (int i = 0; i < used; ++i)
			std::cout << "arr[" << i << "]: " << arr[i] << std::endl;
	}

	int insert(int num)
	{
		if (used >= size)//����
			return -1;

		int idx;
		for (idx = 0; idx < used; ++idx)
			if (arr[idx] > num)
				break;//�Ҳ���λ��

		if (idx < used)//�м���룬��Ҫ����
			memmove(&arr[idx + 1], &arr[idx], (used - idx) * sizeof(int));

		//�ڲ���λ�÷�����Ԫ��
		arr[idx] = num;
		++used;

		return 0;
	}

	int delete_idx(int idx)
	{
		if (idx < 0 || idx >= used)
			return -1;

		//�ƶ�Ԫ��
		memmove(&arr[idx], &arr[idx + 1], (used - idx - 1) * sizeof(int));
		--used;
		return 0;
	}

	int search(int val)
	{
		int idx;
		//��������
		for (idx = 0; idx < used; ++idx)
		{
			if (arr[idx] == val)
				return idx;//�ҵ�����
			if (arr[idx] > val)
				return -1;//����������ģ������Ѿ������ˣ�˵�������ڣ�����Ҫ������
		}

		return -1;
	}

	int delete_value(int val)
	{
		//����һ��
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
