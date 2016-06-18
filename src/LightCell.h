#pragma once

#include <cstdint>
#include <array>

using namespace std;

enum Direction { Up, Down, Right, Left, Middle };

const int dirX[5] = { 0, 0, 1, -1, 0 };
const int dirY[5] = { -1, 1, 0, 0, 0 };

class LightCell
{
public:
	LightCell();
	LightCell(float dens, array<float, 5> ratio);
	~LightCell();

	float lightDensity;
	array<float, 5> diffuseRatio;

	void diffuse(int x, int y);
	inline void addData(float dens, array<float, 5> ratio, float mult);
	//__forceinline static int getXDir(int dir);
	//__forceinline static int getYDir(int dir);
};

