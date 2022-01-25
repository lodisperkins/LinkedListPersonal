#pragma once
#include "Iterator.h"
#include <iostream>

template <typename T>
class List
{
public:
	List();
	List(List<T>& other);
	~List();

	void initialize();
	void destroy();

	Iterator<T> begin();
	Iterator<T> end();

	bool contains(const T& object) const;
	bool isEmpty() const;
	void print() const;

	void pushFront(const T& value);
	void pushBack(const T& value);
	bool insert(const T& value, int index);
	bool remove(const T& value);
	void sort();

	bool getData(Iterator<T>& iter, int index);
	int getLength() const;
	const List<T>& operator =(const List<T>& otherList);
private:
	Node<T>* m_first;
	Node<T>* m_last;
	int m_nodeCount;
};

template<typename T>
inline List<T>::List()
{
	initialize();
	m_first = nullptr;
	m_last = nullptr;
}

template<typename T>
inline List<T>::List(List<T>& other)
{
}

template<typename T>
inline List<T>::~List()
{
	destroy();
}

template<typename T>
inline void List<T>::initialize()
{
	m_nodeCount = 0;
	m_first = nullptr;
	m_last = nullptr;
}

template<typename T>
inline void List<T>::destroy()
{
	for (Node<T>* iter = m_first; iter nullptr;)
	{
		Node<T>* temp = iter;
		iter = iter->next;
		delete temp;
	}
}

template<typename T>
inline Iterator<T> List<T>::begin()
{
	return Iterator<T>(m_first);
}

template<typename T>
inline Iterator<T> List<T>::end()
{
	return Iterator<T>(m_last);
}

template<typename T>
inline bool List<T>::contains(const T& object) const
{
	for (Iterator<T> iter = begin(); iter != end(); ++iter)
	{
		if (*iter == object)
			return true;
	}

	return false;
}

template<typename T>
inline bool List<T>::isEmpty() const
{
	return m_nodeCount == 0;
}

template<typename T>
inline void List<T>::print() const
{
	for (Iterator<T> iter = begin(); iter != end(); ++iter)
	{
		std::cout << *iter << std::endl;
	}
}

template<typename T>
inline void List<T>::pushFront(const T& value)
{
	Node<T>* node = new Node<T>(value);

	if (m_first)
	{
		node->next = m_first->next;

		if (m_first->next)
			m_first->next->previous = node;
	}

	m_first = node;

	if (!m_last) m_last = node;

	m_nodeCount++;
}

template<typename T>
inline void List<T>::pushBack(const T& value)
{
	Node<T>* node = new Node<T>(value);

	if (m_last)
	{
		node->previous = m_last->previous;

		if (m_last->previous)
			m_last->previous->next = node;
	}

	m_last = node;

	if (!m_first) m_first = node;

	m_nodeCount++;
}

template<typename T>
inline bool List<T>::insert(const T& value, int index)
{
	if (index < 0 || index >= m_nodeCount)
		return false;



	return false;
}
