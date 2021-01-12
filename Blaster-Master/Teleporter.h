#pragma once
#include "Enemy.h"

#define TIME_MOVE_ANI 5000
#define TIME_FLICKER 2000
#define TIME_MOVE_GREEN 60
#define V_MOVE 0.1f
#define STATE_FLICKER 0
#define STATE_GREEN 1

#define TELPORTER_WIDTH 25
#define TELPORTER_HEIGHT 32

class Teleporter : public Enemy
{
private:
	bool firstEntry = true;
	bool hasMove = false, hasChangePosition = false;
	DWORD timeMove, timeFlicker, timeChangeGreen, timeChangeGreenAgain;
	ULONGLONG timeDelay = 1000;
	float tempX, tempY;
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();

public:
	Teleporter();
};


