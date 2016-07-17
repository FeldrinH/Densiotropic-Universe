#pragma once

#include <cstdint>
#include <array>
#include "SDL.h"
#include <iostream>

using namespace std;

enum Direction { Up, Down, Left, Right, Middle };

const int dirX[5] = { 0, 0, -1, 1, 0 };
const int dirY[5] = { -1, 1, 0, 0, 0 };

class LightCell
{
public:
	LightCell();
	LightCell(const float dens, const array<float, 5> ratio);

	float lightDensity;

	float diffuseUp;
	float diffuseDown;
	float diffuseLeft;
	float diffuseRight;
	float diffuseMiddle;

	/*__forceinline void clear()
	{
		lightDensity = 0.0f;
		diffuseUp = 0.0f;
		diffuseDown = 0.0f;
		diffuseLeft = 0.0f;
		diffuseRight = 0.0f;
		diffuseMiddle = 0.0f;
	}*/

	/*__forceinline void diffuse(const int x, const int y)
	{
		if (lightDensity != lightDensity)
		{
		lightDensity = 0.0f;
		diffuseRatio.fill(0.0F);
		cout << "NaN" << endl;
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawPoint(renderer, x, y);
		}
	}*/

	__forceinline void addData(const float dens, const float ratioUp, const float ratioDown, const float ratioLeft, const float ratioRight, const float ratioMiddle, const float mult)
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

	//__forceinline static int getXDir(int dir);
	//__forceinline static int getYDir(int dir);
};

