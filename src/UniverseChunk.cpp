#include "UniverseChunk.h"

UniverseChunk::UniverseChunk(int x, int y)
{
	lightMatrixBase = vector<vector<LightCell>>(x, std::vector<LightCell>(y));
	lightMatrixSuper = vector<vector<LightCell>>(x, std::vector<LightCell>(y));
	//matterMatrix = vector<vector<MatterCell>>(x, std::vector<MatterCell>(y));
}

UniverseChunk::~UniverseChunk()
{
}
