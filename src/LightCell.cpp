#include "LightCell.h"
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
