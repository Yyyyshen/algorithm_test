#ifndef SORT_HPP
#define SORT_HPP

#include "public_header.hpp"

#if 0 //������򽻻� https://blog.csdn.net/weixin_45930241/article/details/109142684

#define SWAP(a,b) \
do{\
	(a) ^= (b);\
	(b) ^= (a);\
	(a) ^= (b);\
}while(0)

#endif //������ʹ�ã�ab��ͬʱ����Ϊ0�����һ���²�����Լ���룬ֻ��ʡ��һ���ֲ�������д����װ��

BEGIN_NAMESPACE(yyyyshen)

//ð��
void bubble_sort(int* arr, size_t n)
{
	if (arr == nullptr || n <= 1) return;
	for (int i = 0; i < n; ++i)
	{
		bool has_swap = false;//��¼�Ƿ񽻻�
		for (int j = 0; j < n - i - 1; ++j)
		{
			//ÿ�˰����Ļ������ȥ
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j], arr[j + 1]);
				has_swap = true;
			}
		}
		if (has_swap == false)
			break;//���˱Ƚ��Ѿ�û�н�����˵��������������
	}
}

//����
void insertion_sort(int* arr, size_t n)
{
	if (arr == nullptr || n <= 1) return;
	for (int i = 1; i < n; ++i)
		for (int j = i; j > 0 && arr[j] < arr[j - 1]; --j)
			std::swap(arr[j], arr[j - 1]);//ÿ�˰���С�Ļ�����ǰ��ȥ
}

//ѡ��
void selection_sort(int* arr, size_t n)
{
	if (arr == nullptr || n <= 1) return;
	for (int i = 0; i < n; ++i)
	{
		int index_min = i;
		for (int j = i; j < n; ++j)
			if (arr[j] < arr[index_min])
				index_min = j;//ÿ�˼�¼��С������������ǰ�˵�һ��λ��
		std::swap(arr[i], arr[index_min]);
	}
}

//�鲢
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
	//�ȷֿ���������
	merge_sort_impl(arr, p, q);
	merge_sort_impl(arr, q + 1, r);
	merge_impl(arr, p, q, r);
}
void merge_impl(int* arr, int p, int q, int r)
{
	int* tmp;
	int i, j, k;
	//������������
	tmp = new int[r - p + 1];
	if (tmp == nullptr)
		return;
	//�ϲ���������
	for (i = p, j = q + 1, k = 0; i <= q && j <= r;)
	{
		if (arr[i] <= arr[j])
			tmp[k++] = arr[i++];
		else
			tmp[k++] = arr[j++];
	}
	//������ܶ�����Ĳ���
	if (i == q + 1)
		for (; j <= r;)
			tmp[k++] = arr[j++];
	else
		for (; i <= i;)
			tmp[k++] = arr[i++];
	//Ӧ�õ�ԭ����
	memcpy(arr + p, tmp, (r - p + 1) * sizeof(int));
	//���ն���ռ�
	delete[] tmp;
}

//����
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
	//���������ٷֿ���
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
		if (arr[i] < arr[r]) //С�ķŷֽ����ߣ���ķŷֽ���ұ�
		{
			std::swap(arr[i], arr[ret]);
			++ret;
		}
	}
	//�ֽ���λ
	std::swap(arr[ret], arr[r]);
	return i;
}

END_NAMESPACE(yyyyshen)

#endif // !SORT_HPP
