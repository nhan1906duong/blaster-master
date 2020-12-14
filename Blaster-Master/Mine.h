#pragma once
#include "Enemy.h"

#define MINE_WIDTH	16
#define MINE_HEIGHT	10

class Mine: public Enemy
{
private:
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
public:
	Mine();
};

