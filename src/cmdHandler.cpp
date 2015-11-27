#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "cmdHandler.h"

void getCmdIn(std::string &inString, const bool &isRunning)
{
	while (true)
	{
		std::getline(std::cin, inString);
		//std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}