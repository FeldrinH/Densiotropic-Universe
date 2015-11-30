#include "LightCell.h"
#include "UniverseChunk.h"

LightCell::LightCell()
{
}

LightCell::~LightCell()
{
}

void LightCell::diffuse(int x, int y)
{
	/*float ratioMult = 0;
	for (int a = 0; a < 5; a++)
	{
		ratioMult += diffuseRatio[a];
	}
	for (int a = 0; a < 5; a++)
	{
		diffuseRatio[a] = diffuseRatio[a]*ratioMult;
	}*/
	if (lightDensity == 0.0F)
	{
		return;
	}

	float ratioMult = 1 / lightDensity;
	
	for (int i = 0; i < 5; i++)
	{
		Universe.lightMatrixSuper[x + getXDir(i)][y + getYDir(i)].addDensity(diffuseRatio[i]);
		Universe.lightMatrixSuper[x + getXDir(i)][y + getYDir(i)].addRatio(diffuseRatio, diffuseRatio[i] * ratioMult);
	}

	lightDensity = 0.0F;
	std::fill_n(diffuseRatio, 5, 0.0F);
}

int LightCell::getXDir(int dir)
{
	return dir == Left ? -1 : dir == Right ? 1 : 0;
}

int LightCell::getYDir(int dir)
{
	return dir == Up ? -1 : dir == Down ? 1 : 0;
}
