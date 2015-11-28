#include "UniverseChunk.h"

UniverseChunk::UniverseChunk(int x, int y)
{
	lightMatrix1 = vector<vector<LightCell>>(x, std::vector<LightCell>(y));
	lightMatrix2 = vector<vector<LightCell>>(x, std::vector<LightCell>(y));
	matterMatrix = vector<vector<MatterCell>>(x, std::vector<MatterCell>(y));
}

UniverseChunk::~UniverseChunk()
{
}
