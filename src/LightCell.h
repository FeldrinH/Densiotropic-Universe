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
	LightCell(const float dens, const array<float, 5> ratio);
	~LightCell();

	float lightDensity;
	array<float, 5> diffuseRatio;

	void diffuse(const int x, const int y);
	inline void addData(const float dens, const array<float, 5> ratio, const float mult);
	//__forceinline static int getXDir(int dir);
	//__forceinline static int getYDir(int dir);
};

