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
			//���ݻ�ѹջʧ��
			T* temp = new T[m_cap * 2];
			if (temp == nullptr)
				return;
			//�ɹ�����������
			m_cap *= 2;
			//����
			for (int i = 0; i < m_top; ++i)
				temp[i] = m_arr[i];
			//ɾ��ԭ����
			delete[] m_arr;
			m_arr = temp;
		}
		m_arr[m_top++] = data;
	}
	T pop()
	{
		if (m_top == 0)
			return nullptr;
		//��ջ��ɾ��ջ��
		return m_arr[--m_top];
	}
	T peek()
	{
		if (m_top == 0)
			return nullptr;
		//����ջ��ֵ������ɾ��
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
	T* m_arr;//����ָ��
	int m_cap;//����
	int m_top = 0;//ջ�����
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
		//����ջ����ɾ��
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
		//����ջ������ɾ��
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
	node* m_head;//ͷ�ڵ㣬��Զָ��ջ��
};

//
//���������ʵ��
// ������������ջ
// �����ҳ����ѹջ
// ���˼���ջ
// �����Ǽ�ɾ������ջ����ָλ��֮�������������ǰ��
//

END_NAMESPACE(yyyyshen)

#endif // !STACK_HPP
