#pragma once
#include "GameObject.h"
class Grid
{
private:
	vector<LPGAMEOBJECT> objects;
public:
	Grid();
	void AddObject(LPGAMEOBJECT object);
	void RemoveObject(LPGAMEOBJECT object);

	vector<LPGAMEOBJECT> GetObjects() { return objects; };
	void ClearObjects();
};

