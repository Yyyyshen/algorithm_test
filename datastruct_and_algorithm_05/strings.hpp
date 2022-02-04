#ifndef STRINGS_HPP
#define STRINGS_HPP

#include "public_header.hpp"

BEGIN_NAMESPACE(yyyyshen)

//26个字母的Trie树
#define CHAR_SIZE 26
class trie_node {
public:
	char data;
	bool is_ending;//标记是否此处为一个单词结尾
	trie_node* children[CHAR_SIZE] = { nullptr };//不初始化为空的话会默认按0值初始化所有指针
	trie_node(char c) : data(c), is_ending(false) {}
};
class trie
{
public:
	trie()
	{
		root = new trie_node('/');//根放一个无意义字符
	}

	void insert(char* text, size_t len)
	{
		trie_node* temp = root;
		for (int i = 0; i < len; ++i)
		{
			int index = text[i] - 'a';//减a的ASCII码值则是算出0~25索引
			if (temp->children[index] == nullptr)
				//字符没匹配，则在此位置新建一个节点
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
				return false;//在重复路径上没有找到下一个字符了，则没找到
			temp = temp->children[index];
		}
		if (temp->is_ending == false)
			return false;//虽然匹配，但只是前缀
		else
			return true;//找到
	}
private:
	trie_node* root;
};

END_NAMESPACE(yyyyshen)

#endif // !STRINGS_HPP
