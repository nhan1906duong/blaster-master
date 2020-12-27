#pragma once
#include "Enemy.h"

#define SKULL_WIDTH				18
#define SKULL_HEIGHT			18
#define SKULL_NHA_DAN_HEIGHT	21

#define VX		0.08f
#define VY		0.07f

class Skull: public Enemy
{
private:
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
public:
	Skull();
};

