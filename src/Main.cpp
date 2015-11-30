#include <iostream>
#include <SDL.h>
#include <thread>
#include <string>
#include "cmdHandler.h"
#include <sstream>
#include "UniverseChunk.h"

#define VERSION_NAME "Densiotropic Universe 0.2"

using namespace std;

UniverseChunk Universe;

int main(int, char**) 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		return 1;
	}
	
	bool isRunning = true;

	string size = "";
	getline(cin, size);
	int x, y = 0;

	istringstream s(size);
	s >> x >> y;
	if (x == 0 || y == 0)
	{
		x = 640;
		y = 640;
	}

	SDL_Window* window = SDL_CreateWindow(VERSION_NAME, 20, 50, x, y, SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
	SDL_Event mainEvent;

	string cmdIn = "";
	thread inputHandler(getCmdIn, cmdIn, isRunning);

	Universe = new UniverseChunk(x,y);

	while (isRunning)
	{
		while (SDL_PollEvent(&mainEvent) != 0)
		{
			if (mainEvent.type == SDL_QUIT)
			{
				delete Universe;
				cout << "Deuniversifying..." << endl;
				isRunning = false;
			}
			if (mainEvent.type == SDL_KEYDOWN)
			{

			}
			if (mainEvent.type == SDL_MOUSEBUTTONDOWN)
			{
				if (mainEvent.button.button == SDL_BUTTON_LEFT)
				{

				}
				else if (mainEvent.button.button == SDL_BUTTON_RIGHT)
				{

				}
			}
		}

		if (cmdIn != "")
		{
		}

		
	}

	SDL_Quit();
	exit(0);
	return 0;
}