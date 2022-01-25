#pragma once
#include "Node.h"

template <typename T>
class Iterator
{
public:
	Iterator() { current = nullptr; }
	Iterator(Node<T>* node) { m_current = node; }
	Iterator<T> operator ++() { return Iterator<T>(m_current->next); }
	Iterator<T> operator --() { return Iterator<T>(m_current->previous); }
	bool operator == (const Iterator<T>& iter) { return *iter == m_current->data; }
	T operator *() { return m_current->data; }

private:
	Node<T>* m_current;
};