#pragma once
#include "Enemy.h"

class Teleporter : public Enemy
{
private:

	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();

public:
	Teleporter();
};


