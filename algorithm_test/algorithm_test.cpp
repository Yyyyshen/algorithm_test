// algorithm_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <sstream>
#include <Windows.h>
#include <iomanip>
/**
 * 一字节8bit分割高低4位转16进制
 */
std::string bytes2hex(const uint8_t* bytes, int length);
uint8_t* hex2bytes(std::string hex);
static const char char_dictionary[] = "0123456789ABCDEF"; //"0123456789abcdef"
static const uint8_t byte_dictionary[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
0x06, 0x07, 0x08, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };
int main()
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
	system("pause");
	return 0;
}

std::string bytes2hex(const uint8_t* bytes, int length)
{
	std::stringstream ss;
	for (int i = 0; i < length; i++)
	{
		ss << char_dictionary[bytes[i] >> 4];	//高四位
		ss << char_dictionary[bytes[i] & 0x0F];  //低四位
	}
	return ss.str();
}

uint8_t* hex2bytes(std::string hex)
{
	uint8_t* bytes = new uint8_t(hex.size() / 2);
	for (int i = 0, j = 0; j < hex.size(); i += 1, j += 2)
	{
		bytes[i] = byte_dictionary[hex[j + 0] - '0'] << 4 |
			byte_dictionary[hex[j + 1] - '0']; //-'0'获取数值后或运算填充高低4位
	}
	return bytes;
}