#pragma once
#include <array>
#include "Main.h"
using namespace std;

class LightEmitter
{
public:
	LightEmitter(float dens, array<float, 5> ratio);

	int x, y;
	float lightDensity;
	float lightMult;
	array<float, 5> diffuseRatio;

	void emit()
	{
		Universe.lightMatrixBase[x][y].addData(lightDensity, diffuseRatio, 1.0f);
	}
};

