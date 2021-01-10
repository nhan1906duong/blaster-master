#include "Enemy.h"
#pragma once

#define STATE_VER	0
#define STATE_HOZ	1
#define STATE_FULL	2
#define TIME_CHANGE_STATE	500

#define CANNON_SIZE	26



class Cannon : public Enemy
{
private:
	ULONGLONG timeChangeState;
	bool isVerState;
	void FirerBullet(bool isVerState);
public:
	Cannon();
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
};

