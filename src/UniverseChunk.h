#pragma once

#include "LightCell.h"
#include "MatterCell.h"
#include <vector>

using namespace std;

extern UniverseChunk Universe;

class UniverseChunk
{
public:
	UniverseChunk(int x, int y);
	~UniverseChunk();
	//vector<vector<MatterCell>> matterMatrix;
	vector<vector<LightCell>> lightMatrixBase;
	vector<vector<LightCell>> lightMatrixSuper;
};

