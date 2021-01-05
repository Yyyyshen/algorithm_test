// leet_code_01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include "functions.h"

/**
 * 计划有空时在这个项目中刷题LeetCode
 * 根据题大小，可能是5~10题一组（一个子项目）
 */

void test_func();

int main()
{
	DWORD start_time = GetTickCount64();
	test_func();
	DWORD end_time = GetTickCount64();
	std::cout << "Run time pass: " << end_time - start_time << " ms" << std::endl;
}

void test_func()
{

}