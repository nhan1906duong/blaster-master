#pragma once
#include "Enemy.h"

#define ORB_WIDTH	18
#define ORB_HEIGHT	18

class Orb: public Enemy
{
private:
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
public:
	Orb();
};

