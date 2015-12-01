#include <iostream>
#include <SDL.h>
#include <thread>
#include <string>
#include <sstream>
#include "UniverseChunk.h"
#include "Main.h"
#include "LightEmitter.h"
#include "cmdHandler.h"

//unsigned int fp_control_state = _controlfp(_EM_INEXACT, _MCW_EM);

#define VERSION_NAME "Densiotropic Universe 0.2"

using namespace std;

UniverseChunk Universe;
SDL_Renderer* renderer;
string cmdString = "12";

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

	thread inputHandler(getCmdIn);

	Universe = UniverseChunk(xSize,ySize);
	vector<LightEmitter> lightEmitters;
	
	LightEmitter heldEmitter(0.0f, {0.0f,0.0f,0.0f,0.0f,0.0f});

	while (isRunning)
	{
		//cout << cmdString << endl;
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
					cout << Universe.lightMatrixBase[mainEvent.button.x][mainEvent.button.y].lightDensity;
					for (int i = 0; i < 5; i++)
					{
						cout << " " << Universe.lightMatrixBase[mainEvent.button.x][mainEvent.button.y].diffuseRatio[i];
					}
					cout << endl;
				}
				else if (mainEvent.button.button == SDL_BUTTON_RIGHT && heldEmitter.lightDensity != 0.0f)
				{
					for (int e = 0; e < lightEmitters.size(); e++)
					{
						if (lightEmitters[e].x == mainEvent.button.x && lightEmitters[e].x == mainEvent.button.y)
						{
							lightEmitters.erase(lightEmitters.begin() + e);
							break;
						}
					}
					heldEmitter.x = mainEvent.button.x;
					heldEmitter.y = mainEvent.button.y;
					lightEmitters.push_back(heldEmitter);
					cout << "Placed emitter: " << heldEmitter.x << "," << heldEmitter.y << endl;
				}
			}
		}
		if (cmdString != "")
		{
			istringstream cmdIn(cmdString);
			string command;
			cmdIn >> command;
			if (command == "emitter")
			{
				float lightDensity;
				array<float, 5> diffuseRatio;
				cmdIn >> lightDensity >> diffuseRatio[Up] >> diffuseRatio[Down] >> diffuseRatio[Left] >> diffuseRatio[Right] >> diffuseRatio[Middle];
				heldEmitter = LightEmitter(lightDensity, diffuseRatio);
				cout << "Emitter set: " << lightDensity << endl;
			}
			else if (command == "emplace" && heldEmitter.lightDensity != 0.0f)
			{
				int x, y;
				cmdIn >> x >> y;
				for (int e = 0; e < lightEmitters.size(); e++)
				{
					if (lightEmitters[e].x == x && lightEmitters[e].x == y)
					{
						lightEmitters.erase(lightEmitters.begin() + e);
						break;
					}
				}
				heldEmitter.x = x;
				heldEmitter.y = y;
				lightEmitters.push_back(heldEmitter);
				cout << "Placed emitter: " << heldEmitter.x << "," << heldEmitter.y << endl;
			}
			else if (command == "undo")
			{
				lightEmitters.pop_back();
			}
			else if (command == "clear")
			{
				lightEmitters.clear();
			}
			cmdString = "";
		}
		else
		{
			
		}

		for (int i = 0; i < 10; i++)
		{
			for (int e = 0; e < lightEmitters.size(); e++)
			{
				lightEmitters[e].emit();
			}
	
			for (int x = 0; x < xSize; x++)
			{
				for (int y = 0; y < ySize; y++)
				{
					Universe.lightMatrixBase[x][y].diffuse(x, y);
				}
			}
			Universe.lightMatrixBase.swap(Universe.lightMatrixSuper);
		}
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
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