#pragma once
#include "Enemy.h"

#define DOME_WIDTH 18
#define DOME_HEIGHT 18

// 2 vien dan moi die
class Dome : public Enemy
{
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
public:
	Dome();
};

