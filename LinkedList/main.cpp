#include <iostream>
#include "List.h"
#include <Windows.h>
#include <excpt.h>

void testIter(List<int> list)
{
	for (Iterator<int> iter = list.begin(); iter != list.end(); ++iter)
		int val = *iter;
}

int allocationAndDeallocation()
{
	try
	{
		List<int>* list = new List<int>();
		list->pushBack(1);
		list->pushFront(2);
		list->destroy();
		list->destroy();
		testIter(*list);
		list->print();
		list->pushBack(3);
		list->remove(1);
		testIter(*list);
		list->print();
		Iterator<int> iter;
		list->getData(iter, 0);
		list->insert(3, 3);
		list->sort();

		if (list->contains(1))
			return 0;

		delete list;
	}
	catch (...)
	{
		return 0;
	}

	
	system("cls");
	return 1;
}

bool checkOrder(List<int> list)
{
	Iterator<int> iter;

	if (list.getLength() != 5)
		return false;

	for (int i = 0; i < list.getLength(); i++)
	{
		if (!list.getData(iter, i))
			return false;

		if (*iter != i + 1)
			return false;
	}

	return true;
}

int addingNodes()
{
	try
	{
		List<int> list = List<int>();

		list.insert(3, 0);
		list.insert(2, 0);
		list.pushFront(1);
		list.pushBack(5);
		list.insert(4, 3);

		if (!checkOrder(list))
			return 0;
	}
	catch (...)
	{
		return 0;
	}

	return 1;
}

int pushFront()
{
	try
	{
		List<int> list = List<int>();

		list.destroy();
		list.pushFront(5);
		list.pushFront(4);
		list.pushFront(3);
		list.pushFront(2);
		list.pushFront(1);

		if (!checkOrder(list))
			return 0;
	}
	catch (...)
	{
		return 0;
	}

	return 1;
}

int pushBack()
{
	try
	{
		List<int> list = List<int>();
		list.pushBack(1);
		list.pushBack(2);
		list.pushBack(3);
		list.pushBack(4);
		list.pushBack(5);

		if (!checkOrder(list))
			return 0;
	}
	catch (...)
	{
		return 0;
	}

	return 1;
}

int insert()
{

	try
	{
		List<int> list = List<int>();

		list.insert(5, 0);
		list.insert(1, 0);
		list.insert(2, 1);
		list.insert(3, 2);
		list.insert(4, 3);

		if (!checkOrder(list))
			return 0;
	}
	catch (...)
	{
		return 0;
	}

	return 1;
}

int sort()
{
	try
	{
		List<int> list = List<int>();

		list.insert(1, 0);
		list.insert(3, 0);
		list.pushFront(4);
		list.pushBack(2);
		list.insert(5, 3);
		list.sort();

		if (!checkOrder(list))
			return 0;

		list.destroy();
		list.sort();

		list.destroy();
		list.pushBack(1);
		list.sort();
	}
	catch (...)
	{
		return 0;
	}

	return 1;
}

int assignment()
{
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
			return 0;

		list2 = list;

		if (!checkOrder(list2))
			return 0;

		list.destroy();
		if (!checkOrder(list2))
			return 0;
	}
	catch (...)
	{
		return 0;
	}

	return 1;
}

int main()
{
	int score = allocationAndDeallocation();
	score += addingNodes();
	score += pushFront();
	score += pushBack();
	score += insert();
	score += sort();
	score += assignment();
	std::cout << "Score: " << score;
	return 0;
}