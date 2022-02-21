// sword_to_offer_02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

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
//字符串
// C/C++每个字符串以'\0'结尾，用于寻找尾部，有额外一字节占用
// 常量字符串放到单独内存区域，指针赋值给相同常量字符串时，指向相同内存
void test_str()
{
	char str1[] = "helloworld";
	char str2[] = "helloworld";
	//此过程中，数组各自分配空间，并且把字符串复制进去，所以不同
	cout << "str1 and str2 is: " << (str1 == str2 ? "same" : "diff") << endl;//diff
	char* str3 = (char*)"helloworld";
	char* str4 = (char*)"helloworld";
	//此过程中，指针无须分配空间，而是把他们指向常量字符串"helloworld"所在内存地址，所以相同
	cout << "str3 and str4 is: " << (str3 == str4 ? "same" : "diff") << endl;//same
}
// 
//面试题：替换空格
// 在Url中，特殊字符（空格、#、<等）需要根据ASCII码替换为%形式的字符
// 例如空格，ASCII码32，转16进制0x20，也就是转换为%20
// 编写一个函数替换一串字符中的空格
// 
// 分析
// 首先明确，原地替换还是可以使用额外空间
// 原地替换的话，空格为一个字符，替换后是三个字符
// 需要字符串后有空余空间，且每次替换后其后字符都要后移
void replace_spaces()
{
	char input[25] = "hello world";//预留后续处理空间
#if 0//暴力解，遍历，遇到空格把后续所有字符后移，之后替换，时间复杂度O(n^2)
	for (int i = 0; i < sizeof(input); ++i)
	{
		if (input[i] == ' ')
		{
			for (int j = strlen(input) + 1; j >= i + 2; --j)
				input[j] = input[j - 2];
			input[i] = '%';
			input[i + 1] = '2';
			input[i + 2] = '0';
		}
	}
	cout << input << endl;
#endif
	//更优解
	// 两点法，计算总共需要后移的位数，一个点指向最终结尾，一个指向当前结尾，从后向前依次拷贝或替换
	// 重点
	// 是否想到字符串替换变长问题，内存越界
	// 是否能想到用从后向前遍历，避免每次处理时都把之后所有字符重复挪动一遍
	// 两个有序数组合并问题，如果要求原地合并，也可以同理，从后向前减少移动次数
	if (input == nullptr /* || length <= 0 */) return;//参数检查
	int count = 0;
	for (int i = 0; i < strlen(input); ++i)
		if (input[i] == ' ')
			count += 2;
	int p1 = strlen(input);
	int p2 = p1 + count;
	if (p1 == p2) return;//没有空格
	//还可以检查一下，p2是否大于给定长度
	/* if (p2 > length) return; */
	while (p1 != p2)
	{
		char cur = input[p1--];
		if (cur == ' ')
		{
			input[p2--] = '0';
			input[p2--] = '2';
			input[p2--] = '%';
		}
		else
			input[p2--] = cur;
	}
	cout << input << endl;
}
//

//
//链表
//

int main()
{
	std::cout << "Hello World!\n";
}
