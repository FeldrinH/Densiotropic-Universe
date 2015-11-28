#pragma once

#include "LightCell.h"
#include "MatterCell.h"
#include <vector>

using namespace std;

class UniverseChunk
{
public:
	UniverseChunk(int x, int y);
	~UniverseChunk();
	vector<vector<MatterCell>> matterMatrix;
	vector<vector<LightCell>> lightMatrix1;
	vector<vector<LightCell>> lightMatrix2;
};

