#include "LightEmitter.h"

LightEmitter::LightEmitter(int x, int y, float dens, array<float, 5> ratio) : x(x), y(y)
{
	float ratioMult = 0;

	for (int a = 0; a < 5; a++)
	{
		ratioMult += ratio[a];
	}
	ratioMult = 1 / ratioMult;
	for (int a = 0; a < 5; a++)
	{
		ratio[a] = ratio[a] * ratioMult * dens;
	}

	lightDensity = dens;
	diffuseRatio = ratio;
}

LightEmitter::~LightEmitter()
{
}
