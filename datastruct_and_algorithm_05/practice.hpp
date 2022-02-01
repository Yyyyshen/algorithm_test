#pragma once

//leetcode��ϰ

#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
using namespace std;

//����֮�� /problems/3sum/
class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		vector<vector<int>> ret;
		//������
		for (int i = 0; i < nums.size(); ++i)
		{
			for (int j = i + 1; j < nums.size(); ++j)
			{
				for (int k = j + 1; k < nums.size(); ++k)
				{
					if (nums[i] + nums[j] + nums[k] == 0)
					{
						ret.push_back({ nums[i],nums[j],nums[k] });
						//ʱ�临�Ӷ�O(n^3)��ûȥ��
					}
				}
			}
		}
		return ret;

		//���õĽⷨ
		// �Ƚ����������ظ���Ԫ�ض�����һ��
		// ʹ������ָ�������������飬�������ظ�Ԫ�أ��Ϳ�����Ȼȥ��
		// �����������򣬿��Ը����ܺʹ��ڻ�С��0����������
		// 
		// ����ѭ������������
		// ����Ԫ��
		// ���ѭ����һ������index1��������
		// �ڲ�ѭ�����������ֱ��ͷβ��ʼ��index2 = index1+1��index3 = n-1
		// ��ѭ����������index2>=index3
		// ȥ��
		// ���ѭ���У����index1��ǰһ�����֣�index1-1����ͬ��������
		// �ڲ�ѭ���У����index3��ǰ��ʱ�������ǰһ����index3+1����ͬ��������һ��
		//
		vector<vector<int>> ret;
		int n = nums.size();
		sort(nums.begin(), nums.end());
		for (int index1 = 0; index1 + 2 < n/* ���滹�������������ճ��� */; ++index1)
		{
			if (index1 > 0 && nums[index1] == nums[index1 - 1])
				continue;//ȥ����߲���
			int index2 = index1 + 1, index3 = n - 1;
			while (index2 < index3)
			{
				int sum = nums[index1] + nums[index2] + nums[index3];
				if (sum == 0)
				{
					ret.push_back({ nums[index1],nums[index2],nums[index3] });
					//ȥ���ұ߲���
					--index3;
					while ((index2 < index3) && (nums[index3] == nums[index3 + 1])) --index3;
				}
				else if (sum < 0)//��̫С��˵����ߵ�̫С������
					++index2;
				else //��̫��˵���ұ�̫��ǰ��
					--index3;
			}
		}

		return ret;
		//�����Բ�ֳ����� ����֮��
		//ʱ�临�Ӷ�Ҳ��O(n^2)
	}
};

//������ /problems/majority-element/
int majorityElement(vector<int>& nums) {
	//����1������һ��map��¼�������ռ临�Ӷ�O(n)
	unordered_map<int, int> temp;//����������unordered_mapЧ�ʸ���
	for (int i = 0; i < nums.size(); ++i)
		temp[nums[i]]++;

	for (auto element : temp)
		if (element.second > floor(double(nums.size()) / 2))
			return element.first;
	return -1;

	//����2���趨�ϣ�ֻ���������֣����Ա�����ֱ�ӻ����������˭�������࣬�ռ临�Ӷ�O(1)
	int cur_num = -1, count = 0;
	for (int i = 0; i < nums.size(); ++i)
	{
		if (count == 0)
			cur_num = nums[i];
		if (nums[i] == cur_num)
			++count;
		else
			--count;
	}
	return cur_num;

	//�����������ǵ���for������ʱ�临�Ӷ�O(n)
}

//��ȱʧ�ĵ�һ������ /problems/first-missing-positive/
class bitmap
{
public:
	bitmap(int bits)
		: nbits(bits)
	{
		int size = nbits / 8 + 1;
		bmp = new char[size];//����λ������λͼ
		for (int i = 0; i < size; ++i)
			bmp[i] = '\0';
	}
	~bitmap()
	{
		delete[] bmp;
	}
public:
	void set(int k)
	{
		if (k > nbits) return;//����λͼ��Χ
		int byteindex = k / 8;//�ȼ����������ĸ��ֽ�
		int bitindex = k % 8;//�����ֽ���λ��ƫ��
		//��λ�������б��
		bmp[byteindex] |= (1 << bitindex);
	}
	bool get(int k)
	{
		if (k > nbits) return false;
		int byteindex = k / 8;
		int bitindex = k % 8;
		return (bmp[byteindex] & (1 << bitindex)) != 0;
	}
private:
	int nbits;//λ��
	char* bmp;//λͼ
};
int firstMissingPositive(vector<int>& nums) {
	//λͼ˼·������̫���ˣ�leetcodeֱ�ӳ�ʱ
	//���ܴ��С���ˣ�������û��ô�󣬲���Ҫר����λͼ
	int max = 0;
	for (auto i : nums)
		if (i > max)
			max = i;//����һ�������
	bitmap bmp(max);
	for (auto i : nums)
		if (i > 0)
			bmp.set(i);
	int i;
	for (i = 1; i <= max; ++i)
		if (!bmp.get(i))
			return i;
	return i;

	//��һ��˼·�������������
	int temp = 1;
	sort(nums.begin(), nums.end());
	for (int i = 0; i < nums.size(); i++) {
		if (temp == nums[i]) {
			temp++;
		}
		else if (nums[i] > temp) break;
	}
	return temp;

	//��������λͼ��˼·���Ƚ�ϲ��
	unsigned int size = nums.size();
	vector<int> Appear(size + 2, 0);//������bool�����������˽��vector�沼��ֵ��λ�������ĳ�intӦ�ø���
	int i;
	for (i = size - 1; i >= 0; i--)
	{
		if (nums[i] > 0 && nums[i] <= size)//�Ƚ����������ֻ��С��Χ�ڼ�飨size���ÿ�������ס���ܳ��ֵ���ֵ��Χ��
			Appear[nums[i]] = 1;
	}
	i = 1;
	while (Appear[i] == 1)
		i++;
	return i;
}


//�������� /problems/linked-list-cycle/


//�ϲ�k���������� /problems/merge-k-sorted-lists/
