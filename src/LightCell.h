#pragma once

#include <cstdint>
#include <array>

using namespace std;

enum Direction {Up,Down,Right,Left, Middle};

class LightCell
{
public:
	LightCell();
	LightCell(float dens, array<float,5> ratio);
	~LightCell();

	float lightDensity;
	array<float, 5> diffuseRatio;

	void diffuse(int x, int y);
	void addData(float dens, array<float, 5> ratio, float mult);
	inline static int getXDir(int dir);
	inline static int getYDir(int dir);
	

	void draw(int x, int y);
};

