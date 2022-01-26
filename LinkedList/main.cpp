#include <iostream>
#include "List.h"

int main()
{
	List<int> list = List<int>();
	list.destroy();
	list.pushFront(1);
	list.pushFront(2);
	list.pushFront(3);
	list.pushFront(4);
	list.pushFront(5);
	list.pushBack(6);
	list.pushBack(7);
	list.pushBack(8);
	list.insert(22, 3);

	
	list.sort();
	list.print();
	return 0;
}