#pragma once

#include <cstdint>
#include <array>

using namespace std;

enum Direction { Up, Down, Left, Right, Middle };

const int dirX[5] = { 0, 0, -1, 1, 0 };
const int dirY[5] = { -1, 1, 0, 0, 0 };

class LightCell
{
public:
	LightCell();
	LightCell(const float dens, const array<float, 5> ratio);
	~LightCell();

	float lightDensity;

	float diffuseUp;
	float diffuseDown;
	float diffuseLeft;
	float diffuseRight;
	float diffuseMiddle;

	__forceinline void clear()
	{
		lightDensity = 0.0f;
		diffuseUp = 0.0f;
		diffuseDown = 0.0f;
		diffuseLeft = 0.0f;
		diffuseRight = 0.0f;
		diffuseMiddle = 0.0f;
	}

	void diffuse(const int x, const int y);
	inline void addData(const float dens, const float ratioUp, const float ratioDown, const float ratioLeft, const float ratioRight, const float ratioMiddle, const float mult);
	//__forceinline static int getXDir(int dir);
	//__forceinline static int getYDir(int dir);
};

