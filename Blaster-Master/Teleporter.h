#pragma once
#include "Enemy.h"

#define TIME_MOVE_ANI 3000
#define TIME_FLICKER 1000
#define TIME_MOVE_GREEN 1000
#define V_MOVE 0.1f
#define STATE_FLICKER 0
#define STATE_GREEN 1

class Teleporter : public Enemy
{
private:
	bool firstEntry = true;
	bool hasMove = false;
	DWORD timeMove, timeFlicker, timeChangeGreen;
	ULONGLONG timeDelay = 1000;
	float tempX, tempY;
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();

public:
	Teleporter();
};


