// algorithm_4th_02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//
//排序
//

//初级排序
// 
//选择排序
// 找到数组中最小元素，与第一个元素交换位置
// 再从剩下的数组元素中重复这个动作
// 不断选择剩余元素中的最小者，直到整组排序
//
//特点
// 运行时间与输入无关；即使是已经有序的数组运行一次也跟随机数组所用时间相同
// 数据移动最少；每次交换改变两个数组元素的值，交换N次
// 
void y_select_sort(int* arr, size_t len) {
	for (int i = 0; i < len; ++i) //外层循环控制选择起点
	{
		int min = i;//记录最小索引值
		for (int j = i + 1; j < len; ++j)
		{
			if (arr[j] < arr[min])
			{
				min = j;//内层循环不断比较最小索引
			}
		}
		//交换最小值到第N个位置
		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}
//

int main()
{
	std::cout << "Hello World!\n";
}
