#pragma once
#include "Enemy.h"

#define BOMB_SIZE	10

#define VX_START_SPEED	0.03f
#define VX_GRAVITY	0.005f

#define VY_GRAVITY		-0.005f

#define S_MID	16.0f
#define S_END	10.0f

#define STATE_ROI	0
#define STATE_NAY	1

class Bomb: public Enemy
{
private:
	int time;
	float start_y;
	DWORD start_x = 0;
public:
	Bomb(int nx);
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
};

