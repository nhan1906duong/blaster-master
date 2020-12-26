#pragma once
#include "Grid.h"

class GridManager
{
private:
	GridManager();

	static GridManager* __instance;
	vector<vector<Grid*>> grids;

	vector<LPGAMEOBJECT> objects;

	int round(int num, int other);

	void _AddToGrid(LPGAMEOBJECT object);
public:
	static GridManager* GetInstance();

	void Clear();
	void Reset();

	void AddObject(LPGAMEOBJECT object);
	vector<LPGAMEOBJECT> GetObjectsToUpdate();
};

