#include "LightCell.h"
#include "UniverseChunk.h"
#include "Main.h"
#include "SDL.h"
#include <iostream>

using namespace std;

LightCell::LightCell()
{
	lightDensity = 0.0f;
	diffuseUp = 0.0f;
	diffuseDown = 0.0f;
	diffuseLeft = 0.0f;
	diffuseRight = 0.0f;
	diffuseMiddle = 0.0f;
}

LightCell::LightCell(const float dens, const array<float, 5> ratio)
{
	float ratioMult = 0.0f;

	for (int a = 0; a < 5; a++)
	{
		ratioMult += ratio[a];
	}

	ratioMult = dens / ratioMult;

	diffuseUp = ratio[0] * ratioMult;
	diffuseDown = ratio[1] * ratioMult;
	diffuseLeft = ratio[2] * ratioMult;
	diffuseRight = ratio[3] * ratioMult;
	diffuseMiddle = ratio[4] * ratioMult;

	lightDensity = dens;
}

LightCell::~LightCell()
{
}

void LightCell::diffuse(const int x, const int y)
{
	/*if (lightDensity != lightDensity)
	{
		lightDensity = 0.0f;
		diffuseRatio.fill(0.0F);
		cout << "NaN" << endl;
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawPoint(renderer, x, y);
	}*/

	const float ratioMult = 1 / lightDensity;

	Universe.lightMatrixSuper[x][y - 1].addData(diffuseUp, diffuseUp, diffuseDown, diffuseLeft, diffuseRight, diffuseMiddle, diffuseUp * ratioMult);
	Universe.lightMatrixSuper[x][y + 1].addData(diffuseDown, diffuseUp, diffuseDown, diffuseLeft, diffuseRight, diffuseMiddle, diffuseDown * ratioMult);
	Universe.lightMatrixSuper[x - 1][y].addData(diffuseLeft, diffuseUp, diffuseDown, diffuseLeft, diffuseRight, diffuseMiddle, diffuseLeft * ratioMult);
	Universe.lightMatrixSuper[x + 1][y].addData(diffuseRight, diffuseUp, diffuseDown, diffuseLeft, diffuseRight, diffuseMiddle, diffuseRight * ratioMult);
	Universe.lightMatrixSuper[x][y].addData(diffuseMiddle, diffuseUp, diffuseDown, diffuseLeft, diffuseRight, diffuseMiddle, diffuseMiddle * ratioMult);

	lightDensity = 0.0F;
	diffuseUp = 0.0f;
	diffuseDown = 0.0f;
	diffuseLeft = 0.0f;
	diffuseRight = 0.0f;
	diffuseMiddle = 0.0f;
}

inline void LightCell::addData(const float dens, const float ratioUp, const float ratioDown, const float ratioLeft, const float ratioRight, const float ratioMiddle, const float mult)
{
	lightDensity += dens;
	
	diffuseUp += ratioUp * mult;
	diffuseDown += ratioDown * mult;
	diffuseLeft += ratioLeft * mult;
	diffuseRight += ratioRight * mult;
	diffuseMiddle += ratioMiddle * mult;

	/*if (diffuseRatio[i] != diffuseRatio[i])
	{
	lightDensity = 0.0f;
	diffuseRatio.fill(0.0F);
	cout << "NaN in addData()" << endl;
	}*/
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
