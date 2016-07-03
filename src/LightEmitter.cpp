#include "LightEmitter.h"

LightEmitter::LightEmitter(float dens, array<float, 5> ratio) : lightDensity(dens), fullPhase(true), phase(false), originalPhase(false)
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
	
	diffuseRatio = ratio;
}

LightEmitter::LightEmitter(float dens, array<float, 5> ratio, bool phase) : lightDensity(dens), fullPhase(false), phase(phase), originalPhase(phase)
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

	diffuseRatio = ratio;
}

void LightEmitter::emit(bool curPhase)
{
	if (fullPhase || phase == curPhase)
	{
		Universe.lightMatrixBase[x][y].addData(lightDensity, diffuseRatio[0], diffuseRatio[1], diffuseRatio[2], diffuseRatio[3], diffuseRatio[4], 1.0f);
	}
}
