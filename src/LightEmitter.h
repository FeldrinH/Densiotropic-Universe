#pragma once
#include <array>
using namespace std;

class LightEmitter
{
public:
	LightEmitter(int x, int y, float dens, array<float, 5> ratio);
	~LightEmitter();

	int x, y;
	float lightDensity;
	float lightMult;
	array<float, 5> diffuseRatio;
};

