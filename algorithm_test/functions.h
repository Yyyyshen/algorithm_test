#pragma once
#include <sstream>

/**
 * 常用字节转换；
 * 字节数组与十六进制字串相互转换
 */
static const char char_dictionary[] = "0123456789ABCDEF"; //"0123456789abcdef"
static const uint8_t byte_dictionary[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
0x06, 0x07, 0x08, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };

std::string bytes2hex(const uint8_t* bytes, int length)
{
	std::stringstream ss;
	for (int i = 0; i < length; i++)
	{
		ss << char_dictionary[bytes[i] >> 4];	//右移取高四位
		ss << char_dictionary[bytes[i] & 0x0F];  //按位与取低四位
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

/**
 * 生成指定长度随机字符串
 */

std::string random_str(uint8_t length)
{
	std::string ret;

	return ret;
}