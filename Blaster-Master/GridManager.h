#pragma once
#include "Grid.h"

class GridManager
{
private:
	GridManager();

	static GridManager* __instance;
	vector<vector<Grid*>> grids;
public:
	static GridManager* GetInstance();
};

