#pragma once
#include "Enemy.h"

#define INSECT_WIDTH	18
#define INSECT_HEIGHT	18

class Insect: public Enemy
{
private:
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
public:
	Insect();
};
