#pragma once
class LightEmitter
{
public:
	LightEmitter();
	LightEmitter(int x, int y)
	~LightEmitter();

	int x, y;
	float lightDensity;
	float lightMult;
	array<float, 5> diffuseRatio;
};

