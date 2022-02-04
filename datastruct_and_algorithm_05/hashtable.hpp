#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "public_header.hpp"

BEGIN_NAMESPACE(yyyyshen)

//���������ɢ�б�
class hashtable_based_on_linked_list final
{
public:
	using this_type = hashtable_based_on_linked_list;
public:
	hashtable_based_on_linked_list(size_t n = 10)
		: cap(n)
	{
		if (cap <= 0) throw;
		tables = new node * [cap];
		if (tables == nullptr) throw;
		for (int i = 0; i < cap; ++i)
			tables[i] = nullptr;
	}
	~hashtable_based_on_linked_list()
	{
		if (tables != nullptr)
		{
			node* tmp;
			for (int i = 0; i < cap; ++i)
			{
				while (tables[i] != nullptr)
				{
					tmp = tables[i];
					tables[i] = tables[i]->next;
					delete tmp;
				}
			}
			tables = nullptr;
		}
	}
	hashtable_based_on_linked_list() = delete;
	hashtable_based_on_linked_list(const this_type&) = delete;
	this_type& operator=(const this_type&) = delete;

public:
	void insert(void* key, void* data)
	{
		//�������
		if (key == nullptr || data == nullptr)
			return;
		//һ�����������ֲ�������Ч�ʽ���
		int hash_val = 0;
		node* cur = nullptr, * prev = nullptr, * new_node = nullptr;
		//�����ϣ���ҵ�Ͱ
		hash_val = hash_value(key);
		cur = tables[hash_val];
		//����keyֵ���ҵ�����λ��
		while (cur != nullptr && (key_cmp(key, cur->key) > 0))
		{
			prev = cur;
			cur = cur->next;
		}
		if (cur != nullptr && (key_cmp(key, cur->key) == 0))
			return;//��ͬkeyֵ
		//�����½ڵ�
		new_node = new node(key,data);
		if (new_node == nullptr)
			return;
		//����
		if (prev == nullptr)
		{
			//��Ϊ��Ͱ���µ���ͷ
			new_node->next = tables[hash_val];
			tables[hash_val] = new_node;
		}
		else
		{
			//��Ӧλ�ò���
			new_node->next = prev->next;
			prev->next = new_node;
		}
		//���Ӽ���
		++size;
	}
	bool delete_with_key(void* key)
	{
		if (key == nullptr) return;
		int hash_val = 0;
		node* cur = nullptr, * prev = nullptr;
		
		hash_val = hash_value(key);
		cur = tables[hash_val];
		while (cur != nullptr && (key_cmp(key, cur->key) >= 0))
		{
			if (key_cmp(key, cur->key) == 0)
			{
				if (prev == nullptr)
				{
					tables[hash_val] = cur->next;
					delete cur;
				}
				else
				{
					prev->next = cur->next;
					delete cur;
				}
				return true;
			}

			prev = cur;
			cur = cur->next;
		}
		return false;//û�У�δɾ���κζ���
	}

	void* search(void* key)
	{
		if (key == nullptr) return nullptr;
		int hash_val = 0;
		node* cur = nullptr;
		hash_val = hash_value(key);
		cur = tables[hash_val];
		while (cur != nullptr && (key_cmp(key, cur->key) >= 0))
		{
			if (key_cmp(key, cur->key) == 0)
				return cur->data;
			cur = cur->next;
		}
		return nullptr;//û�ҵ�
	}

private:
	unsigned int simple_hash(const char* str)
	{
		//register��������������ܵĽ���������CPU�ڲ��Ĵ����У�������ͨ���ڴ�Ѱַ���ʣ������Ч�ʡ�
		register unsigned int hash = 0;
		register unsigned int seed = 123;
		while (*str)
			hash = hash * seed + *str++;//������һ��
		return hash & (0x7FFFFFFF);
	}
	//����hash����
	int hash_value(const void* key)
	{
		return simple_hash((char*)key) % cap;
	}
	//key�ȽϺ���
	int key_cmp(const void* key1, const void* key2)
	{
		return strcmp((char*)key1, (char*)key2);
	}
private:
	struct node
	{
		void* key;//��
		void* data;//ֵ���洢������
		node* next;//��һ���ڵ�
		node(void* k, void* v) :key(k), data(v), next(nullptr) {}
	};
	node** tables = nullptr;//��ϣͰ������ÿ��Ԫ�ش洢��ϣ��ͬ�������ͷ
	size_t cap = 0;//Ͱ����
	size_t size = 0;//Ԫ�ظ���
};

END_NAMESPACE(yyyyshen)

#endif // !HASHTABLE_HPP
