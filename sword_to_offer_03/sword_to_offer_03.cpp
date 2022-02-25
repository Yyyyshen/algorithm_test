// sword_to_offer_03.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//
//高质量代码
//

//
//代码规范性
// 书写、布局、命名
// 一般在白纸或者白板写字，字体差问题不大，尽量写清楚即可
// 日常开发IDE处理好了布局，手写时要格外注意，尤其是缩进层次多时
// 变量或函数命名要清楚表达含义，最好还能带上类型前缀，用完整单词等
// 也就是说，代码除了自己明白，也要让其他人一看就能懂
// 

//
//代码完整性
// 考虑问题是否周全
// 除了基本功能，还需要对边界值、特殊值、非法输入等做出合理处理
// 
//三个方面
// 写代码之前考虑好所有可能输入
// 设计测试用例，功能测试、边界测试、负面测试
// 基本功能 例如字符串转整数，考虑正负数、普通字符串“123”等
// 突破常规 例如打印从1到最大n位数，超过整数范围怎么办，需要使用字符串存储
// 各种边界值 例如循环或递归的结束条件
// 考虑各种可能的错误输入 例如空指针、类型错误、数值错误等
// 
//错误处理方式
// 特殊返回值告知调用是否出错，如-1等
// 提供全局变量，各种错误时将变量赋不同值
// 抛异常，但有些语言不支持
// 
//面试题：求数值n次方
// 实现pow函数，不能用库函数，不需要考虑大数
// 分析
// 指数可能有多种情况
class Power final
{
public:
	static double run(double base, int n)
	{
		//指数可以小于0，相当于绝对值次方的倒数，但需要考虑0
		if (double_equal(base, 0.0) && n < 0)
			return 0.0;
		//正常求指数绝对值的次方
		unsigned int absn = n < 0 ? (unsigned int)(-n) : (unsigned int)n;
		//double ret = 1.0;
		//for (int i = 0; i <= absn; ++i)
		//	ret *= base;
		double ret = run_smart(base, absn);
		//正负分别返回不同的值
		return n < 0 ? (1.0 / ret) : ret;
	}
	//最优解法
	// 在上面方法中，n为多少，就要进行多少次乘法
	// 但实际上，base^n/2 * base^n/2 = base^n
	// 也就是使用logn次乘法（斐波那契也是）
	// 所以，上面解法中求指数绝对值次方的循环部分可以用如下函数代替
	static double run_smart(double base, unsigned int n)
	{
		if (n == 0)
			return 1.0;
		if (n == 1)
			return base;
		//是n/2次方的乘积和，除法用位移代替
		double ret = run_smart(base, n >> 1);
		ret *= ret;
		//如果是奇数还要多乘一次，求模用位与运算代替
		if ((n & 0x1) == 1)
			ret *= base;
		return ret;
	}
private:
	static bool double_equal(double a, double b)
	{
		//***浮点数对比由于精度的原因，不能直接用相等***
		constexpr double ESP = 0.0000000001;
		//相减后精度够高则认定为相等
		return (a - b) < ESP;
		//还可以互相减一次，如果都为0，则相等
	}
};
// 
//面试题：打印从1到最大的n位数
// 分析
// 陷阱在于，n位是多少位，整数型能否装得下
class PrintOneToMaxN final
{
public:
	static void run(int n)
	{
		//如果直接求N位最大值再遍历打印，就把问题想太简单了
		//如果大于20位（64位整数范围）需要使用字符串表示数字

		//基本参数检查
		if (n <= 0) return;
		//字符串实现
		char* number = new char[n + 1];
		//先全赋值为0
		memset(number, '0', n);
		number[n] = '\0';//\0是字符结尾，是真正的0，跟字符0不同
		//封装一下数字增长和打印函数
		while (increment(number, strlen(number)))
			print(number, strlen(number));

		delete[] number;
	}
private:
	//字符增长
	static bool increment(char* number, size_t len)
	{
		//逐个处理位数
		int carry = 0;
		for (int i = len - 1; i >= 0; --i)
		{
			//取出位当前数字
			int num = number[i] - '0' + carry;
			//在最后一位加一
			if (i == len - 1)
				++num;
			//判断是否需要进位
			if (num < 10)
			{
				number[i] = num + '0';
				//没进位就不用继续了
				break;
			}
			//需要进位的话，判断是否已经溢出了，也就是第一个数字
			if (i == 0)
				return false;//作为外层结束循环的条件
			//没有溢出，则取个位数，并赋值进位标志
			num -= 10;
			carry = 1;
			number[i] = num + '0';
		}
		//可以继续增长
		return true;
	}
	//打印字符
	static void print(const char* number, size_t len)
	{
		//不只是单纯打印，使用这个方法时，位数不够的情况下，前面都补了0
		int begin = 0;
		//跳过为0的部分
		while (begin < len && number[begin] == '0')
			++begin;
		//打印后面
		while (begin < len)
			cout << number[begin++];
		cout << '\t';
	}
public:
	//问题转换，从意义上将，其实是n个0~9数字的全排列，递归枚举也可完成
	static void run_recursive(int n)
	{
		if (n <= 0) return;
		char* number = new char[n + 1];
		memset(number, '0', n);
		number[n] = '\0';
		//每个索引，枚举所有数字情况
		for (int i = 0; i < 10; ++i)
		{
			number[0] = i + '0';
			recur_impl(number, n, 0);
		}
		delete[] number;
	}
private:
	static void recur_impl(char* number, int length, int index)
	{
		//枚举到最后一位，打印一次
		if (index = length - 1)
		{
			print(number, strlen(number));
			return;
		}
		//往下一个数字枚举0~9
		for (int i = 0; i < 10; ++i)
		{
			number[index + 1] = i + '0';
			recur_impl(number, length, index + 1);
		}
	}
};
// 
//

int main()
{
	std::cout << "Hello World!\n";
}
