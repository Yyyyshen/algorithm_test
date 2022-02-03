#ifndef STACK_HPP
#define STACK_HPP

#include "public_header.hpp"

BEGIN_NAMESPACE(yyyyshen)

template<class T>
class array_stack final
{
public:
	array_stack(int size = 10)
		: m_cap(size)
	{
		m_arr = new T[m_cap];
		if (m_arr == nullptr)
			std::cout << "array_stack ctor failed" << std::endl;
	}
	~array_stack()
	{
		delete[] m_arr;
		m_arr = nullptr;
	}
public:
	void push(const T& data)
	{
		if (m_top == m_cap)
		{
			//扩容或压栈失败
			T* temp = new T[m_cap * 2];
			if (temp == nullptr)
				return;
			//成功才设置属性
			m_cap *= 2;
			//拷贝
			for (int i = 0; i < m_top; ++i)
				temp[i] = m_arr[i];
			//删除原数组
			delete[] m_arr;
			m_arr = temp;
		}
		m_arr[m_top++] = data;
	}
	T pop()
	{
		if (m_top == 0)
			return nullptr;
		//出栈并删除栈顶
		return m_arr[--m_top];
	}
	T peek()
	{
		if (m_top == 0)
			return nullptr;
		//返回栈顶值，但不删除
		return m_arr[m_top - 1];
	}
	int size() noexcept
	{
		return m_top;
	}
	int cap() noexcept
	{
		return m_cap;
	}
private:
	T* m_arr;//数组指针
	int m_cap;//容量
	int m_top = 0;//栈顶标记
};

template<class T>
class linked_list_stack final
{
public:
	linked_list_stack()
	{
		m_head = new node;
		m_head->next = nullptr;
	}
	~linked_list_stack()
	{
		while (m_head->next != nullptr)
			pop();
		delete m_head;
		m_head = nullptr;
	}
public:
	void push(const T& data)
	{
		node* new_node = new node(data);
		if (new_node == nullptr)
			return;
		new_node->next = m_head->next;
		m_head->next = new_node;
		++m_size;
	}
	T pop()
	{
		if (m_head == nullptr)
			return nullptr;
		//返回栈顶并删除
		node* temp = m_head->next;
		m_head->next = m_head->next->next;
		T ret = temp->data;
		delete temp;
		--m_size;
		return ret;
	}
	T peek()
	{
		if (m_head == nullptr)
			return nullptr;
		//返回栈顶但不删除
		return m_head->next->data;
	}
	int size() noexcept
	{
		return m_size;
	}
private:
	int m_size = 0;
	struct node
	{
		node(T d) :data(d) {}
		T data;
		node* next;
	};
	node* m_head;//头节点，永远指向栈顶
};

//
//对于浏览器实现
// 可以用数组版的栈
// 点击新页面则压栈
// 后退即出栈
// 由于是假删除，若栈顶所指位置之后有数据则可以前进
//

END_NAMESPACE(yyyyshen)

#endif // !STACK_HPP
