#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "public_header.hpp"

BEGIN_NAMESPACE(yyyyshen)

template<typename T>
class circle_queue_based_on_array final
{
public:
	using this_type = circle_queue_based_on_array;
public:
	circle_queue_based_on_array() = delete;
	circle_queue_based_on_array(size_t cap)
		:m_cap(cap)
	{
		m_arr = new T[m_cap];
	}
	~circle_queue_based_on_array()
	{
		if (m_arr != nullptr)
			delete[] m_arr;
		m_arr = nullptr;
	}
	circle_queue_based_on_array(const this_type&) = delete;
	this_type& opertor = (const this_type&) = delete;

public:
	void enqueue(T data)
	{
		if ((m_tail + 1) % m_cap == head)
			throw "queue is full";
		m_arr[m_tail] = data;
		m_tail = (m_tail + 1) % m_cap;
	}
	T head() noexcept
	{
		if (m_tail == m_head)
			return nullptr;
		return m_arr[m_head];
	}
	void dequeue() noexcept
	{
		if (m_tail == m_head)
			return;
		m_head = (m_head + 1) % m_cap;
	}

private:
	size_t m_cap;
	int m_head = 0;
	int m_tail = 0;
	T* m_arr = nullptr;
};

END_NAMESPACE(yyyyshen)

#endif // !QUEUE_HPP
