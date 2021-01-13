#pragma once
#include "Enemy.h"

#define EYEBALL_WIDTH 16
#define EYEBALL_HEIGHT 16

#define VMOVE		0.06f

#define TIME_NHA_DAN_AND_MOVE	2500
#define TIME_STOP_MOVE	1000
#define TIME_MOVE	350

class EyeBall : public Enemy
{
private:
	DWORD timeMoveAndFire;
	DWORD timeDelay;
	DWORD timeChangeVector;
	bool firstEntry = true;
	bool hasMove = false;
	float bouncingLeft, bouncingTop, bouncingRight, bouncingBottom;
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
	
public:
	EyeBall();
};

