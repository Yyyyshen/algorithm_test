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
				min = j;//内层循环不断比较，记录最小索引
			}
		}
		//交换最小值到第N个位置
		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}
//
//插入排序
// 将未排序的元素插入已经有序牌中的适当位置
// 为了腾出空间，需要将其余元素后移一位
// 
//特点
// 所需时间取决于输入元素的起始顺序；接近有序的数组比随机或逆序的数组快得多
// 
//常用场景
// 数组每个元素距离最终位置不远
// 一个有序大数组接一个小数组
// 数组中只有小部分元素位置不正确
void y_insert_sort(int* arr, size_t len) {
	for (int i = 0; i < len; ++i)
	{
		for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
		{
			int temp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = arr[j];
		}
	}
}
// 
//希尔排序
// 基于插入排序
// 大规模乱序的数组使用插入排序很慢，因为只交换相邻元素
// 希尔排序改进了插入排序，交换不相邻元素对数组局部排序
// 最终用插入排序将局部有序数组排序
// 思想是先使数组任意间隔为h的元素都是有序的，各个子数组都比较短且部分有序，很适合快速排序
void y_shell_sort(int* arr, size_t len) {
	int h = 1;
	while (h < len / 3) h = 3 * h + 1;
	while (h >= 1)
	{
		for (int i = h; i < len; i++) {
			for (int j = i; j >= h && arr[j] < arr[j - h];j-=h)
			{
				int temp = arr[j];
				arr[j] = arr[j - h];
				arr[j - h] = temp;
			}
		}
		h = h / 3;
	}
}
// 
// 
//


int main()
{
	std::cout << "Hello World!\n";
}
