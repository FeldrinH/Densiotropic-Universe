#pragma once

#include <array>
#include <vector>
#include "Main.h"
#include "LightCell.h"

using namespace std;

class LightEmitter
{
public:
	LightEmitter(float dens, array<float, 5> ratio);
	LightEmitter(float dens, array<float, 5> ratio, bool phase);

	int x, y;
	float lightDensity;
	float lightMult;
	array<float, 5> diffuseRatio;
	bool fullPhase;
	bool phase;
	bool originalPhase;

	void emit(bool curPhase, vector<vector<LightCell>>& lightMatrix);
};

