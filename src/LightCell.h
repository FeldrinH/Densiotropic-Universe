#pragma once

#include <cstdint>

enum Direction {Up,Down,Middle,Left,Right};

class LightCell
{
public:
	LightCell();
	~LightCell();
	float lightDensity;
	float diffuseRatio[5];

	void diffuse(int x, int y);
	static int getXDir(int dir);
	static int getYDir(int dir);

	void addDensity(float dens);
	void addRatio(float ratio[5], float mult);
};

