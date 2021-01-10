#include "Enemy.h"
#pragma once

#define STATE_VER	0
#define STATE_HOZ	1
#define STATE_FULL	2
#define TIME_CHANGE_STATE	500
#define LOCATION_CANNON_X	160.0f
#define LOCATION_CANNON_Y	278.0f

#define CANNON_SIZE	26



class Cannon : public Enemy
{
private:
	DWORD timeChangeState;
	bool isVerState;
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();

public:
	Cannon();
};

