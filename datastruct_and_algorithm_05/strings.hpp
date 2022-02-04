#ifndef STRINGS_HPP
#define STRINGS_HPP

#include "public_header.hpp"

BEGIN_NAMESPACE(yyyyshen)

//26����ĸ��Trie��
#define CHAR_SIZE 26
class trie_node {
public:
	char data;
	bool is_ending;//����Ƿ�˴�Ϊһ�����ʽ�β
	trie_node* children[CHAR_SIZE] = { nullptr };//����ʼ��Ϊ�յĻ���Ĭ�ϰ�0ֵ��ʼ������ָ��
	trie_node(char c) : data(c), is_ending(false) {}
};
class trie
{
public:
	trie()
	{
		root = new trie_node('/');//����һ���������ַ�
	}

	void insert(char* text, size_t len)
	{
		trie_node* temp = root;
		for (int i = 0; i < len; ++i)
		{
			int index = text[i] - 'a';//��a��ASCII��ֵ�������0~25����
			if (temp->children[index] == nullptr)
				//�ַ�ûƥ�䣬���ڴ�λ���½�һ���ڵ�
				temp->children[index] = new trie_node(text[i]);
			temp = temp->children[index];
		}
		temp->is_ending = true;
	}

	bool find(char* text, size_t len)
	{
		trie_node* temp = root;
		for (int i = 0; i < len; ++i)
		{
			int index = text[i] - 'a';
			if (temp->children[index] == nullptr)
				return false;//���ظ�·����û���ҵ���һ���ַ��ˣ���û�ҵ�
			temp = temp->children[index];
		}
		if (temp->is_ending == false)
			return false;//��Ȼƥ�䣬��ֻ��ǰ׺
		else
			return true;//�ҵ�
	}
private:
	trie_node* root;
};

END_NAMESPACE(yyyyshen)

#endif // !STRINGS_HPP
