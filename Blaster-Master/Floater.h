#pragma once
#include "Enemy.h"

#define FLOATER_WIDTH 18
#define FLOATER_HEIGHT 18

class Floater : public Enemy
{
private:
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
public:
	Floater();
};

