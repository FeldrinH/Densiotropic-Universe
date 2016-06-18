#include <iostream>
#include "cmdHandler.h"
#include "Main.h"

void getCmdIn()
{
	string cacheString;
	while (true)
	{
		std::getline(std::cin, cacheString);
		cmdQueue.push(cacheString);
		//std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}