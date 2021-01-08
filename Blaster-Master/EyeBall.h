#pragma once
#include "Enemy.h"

#define EYEBALL_WIDTH 18
#define EYEBALL_HEIGHT 9

#define VMOVE		0.09f

#define TIME_NHA_DAN_AND_MOVE	2000
#define TIME_STOP_MOVE	1000
#define TIME_MOVE	500

class EyeBall : public Enemy
{
private:
	DWORD timeMoveAndFire;
	DWORD timeDelay;
	bool firstEntry = true;
	bool startEnemies = false;
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
	
public:
	EyeBall();
};

