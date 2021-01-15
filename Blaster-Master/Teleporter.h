#pragma once
#include "Enemy.h"

#define TIME_MOVE_ANI 5000
#define TIME_FLICKER 800
#define TIME_MOVE_GREEN 50
#define V_MOVE 0.1f
#define STATE_FLICKER 0
#define STATE_GREEN 1

#define TELEPORTER_WIDTH 25
#define TELEPORTER_HEIGHT 32

class Teleporter : public Enemy
{
private:
	bool firstEntry = true, startEnemy = false;
	bool hasMove = false, hasChangePosition = false;
	DWORD timeMove, timeFlicker, timeChangeGreen, timeChangeGreenAgain;
	ULONGLONG timeDelay = 1000;
	float tempX, tempY, xNew, yNew;
	float bouncingLeft, bouncingTop, bouncingRight, bouncingBottom;
	float leftStartEnemy, topStartEnemy, rightStartEnemy, bottomStartEnemy;
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
	virtual bool PlayerComming();

public:
	Teleporter(float l, float t, float r, float b, float leftStartEnemy, float topStartEnemy, float rightStartEnemy, float bottomStartEnemy);
};


