// algorithm_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <iomanip>
#include "functions.h"

/**
 * 算法测试
 * 公司每周一小题练习
 */
void test_func1();//字节转换测试
void test_func2();//随机字串生成测试

int main()
{
	//test_func1();
	test_func2();
	system("pause");
	return 0;
}

void test_func2()
{
	std::string ret = random_str(50);
	std::cout << "random str: " << ret << std::endl;
}

void test_func1()
{
	uint8_t bytes[64] = { 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF,
					0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF,
					0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF,
					0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF,
					0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF,
					0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF,
					0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF,
					0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF };
	std::cout << "bytes2hex" << std::endl;
	std::string ret;
	DWORD start_time = GetTickCount64();
	for (int i = 0; i < 10000; i++)
	{
		bytes2hex(bytes, sizeof(bytes));
	}
	DWORD end_time = GetTickCount64();
	ret = bytes2hex(bytes, sizeof(bytes));
	std::cout << "ret: " << ret << std::endl;
	std::cout << "length: " << ret.size() << std::endl;

	std::cout << "Run 1w times pass: " << end_time - start_time << " ms" << std::endl; //debug x86:435ms   release x64: 46ms
	std::cout << "hex2byte" << std::endl;
	uint8_t* b_ret = hex2bytes(ret);
	std::cout << setiosflags(std::ios::uppercase) << std::hex;
	for (int i = 0; i < ret.size() / 2; i++)
	{
		std::cout << unsigned(b_ret[i]) << " ";
	}
	std::cout << std::endl;
}