#include "LightCell.h"
#include "UniverseChunk.h"
#include "Main.h"
#include "SDL.h"
#include <iostream>

LightCell::LightCell()
{
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
	if (lightDensity == 0.0F)
	{
		return;
	}

	float ratioMult = 1 / lightDensity;
	
	for (int i = 0; i < 5; i++)
	{
		if (x + getXDir(i) > -1 && x + getXDir(i) < Universe.x && y + getYDir(i) > -1 && y + getYDir(i) < Universe.y)
		{
			Universe.lightMatrixSuper[x + getXDir(i)][y + getYDir(i)].addData(diffuseRatio[i], diffuseRatio, diffuseRatio[i] * ratioMult);
		}
	}

	lightDensity = 0.0F;
	diffuseRatio.fill(0.0F);
}

void LightCell::addData(float dens, array<float, 5> ratio, float mult)
{
	lightDensity += dens;
	for (int i = 0; i < 5; i++)
	{
		diffuseRatio[i] += ratio[i] * mult;
	}
}

int LightCell::getXDir(int dir)
{
	return dir == Left ? -1 : dir == Right ? 1 : 0;
}

int LightCell::getYDir(int dir)
{
	return dir == Up ? -1 : dir == Down ? 1 : 0;
}

void LightCell::draw(int x, int y)
{
	SDL_SetRenderDrawColor(renderer, lightDensity, lightDensity, lightDensity, 255);
	SDL_RenderDrawPoint(renderer, x, y);
}
