#pragma once
#include "Enemy.h"

#define SKULL_WIDTH				18
#define SKULL_HEIGHT			18
#define SKULL_NHA_DAN_HEIGHT	21

#define SKULL_VX		0.08f
#define SKULL_VY		0.07f

#define TIME_NHA_DAN	500

#define STATE_NORMAL	0
#define STATE_NHA_DAN	1

class Skull: public Enemy
{
private:
	ULONGLONG startNhaDan;
public:
	Skull(int nx);
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
};

