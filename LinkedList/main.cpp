#include <iostream>
#include "List.h"



int main()
{

	List<int> list = List<int>();

	int score = list.startTest();
	std::cout << "Score: " << score << "/" << "7";
	return 0;
}
