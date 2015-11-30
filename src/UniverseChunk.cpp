#include "UniverseChunk.h"

UniverseChunk::UniverseChunk()
{
	lightMatrixBase = vector<vector<LightCell>>(0, std::vector<LightCell>(0));
	lightMatrixSuper = vector<vector<LightCell>>(0, std::vector<LightCell>(0));
}

UniverseChunk::UniverseChunk(int x, int y) : x(x), y(y)
{
	lightMatrixBase = vector<vector<LightCell>>(x, std::vector<LightCell>(y));
	lightMatrixSuper = vector<vector<LightCell>>(x, std::vector<LightCell>(y));
	//matterMatrix = vector<vector<MatterCell>>(x, std::vector<MatterCell>(y));
}

UniverseChunk::~UniverseChunk()
{
}
