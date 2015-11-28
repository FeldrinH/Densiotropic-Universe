#pragma once

#include <cstdint>

class LightCell
{
public:
	LightCell();
	~LightCell();
	uint8_t lightDensity;
	uint8_t diffuseRatio[3][3];
};

