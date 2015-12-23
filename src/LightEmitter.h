#pragma once
#include <array>
#include "Main.h"
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

	void emit(bool curPhase);
};

