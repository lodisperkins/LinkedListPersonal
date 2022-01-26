#pragma once

template<typename T>
class Node
{
public:
	Node() { next = nullptr; previous = nullptr; }
	Node(T value) { data = value; next = nullptr; previous = nullptr; }
	Node<T>* next;
	Node<T>* previous;
	T data;
};