#ifndef SINGLE_LINKED_LIST_HPP
#define SINGLE_LINKED_LIST_HPP

#include "public_header.hpp"
#include <functional>

BEGIN_NAMESPACE(yyyyshen)

//ǰ������
class single_linked_list_node;

//������
class single_linked_list
{
public://���ͱ�������
	using this_type = single_linked_list;
	using node_type = single_linked_list_node;
public://��������
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
	//ɾ����������Ϳ�����ֵ
	single_linked_list(const this_type&) = delete;
	this_type& operator=(const this_type&) = delete;

public://��������
	//β������
	node_type* insert_at_tail(void* data, size_t size)
	{
		node_type* new_element = new node_type();
		if (new_element == nullptr)
			return nullptr;//�½��ڵ�ʧ�ܷ��ؿ�
		new_element->data = data;
		insert(new_element, tail());//�������ò���
		return new_element;
	}
	//ָ��λ�ò���
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
	//ɾ���ڵ�
	void delete_node(node_type* element)
	{
		if (element == nullptr || element == end())
			return;
		node_type* temp = m_sentinel;
		while (temp->next != nullptr)
		{
			if (temp->next == element)//�ҵ���ɾ��
			{
				temp->next = element->next;
				delete element;
				break;
			}
			else
				temp = temp->next;
		}
	}
	//����
	node_type* begin()
	{
		m_cur = nullptr;//����
		if (m_sentinel->next == nullptr)
			m_cur = end();
		else
			m_cur = m_sentinel->next;
		return m_cur;
	}
	//��һ��
	node_type* next()
	{
		if (m_cur == nullptr || m_cur == end())
			return m_cur;
		m_cur = m_cur->next;
		if (m_cur == nullptr)
			m_cur = end();
		return m_cur;
	}
	//��β
	node_type* end()
	{
		return m_null;
	}
	//�п�
	bool empty()
	{
		return begin() == end();
	}

public://���ò���
	//��ת����
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
	//��黷
	bool check_circle()
	{
		if (empty())
			return false;
		//���㷨��һ����һ����
		node_type* fast = m_sentinel->next, * slow = m_sentinel->next;
		while ((fast != nullptr) && (fast->next != nullptr))//���ÿ����������ֻ�Կ�ڵ��ж�
		{
			fast = fast->next->next;
			slow = slow->next;
			if (fast == slow)
				return true;//�����׷�����ģ����л�
		}
		//�����û����
		return false;
	}
	//�ϲ���������
	void merge(this_type& lst, std::function<int(void* t1, void* t2)> func_comp)
	{
		if (func_comp == nullptr)
			return;
		node_type* pl1 = begin(), * pl2 = lst.begin();

	}
	//ɾ��������n���ڵ�
	void delete_last_kth(int k)
	{
		if (k <= 0)
			return;
		int i = 1;
		node_type* fast = m_sentinel->next;
		while ((fast != nullptr) && (i < k))
		{
			//һ���ڵ�����k��
			fast = fast->next;
			++i;
		}
		if (fast == nullptr)
			return;//k̫����
		node_type* slow = m_sentinel->next, * pre = nullptr;
		while (fast->next != nullptr)
		{
			//������һ���ߣ����k������ߵ�β�����ľ��ǵ�����k��
			fast = fast->next;
			pre = slow;//��¼ǰһ���ڵ㣬����ɾ��
			slow = slow->next;
		}
		if (pre != nullptr)
			pre->next = slow->next;
		delete slow;
	}
	//ȡ�м�ڵ�
	node_type* center()
	{
		//���㷨
		node_type* fast = m_sentinel->next, * slow = m_sentinel->next;
		while ((fast != nullptr) && (fast->next != nullptr))
		{
			fast = fast->next->next;
			slow = slow->next;//�����������������һ������ĵ��յ����������е�
		}
		return slow;
	}

private://���ò���
	void insert(node_type* new_element, node_type* cur_element, bool back = true)
	{
		if (back) // ��ʾ���뵽ָ��Ԫ�غ���
		{
			new_element->next = cur_element->next;
			cur_element->next = new_element;
		}
		else//���뵽ָ��Ԫ��ǰ��
		{
			//�ҵ�ǰһ��Ԫ��
			node_type* temp = m_sentinel;
			while (temp != nullptr)
			{
				if (temp->next == cur_element)//�ҵ������뵽ǰ��
				{
					new_element->next = temp->next;
					temp->next = new_element;
					break;
				}
				else
					temp = temp->next;//������
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
	node_type* m_head;//ͷ�ڵ�
	node_type* m_sentinel;//�ڱ�
	node_type* m_null;//�սڵ�����end()����
	node_type* m_cur = nullptr;//��ǰ�ڵ㣬ö��ʹ��
};

//�ڵ㶨��
class single_linked_list_node final
{
	friend class single_linked_list;
public:
	using this_type = single_linked_list_node;
protected:
	single_linked_list_node() = default;
	~single_linked_list_node() = default;
public:
	//��ȡ����ָ��
	void* get_data_ptr() noexcept
	{
		return data;
	}
protected:
	this_type* next = nullptr;
	void* data = nullptr;
};

//��ʼ������
void create_linked_list(single_linked_list& lst)
{

}

//��ӡ����
void print_linked_list(single_linked_list& lst)
{

}

//����ʹ��
void test_linked_list_demo()
{

}


END_NAMESPACE(yyyyshen)

#endif // !SINGLE_LINKED_LIST_HPP
