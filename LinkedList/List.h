#pragma once
#include "Iterator.h"
#include <iostream>

template <typename T>
class List
{
public:
	List();
	List(const List<T>&);
	~List();

	void initialize();
	void destroy();

	Iterator<T> begin() const;
	Iterator<T> end() const;

	bool contains(const T object) const;
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
inline List<T>::List(const List<T>& other)
{
	this = other;
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
	for (Node<T>* iter = m_first; iter != nullptr;)
	{
		Node<T>* temp = iter;
		iter = iter->next;
		delete temp;
	}

	initialize();
}

template<typename T>
inline Iterator<T> List<T>::begin() const
{
	return Iterator<T>(m_first);
}

template<typename T>
inline Iterator<T> List<T>::end() const
{
	return Iterator<T>(m_last->next);
}

template<typename T>
inline bool List<T>::contains(const T object) const
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
	return m_nodeCount <= 0;
}

template<typename T>
inline void List<T>::print() const
{
	if (m_nodeCount <= 0) return;

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
		m_first->previous = node;
		node->next = m_first;
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
		m_last->next = node;
		node->previous = m_last;
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

	Node<T>* newNode = new Node<T>(value);
	Node<T>* oldNode = m_first;

	for (int i = 0; i < index; i++)
	{
		if (oldNode->next)
			oldNode = oldNode->next;
	}

	if (oldNode->previous)
		oldNode->previous->next = newNode;

	newNode->previous = oldNode->previous;
	oldNode->previous = newNode;
	newNode->next = oldNode;

	m_nodeCount++;

	if (index == 0)
		m_first = newNode;
	else if (index == m_nodeCount - 1)
		m_last = newNode;


	return true;
}

template<typename T>
inline bool List<T>::remove(const T& value)
{

	Node<T>* nodeToRemove = m_first;

	if (m_first->data == value && m_nodeCount == 1)
	{
		delete nodeToRemove;
		initialize();
		return true;
	}

	bool nodeRemoved = false;

	for (int i = 0; i < m_nodeCount; i++)
	{
		if (nodeToRemove->data == value)
		{
			if (nodeToRemove->previous)
				nodeToRemove->previous->next = nodeToRemove->next;
			if (nodeToRemove->next)
				nodeToRemove->next->previous = nodeToRemove->previous;

			if (nodeToRemove == m_last)
				m_last = nodeToRemove->previous;
			else if (nodeToRemove == m_first)
				m_first = nodeToRemove->next;

			nodeRemoved = true;
			break;
		}

		if (nodeToRemove->next)
			nodeToRemove = nodeToRemove->next;
	}

	if (nodeRemoved)
	{
		delete nodeToRemove;
		m_nodeCount--;
	}

	return nodeRemoved;
}

template<typename T>
inline void List<T>::sort()
{
	T key;
	int j = 0;
	int i = 1;
	Iterator<T> previousIter;

	for (Iterator<T> iter = ++begin(); iter != end();)
	{
		key = *iter;
		j = i - 1;
		previousIter = iter;
		--previousIter;

		while (key < *previousIter && j >= 0)
		{
			j--;
			--previousIter;

			if (previousIter == Iterator<T>())
				break;
		}

		++iter;
		remove(key);
		insert(key, j + 1);
		i++;
	}
}

template<typename T>
inline bool List<T>::getData(Iterator<T>& iter, int index)
{
	if (index < 0 || index >= m_nodeCount)
		return false;

	iter = begin();

	for (int i = 0; i < index; i++)
		++iter;

	return true;
}

template<typename T>
inline int List<T>::getLength() const
{
	return m_nodeCount;
}

template<typename T>
inline const List<T>& List<T>::operator =(const List<T>& otherList)
{
	destroy();
	m_first = otherList.m_first;
	m_last = otherList.m_last;
}
