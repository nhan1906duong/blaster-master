#pragma once
#include "Enemy.h"

#define MINE_WIDTH	14
#define MINE_HEIGHT	8

class Mine: public Enemy
{
public:
	Mine();
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
	void PrepareToRemove();
};

