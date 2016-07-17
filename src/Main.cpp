#include <iostream>
#include <SDL.h>
#include <thread>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "Main.h"
#include "LightCell.h"
#include "LightEmitter.h"
#include "cmdHandler.h"

//unsigned int fp_control_state = _controlfp(_EM_INEXACT, _MCW_EM);

#define VERSION_NAME "Densiotropic Universe 0.1.5"

using namespace std;

SDL_Renderer* renderer;
concurrency::concurrent_queue<std::string> cmdQueue;

int main(int, char**)
{

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		return 1;
	}

	bool isRunning = true;

	int xSize, ySize = 0;
	bool vsync;

	{
		string input, vsyncin;
		cout << "xSize ySize vsync (enter for defaults): ";
		getline(cin, input);
		istringstream s(input);
		s >> xSize >> ySize;
		if (xSize == 0 || ySize == 0)
		{
			xSize = 640;
			ySize = 640;
		}
		if (s >> vsyncin)
		{
			vsync = vsyncin != "false";
		}
		else
		{
			vsync = true;
		}
	}

	int xMax = xSize + 1;
	int yMax = ySize + 1;

	SDL_Window* window = SDL_CreateWindow(VERSION_NAME, 20, 50, xSize, ySize, SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | (vsync ? SDL_RENDERER_PRESENTVSYNC : 0));
	Uint32* pixels = new Uint32[xSize*ySize];
	SDL_Texture* renderTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, xSize, ySize);
	SDL_Event mainEvent;

	thread inputHandler(getCmdIn);

	int* pixel = new int(0x00FF0000);
	SDL_Surface* cursorSurface = SDL_CreateRGBSurfaceFrom(pixel, 1, 1, 24, 1, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	SDL_Cursor* cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);
	SDL_SetCursor(cursor);
	SDL_FreeSurface(cursorSurface);
	delete pixel;

	vector<vector<LightCell>> lightMatrixBase = vector<vector<LightCell>>(xSize + 2, std::vector<LightCell>(ySize + 2));
	vector<vector<LightCell>> lightMatrixSuper = vector<vector<LightCell>>(xSize + 2, std::vector<LightCell>(ySize + 2));

	vector<LightEmitter> lightEmitters;

	LightEmitter heldEmitter(0.0f, { 0.0f,0.0f,0.0f,0.0f,0.0f });

	int delay = 0;

	int speed = 10;
	bool curPhase = true;
	bool emitHand = false;

	string cmdCache;

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
				if (mainEvent.key.keysym.sym == SDLK_r)
				{
					delay = 0;
				}
				else if (mainEvent.key.keysym.sym == SDLK_e)
				{
					int mouseX, mouseY;
					SDL_GetMouseState(&mouseX, &mouseY);
					LightCell* lc = &lightMatrixBase[mouseX][mouseY];
					cout << lc->lightDensity << " " << lc->diffuseUp << " " << lc->diffuseDown << " " << lc->diffuseLeft << " " << lc->diffuseRight << " " << lc->diffuseMiddle << endl;
				}
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
						cout << "Placed emitter: " << lightEmitters.back().x << "," << lightEmitters.back().y << endl;
					}
				}
				else if (mainEvent.button.button == SDL_BUTTON_MIDDLE)
				{
					LightCell* lc = &lightMatrixBase[mainEvent.button.x][mainEvent.button.y];
					cout << lc->lightDensity << " " << lc->diffuseUp << " " << lc->diffuseDown << " " << lc->diffuseLeft << " " << lc->diffuseRight << " " << lc->diffuseMiddle << endl;
				}
			}
			else if (mainEvent.type == SDL_MOUSEBUTTONUP && mainEvent.button.button == SDL_BUTTON_LEFT)
			{
				emitHand = false;
			}
		}

		if (delay < 1)
		{
			if (cmdQueue.try_pop(cmdCache))
			{
				istringstream cmdIn(cmdCache);
				string command;
				cmdIn >> command;
				if (command == "emitter")
				{
					float lightDensity;
					array<float, 5> diffuseRatio;
					bool phase;
					cmdIn >> lightDensity >> diffuseRatio[Up] >> diffuseRatio[Down] >> diffuseRatio[Left] >> diffuseRatio[Right] >> diffuseRatio[Middle];
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
						lightEmitters.push_back(heldEmitter);
						lightEmitters.back().x = x;
						lightEmitters.back().y = y;
						lightEmitters.back().phase = lightEmitters.back().originalPhase ^ ((x % 2) == (y % 2));
						cout << "Placed emitter: " << lightEmitters.back().x << "," << lightEmitters.back().y << endl;
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
						lightEmitters.erase(lightEmitters.begin() + removeNum);
					}
				}
				else if (command == "clear")
				{
					lightEmitters.clear();
				}
				else if (command == "reset")
				{
					lightMatrixBase = vector<vector<LightCell>>(xSize + 2, std::vector<LightCell>(ySize + 2));
					lightMatrixSuper = vector<vector<LightCell>>(xSize + 2, std::vector<LightCell>(ySize + 2));
				}
				else if (command == "speed")
				{
					cmdIn >> speed;
					cout << "Set speed: " << speed << endl;
				}
				else if (command == "load")
				{
					string fileName;
					cmdIn >> fileName;

					string newCmd;
					ifstream loadFile(fileName);
					while (getline(loadFile, newCmd))
					{
						if (newCmd.substr(0, 2) != "//")
						{
							cmdQueue.push(newCmd);
						}
					}

					cout << "Commands loaded from: " << fileName << endl;
				}
				else if (command == "save")
				{
					string fileName;
					cmdIn >> fileName;

					ofstream saveFile;
					saveFile.open(fileName, ofstream::trunc);
					for (int e = 0; e < lightEmitters.size(); e++)
					{
						LightEmitter em = lightEmitters[e];
						saveFile << "emitter " << em.lightDensity;
						for (int i = 0; i < 5; i++)
						{
							saveFile << " " << em.diffuseRatio[i];
						}
						if (!em.fullPhase)
						{
							saveFile << " " << em.originalPhase;
						}
						saveFile << endl;
						saveFile << "emplace " << em.x << " " << em.y << endl;
					}
					saveFile.close();

					cout << "Emitters saved as: " << fileName << endl;
				}
				else if (command == "sleep")
				{
					int duration;
					cmdIn >> duration;
					delay = duration;
				}
				else
				{
					cout << "Unknown command: " << cmdCache << endl;
				}
			}
		}
		else
		{
			delay--;
		}


		//PROCESSING

		if (emitHand)
		{
			SDL_GetMouseState(&heldEmitter.x, &heldEmitter.y);
			heldEmitter.phase = heldEmitter.originalPhase ^ ((heldEmitter.x % 2) == (heldEmitter.y % 2));
		}

		LightCell* cur;
		LightCell* curSuper;

		for (int i = 0; i < speed; i++)
		{
			if (emitHand && heldEmitter.lightDensity != 0.0f)
			{
				heldEmitter.emit(curPhase, lightMatrixBase);
			}
			for (int e = 0; e < lightEmitters.size(); e++)
			{
				lightEmitters[e].emit(curPhase, lightMatrixBase);
			}

			for (int x = 1; x < xMax; x++)
			{
				for (int y = 1; y < yMax; y++)
				{
					cur = lightMatrixBase[x].data() + y;
					curSuper = lightMatrixSuper[x].data() + y;

					if (cur->lightDensity >= 0.00390625f)
					{
						const float ratioMult = 1.0f / cur->lightDensity;

						(curSuper - 1)->addData(cur->diffuseUp, cur->diffuseUp, cur->diffuseDown, cur->diffuseLeft, cur->diffuseRight, cur->diffuseMiddle, cur->diffuseUp * ratioMult);
						(curSuper + 1)->addData(cur->diffuseDown, cur->diffuseUp, cur->diffuseDown, cur->diffuseLeft, cur->diffuseRight, cur->diffuseMiddle, cur->diffuseDown * ratioMult);
						lightMatrixSuper[x - 1][y].addData(cur->diffuseLeft, cur->diffuseUp, cur->diffuseDown, cur->diffuseLeft, cur->diffuseRight, cur->diffuseMiddle, cur->diffuseLeft * ratioMult);
						lightMatrixSuper[x + 1][y].addData(cur->diffuseRight, cur->diffuseUp, cur->diffuseDown, cur->diffuseLeft, cur->diffuseRight, cur->diffuseMiddle, cur->diffuseRight * ratioMult);
						curSuper->addData(cur->diffuseMiddle, cur->diffuseUp, cur->diffuseDown, cur->diffuseLeft, cur->diffuseRight, cur->diffuseMiddle, cur->diffuseMiddle * ratioMult);

						memset(cur, 0, sizeof(LightCell));
					}
					else if (cur->lightDensity != 0.0f)
					{
						memset(cur, 0, sizeof(LightCell));
					}
				}
			}
			lightMatrixBase.swap(lightMatrixSuper);
			curPhase = !curPhase;
		}


		//DRAWING

		memset(pixels, 0, xSize * ySize * sizeof(Uint32));
		Uint8 cacheDensity;
		for (int x = 1; x < xMax; x++)
		{
			for (int y = 1; y < yMax; y++)
			{
				//if (Universe.lightMatrixBase[x][y].lightDensity > 0.75F)
				{
					cacheDensity = lightMatrixBase[x][y].lightDensity >= 255.0F ? 255 : (Uint8)lightMatrixBase[x][y].lightDensity;
					pixels[(y - 1) * xSize + x - 1] = cacheDensity | cacheDensity << 8 | cacheDensity << 16;
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