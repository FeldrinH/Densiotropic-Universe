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

#define VERSION_NAME "Densiotropic Universe 0.1.4"

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
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
	Uint32* pixels = new Uint32[xSize*ySize];
	SDL_Texture* renderTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, xSize, ySize);
	SDL_Event mainEvent;

	thread inputHandler(getCmdIn);
	
	int* pixel = new int(0x00FF0000);
	SDL_Surface* cursorSurface = SDL_CreateRGBSurfaceFrom(pixel, 1, 1, 24, 1, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	SDL_Cursor* cursor = SDL_CreateColorCursor(cursorSurface,0,0);
	SDL_SetCursor(cursor);
	SDL_FreeSurface(cursorSurface);
	delete pixel;

	Universe = UniverseChunk(xSize,ySize);
	vector<LightEmitter> lightEmitters;
	
	LightEmitter heldEmitter(0.0f, {0.0f,0.0f,0.0f,0.0f,0.0f});

	int speed = 10;
	bool curPhase = true;
	bool emitHand = false;

	while (isRunning)
	{
		//EVENT HANDLING

		while (SDL_PollEvent(&mainEvent) != 0)
		{
			if (mainEvent.type == SDL_QUIT)
			{
				cout << "Deuniversifying..." << endl;
				isRunning = false;
			}
			else if (mainEvent.type == SDL_KEYDOWN)
			{

			}
			else if (mainEvent.type == SDL_MOUSEBUTTONDOWN)
			{
				if (mainEvent.button.button == SDL_BUTTON_LEFT)
				{
					emitHand = true;
				}
				else if (mainEvent.button.button == SDL_BUTTON_RIGHT)
				{
					for (int e = 0; e < lightEmitters.size(); e++)
					{
						if (lightEmitters[e].x == mainEvent.button.x && lightEmitters[e].y == mainEvent.button.y)
						{
							lightEmitters.erase(lightEmitters.begin() + e);
							cout << "Removed emitter: " << mainEvent.button.x << "," << mainEvent.button.y << endl;
							break;
						}
					}
					if (heldEmitter.lightDensity != 0.0f)
					{
						lightEmitters.push_back(heldEmitter);
						lightEmitters.back().x = mainEvent.button.x;
						lightEmitters.back().y = mainEvent.button.y;
						lightEmitters.back().phase = lightEmitters.back().originalPhase ^ ((mainEvent.button.x % 2) == (mainEvent.button.y % 2));
						cout << "Placed emitter: " << heldEmitter.x << "," << heldEmitter.y << endl;
					}
				}
				else if (mainEvent.button.button == SDL_BUTTON_MIDDLE)
				{
					cout << Universe.lightMatrixBase[mainEvent.button.x][mainEvent.button.y].lightDensity;
					for (int i = 0; i < 5; i++)
					{
						cout << " " << Universe.lightMatrixBase[mainEvent.button.x][mainEvent.button.y].diffuseRatio[i];
					}
					cout << endl;
				}
			}
			else if (mainEvent.type == SDL_MOUSEBUTTONUP && mainEvent.button.button == SDL_BUTTON_LEFT)
			{
				emitHand = false;
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
				bool phase;
				cmdIn >> lightDensity >> diffuseRatio[Up] >> diffuseRatio[Down] >> diffuseRatio[Right] >> diffuseRatio[Left] >> diffuseRatio[Middle];
				if (cmdIn >> phase)
				{
					heldEmitter = LightEmitter(lightDensity, diffuseRatio, phase);
				}
				else 
				{
					heldEmitter = LightEmitter(lightDensity, diffuseRatio);
				}

				cout << "Density: " << lightDensity << "  Ratio:";
				for (int i = 0; i < 5; i++)
				{
					cout << " " << heldEmitter.diffuseRatio[i];
				}
				if (!heldEmitter.fullPhase)
				{
					cout << "  Phase: " << heldEmitter.phase;
				}
				cout << endl;
			}
			else if (command == "emplace")
			{
				int x, y;
				cmdIn >> x >> y;
				for (int e = 0; e < lightEmitters.size(); e++)
				{
					if (lightEmitters[e].x == x && lightEmitters[e].y == y)
					{
						lightEmitters.erase(lightEmitters.begin() + e);
						cout << "Removed emitter: " << x << "," << y << endl;
						break;
					}
				}
				if (heldEmitter.lightDensity != 0.0f)
				{
					heldEmitter.x = x;
					heldEmitter.y = y;
					lightEmitters.push_back(heldEmitter);
					lightEmitters.back().phase = lightEmitters.back().originalPhase ^ ((x % 2) == (y % 2));
					cout << "Placed emitter: " << heldEmitter.x << "," << heldEmitter.y << endl;
				}
			}
			else if (command == "undo")
			{
				if (!lightEmitters.empty())
				{
					lightEmitters.pop_back();
				}
			}
			else if (command == "remove")
			{
				int removeNum;
				cmdIn >> removeNum;
				if (removeNum < lightEmitters.size())
				{
					lightEmitters.erase(lightEmitters.begin()+removeNum);
				}
			}
			else if (command == "clear")
			{
				lightEmitters.clear();
			}
			else if (command == "reset")
			{
				Universe = UniverseChunk(xSize, ySize);
			}
			else if (command == "speed")
			{
				cmdIn >> speed;
				cout << "Set speed: " << speed << endl;
			}
			cmdString = "";
		}


		//PROCESSING

		if (emitHand)
		{
			SDL_GetMouseState(&heldEmitter.x, &heldEmitter.y);
			heldEmitter.phase = heldEmitter.originalPhase ^ ((heldEmitter.x % 2) == (heldEmitter.y % 2));
		}

		for (int i = 0; i < speed; i++)
		{
			if (emitHand && heldEmitter.lightDensity != 0.0f)
			{
				heldEmitter.emit(curPhase);
			}
			for (int e = 0; e < lightEmitters.size(); e++)
			{
				lightEmitters[e].emit(curPhase);
			}
	
			for (int x = 0; x < xSize; x++)
			{
				for (int y = 0; y < ySize; y++)
				{
					if (Universe.lightMatrixBase[x][y].lightDensity >= 0.00390625f)
					{
						Universe.lightMatrixBase[x][y].diffuse(x, y);
					}
					else if (Universe.lightMatrixBase[x][y].lightDensity != 0.0f)
					{
						Universe.lightMatrixBase[x][y].lightDensity = 0.0f;
						Universe.lightMatrixBase[x][y].diffuseRatio = { 0.0f,0.0f,0.0f,0.0f,0.0f };
					}
				}
			}
			Universe.lightMatrixBase.swap(Universe.lightMatrixSuper);
			curPhase = !curPhase;
		}

		
		//DRAWING

		memset(pixels, 0, xSize * ySize * sizeof(Uint32));
		Uint8 cacheDensity;
		for (int x = 0; x < xSize; x++)
		{
			for (int y = 0; y < ySize; y++)
			{
				if (Universe.lightMatrixBase[x][y].lightDensity > 0.75F)
				{
					cacheDensity = Universe.lightMatrixBase[x][y].lightDensity >= 255.0F ? 255 : (Uint8)Universe.lightMatrixBase[x][y].lightDensity;
					pixels[y * xSize + x] = cacheDensity | cacheDensity << 8 | cacheDensity << 16;
				}
				/*else
				{
					pixels[y * xSize + x] = 255;
 				}*/
			}
		}
		
		//SDL_RenderClear(renderer);
		SDL_UpdateTexture(renderTexture, NULL, pixels, xSize * sizeof(Uint32));
		SDL_RenderCopy(renderer, renderTexture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	delete[] pixels;
	SDL_DestroyTexture(renderTexture);
	SDL_FreeCursor(cursor);
	SDL_Quit();
	exit(0);
	return 0;
}