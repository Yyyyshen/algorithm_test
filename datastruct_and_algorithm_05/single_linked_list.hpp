#ifndef SINGLE_LINKED_LIST_HPP
#define SINGLE_LINKED_LIST_HPP

#include "public_header.hpp"
#include <functional>

BEGIN_NAMESPACE(yyyyshen)

//前置声明
class single_linked_list_node;

//单链表
class single_linked_list
{
public://类型别名定义
	using this_type = single_linked_list;
	using node_type = single_linked_list_node;
public://构造析构
	single_linked_list()
	{
		m_head = new node_type();
		m_sentinel = new node_type();
		m_null = new node_type();
		m_head->next = m_sentinel;
	}
	~single_linked_list()
	{
		if (m_sentinel != nullptr)
		{
			delete m_sentinel;
			m_sentinel = nullptr;
		}
		if (m_null != nullptr)
		{
			delete m_null;
			m_null = nullptr;
		}
		if (m_head != nullptr)
		{
			delete m_head;
			m_head = nullptr;
		}
	}
	//删除拷贝构造和拷贝赋值
	single_linked_list(const this_type&) = delete;
	this_type& operator=(const this_type&) = delete;

public://基本操作
	//尾部插入
	node_type* insert_at_tail(void* data, size_t size)
	{
		node_type* new_element = new node_type();
		if (new_element == nullptr)
			return nullptr;//新建节点失败返回空
		new_element->data = data;
		insert(new_element, tail());//复用内置操作
		return new_element;
	}
	//指定位置插入
	node_type* insert_at(node_type* element, void* data, size_t size)
	{
		if (element == nullptr || element == end())
			return nullptr;
		node_type* new_element = new node_type();
		if (new_element == nullptr)
			return nullptr;
		new_element->data = data;
		insert(new_element, element);
		return new_element;
	}
	//删除节点
	void delete_node(node_type* element)
	{
		if (element == nullptr || element == end())
			return;
		node_type* temp = m_sentinel;
		while (temp->next != nullptr)
		{
			if (temp->next == element)//找到，删除
			{
				temp->next = element->next;
				delete element;
				break;
			}
			else
				temp = temp->next;
		}
	}
	//链首
	node_type* begin()
	{
		m_cur = nullptr;//重置
		if (m_sentinel->next == nullptr)
			m_cur = end();
		else
			m_cur = m_sentinel->next;
		return m_cur;
	}
	//下一个
	node_type* next()
	{
		if (m_cur == nullptr || m_cur == end())
			return m_cur;
		m_cur = m_cur->next;
		if (m_cur == nullptr)
			m_cur = end();
		return m_cur;
	}
	//链尾
	node_type* end()
	{
		return m_null;
	}
	//判空
	bool empty()
	{
		return begin() == end();
	}

public://常用操作
	//反转链表
	void reverse()
	{
		if (empty())
			return;
		node_type* cur = m_sentinel->next, * pre = nullptr, * temp = nullptr;
		while (true)
		{
			temp = cur->next;
			cur->next = pre;
			if (temp == nullptr)
				break;
			pre = cur;
			cur = temp;
		}
		m_sentinel->next = cur;
	}
	//检查环
	bool check_circle()
	{
		if (empty())
			return false;
		//两点法，一个快一个慢
		node_type* fast = m_sentinel->next, * slow = m_sentinel->next;
		while ((fast != nullptr) && (fast->next != nullptr))//快的每次走两步，只对快节点判断
		{
			fast = fast->next->next;
			slow = slow->next;
			if (fast == slow)
				return true;//快的能追上慢的，则有环
		}
		//检查完没问题
		return false;
	}
	//合并有序链表
	void merge(this_type& lst, std::function<int(void* t1, void* t2)> func_comp)
	{
		if (func_comp == nullptr)
			return;
		node_type* pl1 = begin(), * pl2 = lst.begin();

	}
	//删除倒数第n个节点
	void delete_last_kth(int k)
	{
		if (k <= 0)
			return;
		int i = 1;
		node_type* fast = m_sentinel->next;
		while ((fast != nullptr) && (i < k))
		{
			//一个节点先走k步
			fast = fast->next;
			++i;
		}
		if (fast == nullptr)
			return;//k太大了
		node_type* slow = m_sentinel->next, * pre = nullptr;
		while (fast->next != nullptr)
		{
			//两个点一起走，相距k，快的走到尾则慢的就是倒数第k个
			fast = fast->next;
			pre = slow;//记录前一个节点，方便删除
			slow = slow->next;
		}
		if (pre != nullptr)
			pre->next = slow->next;
		delete slow;
	}
	//取中间节点
	node_type* center()
	{
		//两点法
		node_type* fast = m_sentinel->next, * slow = m_sentinel->next;
		while ((fast != nullptr) && (fast->next != nullptr))
		{
			fast = fast->next->next;
			slow = slow->next;//快的走两步，慢的走一步，快的到终点则慢的是中点
		}
		return slow;
	}

private://内置操作
	void insert(node_type* new_element, node_type* cur_element, bool back = true)
	{
		if (back) // 表示插入到指定元素后面
		{
			new_element->next = cur_element->next;
			cur_element->next = new_element;
		}
		else//插入到指定元素前面
		{
			//找到前一个元素
			node_type* temp = m_sentinel;
			while (temp != nullptr)
			{
				if (temp->next == cur_element)//找到，插入到前面
				{
					new_element->next = temp->next;
					temp->next = new_element;
					break;
				}
				else
					temp = temp->next;//往后找
			}
		}
	}
	node_type* tail()
	{
		node_type* temp = m_sentinel;
		while (temp->next != nullptr)
			temp = temp->next;
		return temp;
	}

private:
	node_type* m_head;//头节点
	node_type* m_sentinel;//哨兵
	node_type* m_null;//空节点用于end()返回
	node_type* m_cur = nullptr;//当前节点，枚举使用
};

//节点定义
class single_linked_list_node final
{
	friend class single_linked_list;
public:
	using this_type = single_linked_list_node;
protected:
	single_linked_list_node() = default;
	~single_linked_list_node() = default;
public:
	//获取数据指针
	void* get_data_ptr() noexcept
	{
		return data;
	}
protected:
	this_type* next = nullptr;
	void* data = nullptr;
};

//初始化链表
void create_linked_list(single_linked_list& lst)
{

}

//打印链表
void print_linked_list(single_linked_list& lst)
{

}

//基本使用
void test_linked_list_demo()
{

}


END_NAMESPACE(yyyyshen)

#endif // !SINGLE_LINKED_LIST_HPP
