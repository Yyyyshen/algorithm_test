#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "public_header.hpp"

BEGIN_NAMESPACE(yyyyshen)

//基于链表的散列表
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
		//参数检查
		if (key == nullptr || data == nullptr)
			return;
		//一次申请好所需局部变量，效率较优
		int hash_val = 0;
		node* cur = nullptr, * prev = nullptr, * new_node = nullptr;
		//计算哈希，找到桶
		hash_val = hash_value(key);
		cur = tables[hash_val];
		//根据key值，找到插入位置
		while (cur != nullptr && (key_cmp(key, cur->key) > 0))
		{
			prev = cur;
			cur = cur->next;
		}
		if (cur != nullptr && (key_cmp(key, cur->key) == 0))
			return;//相同key值
		//建立新节点
		new_node = new node(key,data);
		if (new_node == nullptr)
			return;
		//插入
		if (prev == nullptr)
		{
			//成为本桶内新的链头
			new_node->next = tables[hash_val];
			tables[hash_val] = new_node;
		}
		else
		{
			//对应位置插入
			new_node->next = prev->next;
			prev->next = new_node;
		}
		//增加计数
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
		return false;//没有，未删除任何东西
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
		return nullptr;//没找到
	}

private:
	unsigned int simple_hash(const char* str)
	{
		//register请求编译器尽可能的将变量存在CPU内部寄存器中，而不是通过内存寻址访问，以提高效率。
		register unsigned int hash = 0;
		register unsigned int seed = 123;
		while (*str)
			hash = hash * seed + *str++;//随便计算一下
		return hash & (0x7FFFFFFF);
	}
	//简易hash函数
	int hash_value(const void* key)
	{
		return simple_hash((char*)key) % cap;
	}
	//key比较函数
	int key_cmp(const void* key1, const void* key2)
	{
		return strcmp((char*)key1, (char*)key2);
	}
private:
	struct node
	{
		void* key;//键
		void* data;//值，存储的数据
		node* next;//下一个节点
		node(void* k, void* v) :key(k), data(v), next(nullptr) {}
	};
	node** tables = nullptr;//哈希桶，数组每个元素存储哈希相同对象的链头
	size_t cap = 0;//桶容量
	size_t size = 0;//元素个数
};

END_NAMESPACE(yyyyshen)

#endif // !HASHTABLE_HPP
