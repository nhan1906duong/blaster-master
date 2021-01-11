#pragma once
#include "Enemy.h"
class MineBomb: public Enemy
{
public:
	MineBomb();
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
};

