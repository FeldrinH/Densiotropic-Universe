#pragma once

#include <cstdint>
#include <array>

using namespace std;

enum Direction {Up,Down,Left,Right, Middle};

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
	static int getXDir(int dir);
	static int getYDir(int dir);
	

	void draw(int x, int y);
};

