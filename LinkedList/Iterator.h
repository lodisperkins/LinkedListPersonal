#pragma once
#include "Node.h"

template <typename T>
class Iterator
{
public:
	Iterator() { m_current = nullptr; }
	Iterator(Node<T>* node) { m_current = node; }
	Iterator<T> operator ++() { return Iterator<T>(m_current->next); }
	Iterator<T> operator --() { return Iterator<T>(m_current->previous); }
	T operator *() { return m_current->data; }
	bool operator == (const Iterator<T>& iter) { return iter.m_current == m_current; }
	bool operator != (const Iterator<T>& iter) { return iter.m_current != m_current; }

private:
	Node<T>* m_current;
};