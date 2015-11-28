#pragma once

#include "Cell.h"
#include <vector>

using namespace std;

class UniverseChunk
{
public:
	UniverseChunk(int x, int y);
	~UniverseChunk();
	vector<vector<Cell>> cellMatrix;
};

