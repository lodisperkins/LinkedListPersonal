
#pragma once
#include "Iterator.h"
#include "Node.h"
#include <iostream>

#include <Windows.h>
#include <excpt.h>

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
	int startTest();
	bool checkOrder(List<T>& list);
private:
	Node<T>* m_first = nullptr;
	Node<T>* m_last = nullptr;
	int m_nodeCount = 0;
};

template<typename T>
inline List<T>::List()
{
	initialize();
}

template<typename T>
inline List<T>::List(const List<T>& other)
{
	*this = other;
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
	if (isEmpty())
		return;

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
	if (isEmpty())
		return Iterator<T>(nullptr);

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
	if (index < 0 || index >= m_nodeCount && !isEmpty())
		return false;

	if (isEmpty())
	{
		pushFront(value);
		return true;
	}

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
	if (isEmpty())
		return false;

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
	if (isEmpty())
		return;

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

	if (otherList.isEmpty())
	{
		initialize();
		return *this;
	}

	for (Iterator<T> iter = otherList.begin(); iter != otherList.end(); ++iter)
		pushBack(*iter);

	return *this;
}
template<typename T>
inline int List<T>::startTest()
{


	float score = 0;


	score++;

	try
	{
		List<int>* list = new List<int>();
		list->pushBack(1);
		list->pushFront(2);
		list->destroy();
		list->destroy();
		for (Iterator<int> iter = list->begin(); iter != list->end(); ++iter)
			int val = *iter;
		list->print();
		list->pushBack(3);
		list->remove(1);
		list->pushBack(2);
		list->pushBack(1);
		int val = 0;

		for (Iterator<int> iter = list->begin(); iter != list->end(); ++iter)
		{
			val += *iter;
			if (val > 6)
				throw std::exception();
		}

		if (val != 6)
			throw std::exception();

		list->print();
		Iterator<int> iter;
		list->getData(iter, 0);
		list->insert(3, 3);
		list->sort();

		if (list->contains(1))
			throw std::exception();

		delete list;
	}
	catch (...)
	{
		score--;
	}


	system("cls");

	score++;

	try
	{

		//1/2
		List<int> list = List<int>();

		list.insert(3, 0);
		list.insert(2, 0);
		list.pushFront(1);
		list.pushBack(5);
		list.insert(4, 3);

		Iterator<int> iter;

		list.getData(iter, 4);

		if (*iter != 5)
			throw std::exception();

		if (!checkOrder(list))
			throw std::exception();
	}
	catch (...)
	{
		score--;
	}

	score++;

	try
	{
		//1/2
		List<int> list = List<int>();

		list.destroy();
		list.pushFront(5);
		list.pushFront(4);
		list.pushFront(3);
		list.pushFront(2);
		list.pushFront(1);

		if (!checkOrder(list))
			throw std::exception();
	}
	catch (...)
	{
		score--;
	}

	score++;

	try
	{
		//1/2
		List<int> list = List<int>();
		list.pushBack(1);
		list.pushBack(2);
		list.pushBack(3);
		list.pushBack(4);
		list.pushBack(5);

		if (!checkOrder(list))
			throw std::exception();
	}
	catch (...)
	{
		score--;
	}

	score++;

	try
	{
		//1/2
		List<int> list = List<int>();

		list.insert(5, 0);
		list.insert(1, 0);
		list.insert(2, 1);
		list.insert(3, 2);
		list.insert(4, 3);

		if (!checkOrder(list))
			throw std::exception();
	}
	catch (...)
	{
		score--;
	}

	score++;

	try
	{
		//1/2
		//return 0;
		List<int> list = List<int>();

		list.insert(1, 0);
		list.insert(3, 0);
		list.pushFront(4);
		list.pushBack(2);
		list.insert(5, 3);
		list.sort();

		if (!checkOrder(list))
			throw std::exception();

		list.destroy();
		list.sort();

		list.destroy();
		list.pushBack(1);
		list.sort();
	}
	catch (...)
	{
		score--;
	}

	score++;

	try
	{
		List<int> list = List<int>();
		List<int> list2 = List<int>(list);

		list.pushBack(1);
		list.pushBack(2);
		list.pushBack(3);
		list.pushBack(4);
		list.pushBack(5);

		if (checkOrder(list2))
			throw std::exception();

		list2 = list;

		if (!checkOrder(list2))
			throw std::exception();

		list.destroy();
		if (!checkOrder(list2))
			throw std::exception();
	}
	catch (...)
	{
		score--;
	}

	return score;
}

template<typename T>
inline bool List<T>::checkOrder(List<T>& list)
{
	if (list.m_nodeCount != 5)
		return false;

	Node<int>* iter = list.m_first;
	for (int i = 0; i < list.m_nodeCount; i++)
	{
		if (iter->data != i + 1)
			return false;

		iter = iter->next;
	}

	return true;
}