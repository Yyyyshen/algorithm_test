#pragma once
#include <sstream>

/**
 * �����ֽ�ת����
 * �ֽ�������ʮ�������ִ��໥ת��
 */
static const char char_dictionary[] = "0123456789ABCDEF"; //"0123456789abcdef"
static const uint8_t byte_dictionary[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
0x06, 0x07, 0x08, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };

std::string bytes2hex(const uint8_t* bytes, int length)
{
	std::stringstream ss;
	for (int i = 0; i < length; i++)
	{
		ss << char_dictionary[bytes[i] >> 4];	//����ȡ����λ
		ss << char_dictionary[bytes[i] & 0x0F];  //��λ��ȡ����λ
	}
	return ss.str();
}

uint8_t* hex2bytes(std::string hex)
{
	uint8_t* bytes = new uint8_t(hex.size() / 2);
	for (int i = 0, j = 0; j < hex.size(); i += 1, j += 2)
	{
		bytes[i] = byte_dictionary[hex[j + 0] - '0'] << 4 |
			byte_dictionary[hex[j + 1] - '0']; //-'0'��ȡ��ֵ����������ߵ�4λ
	}
	return bytes;
}

/**
 * ����ָ����������ַ���
 */

std::string random_str(uint8_t length)
{
	std::string ret;

	return ret;
}