#include "UniverseChunk.h"

UniverseChunk::UniverseChunk(int x, int y)
{
	cellMatrix = vector<vector<Cell>>(x, std::vector<Cell>(y));
}

UniverseChunk::~UniverseChunk()
{
}
