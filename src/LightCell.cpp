#include "LightCell.h"
#include "UniverseChunk.h"
#include "Main.h"
#include "SDL.h"
#include <iostream>

using namespace std;

LightCell::LightCell()
{
	lightDensity = 0;
	diffuseRatio = {0.0f,0.0f,0.0f,0.0f,0.0f};
}

LightCell::LightCell(float dens, array<float, 5> ratio)
{
	float ratioMult = 0;

	for (int a = 0; a < 5; a++)
	{
		ratioMult += ratio[a];
	}
	ratioMult = 1 / ratioMult;
	for (int a = 0; a < 5; a++)
	{
		ratio[a] = ratio[a] * ratioMult * dens;
	}

	lightDensity = dens;
	diffuseRatio = ratio;
}

LightCell::~LightCell()
{
}

void LightCell::diffuse(int x, int y)
{
	/*if (lightDensity != lightDensity)
	{
		lightDensity = 0.0f;
		diffuseRatio.fill(0.0F);
		cout << "NaN" << endl;
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawPoint(renderer, x, y);
	}*/
	
	float ratioMult = 1 / lightDensity;
	for (int i = 0; i < 5; i++)
	{
		Universe.lightMatrixSuper[x + dirX[i]][y + dirY[i]].addData(diffuseRatio[i], diffuseRatio, diffuseRatio[i] * ratioMult);
	}

	lightDensity = 0.0F;
	diffuseRatio.fill(0.0F);
}

inline void LightCell::addData(float dens, array<float, 5> ratio, float mult)
{
	lightDensity += dens;
	for (int i = 0; i < 5; i++)
	{
		diffuseRatio[i] += ratio[i] * mult;
		/*if (diffuseRatio[i] != diffuseRatio[i])
		{
			lightDensity = 0.0f;
			diffuseRatio.fill(0.0F);
			cout << "NaN in addData()" << endl;
		}*/
	}
}

/*__forceinline int LightCell::getXDir(int dir)
{
	return dir == Left ? -1 : dir == Right ? 1 : 0;
}

__forceinline int LightCell::getYDir(int dir)
{
	return dir == Up ? -1 : dir == Down ? 1 : 0;
}*/

/*void LightCell::draw(int x, int y)
{
	if (lightDensity > 255.0F)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, lightDensity, lightDensity, lightDensity, 255);
	}
	SDL_RenderDrawPoint(renderer, x, y);
}*/
