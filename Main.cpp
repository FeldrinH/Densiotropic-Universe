#include <iostream>
#include <SDL.h>
#include <thread>
#include "cmdHandler.h"

#define VERSION_NAME "Densiotropic Universe 0.1"

using namespace std;

void init(int sizeX, int sizeY, string &cmdIn)
{
	SDL_Window* window = SDL_CreateWindow(VERSION_NAME, 20, 50, sizeX, sizeY, SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
	SDL_Event mainEvent;

	while (true)
	{
		while (SDL_PollEvent(&mainEvent) != 0)
		{
			if (mainEvent.type == SDL_QUIT)
			{
				cout << "Deuniversifying..." << endl;
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				return;
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
}

int main(int, char**) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		return 1;
	}

	string cmdIn = "";
	bool getInput = true;
	thread inputHandler(getCmdIn, cmdIn, getInput);

	init(640, 640, cmdIn);
	while (true)
	{
		int x, y = 0;
		cin >> x, y;
		init(x, y, cmdIn);
	}

	//SDL_Quit();
	return 0;
}