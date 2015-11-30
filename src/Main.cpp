#include <iostream>
#include <SDL.h>
#include <thread>
#include <string>
#include "cmdHandler.h"
#include <sstream>
#include "UniverseChunk.h"
#include "Main.h"

//unsigned int fp_control_state = _controlfp(_EM_INEXACT, _MCW_EM);

#define VERSION_NAME "Densiotropic Universe 0.2"

using namespace std;

UniverseChunk Universe;
SDL_Renderer* renderer;

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
	int xSize, ySize = 0;

	istringstream s(size);
	s >> xSize >> ySize;
	if (xSize == 0 || ySize == 0)
	{
		xSize = 640;
		ySize = 640;
	}

	SDL_Window* window = SDL_CreateWindow(VERSION_NAME, 20, 50, xSize, ySize, SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
	SDL_Event mainEvent;

	string cmdIn = "";
	thread inputHandler(getCmdIn, cmdIn, isRunning);

	Universe = UniverseChunk(xSize,ySize);
	//Universe.lightMatrixBase[320][320] = LightCell(4096.0F, { 1.0F,1.0F,1.0F,1.0F,0.0F });

	while (isRunning)
	{
		while (SDL_PollEvent(&mainEvent) != 0)
		{
			if (mainEvent.type == SDL_QUIT)
			{
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

		for (int i = 0; i < 10; i++)
		{
		Universe.lightMatrixBase[400][400].addData(192.0f, { 1.0F,0.0F,1.0F,1.0F,0.0F }, 64.0f);
		Universe.lightMatrixBase[401][300].addData(192.0f, { 0.0F,1.0F,1.0F,1.0F,0.0F }, 64.0f);
	
			for (int x = 0; x < xSize; x++)
			{
				for (int y = 0; y < ySize; y++)
				{
					Universe.lightMatrixBase[x][y].diffuse(x, y);
				}
			}
			Universe.lightMatrixBase.swap(Universe.lightMatrixSuper);
		}
		for (int x = 0; x < xSize; x++)
		{
			for (int y = 0; y < ySize; y++)
			{
				Universe.lightMatrixBase[x][y].draw(x,y);
			}
		}

		SDL_RenderPresent(renderer);
	}

	SDL_Quit();
	exit(0);
	return 0;
}