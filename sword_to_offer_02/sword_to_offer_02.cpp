// sword_to_offer_02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//
//数据结构
//

//
//数组
// 数组名是一个指针，指向第一个元素
int GetSize(int data[]) { return sizeof(data); }
void
test_raw_arr()
{
	int data[] = { 1,2,3,4,5 };
	int* p_data = data;
	std::cout << "data[] size : " << sizeof(data) << std::endl	//20
		<< "p_data size : " << sizeof(p_data) << std::endl		//4
		<< "GetSize(data[]) : " << GetSize(data) << std::endl;	//4 当数组作为函数参数传递时，自动退化成同类型指针
}
// 
//例
// 二维数组中查找
bool
find_num_in_2d_arr(int* matrix, int rows, int columns, int number)
{
	//正常遍历
	if (matrix == nullptr) return false;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
			if (matrix[i * j + j] == number)
				return true;
	}

	return false;

	//加上条件：每行、每列都是递增排列。
	//普通遍历可行，但可以优化

	//选取数组右上角数字，如果等于要查找的数，过程结束；大于查找数字，其所在列可以忽略；小于则可以忽略所在行

	if (matrix != nullptr && rows > 0 && columns > 0)			//参数检查
	{
		int row = 0, column = columns - 1;
		while (row < rows && column >= 0)
		{
			if (matrix[row * column + column] == number)
				return true;
			else if (matrix[row * column + column] > number)
				--column;
			else
				++row;
		}
	}

	return false;
}
// 
//

int main()
{
	std::cout << "Hello World!\n";
}
