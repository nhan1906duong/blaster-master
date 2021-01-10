#pragma once
#include "Enemy.h"

#define FLOATER_WIDTH 18
#define FLOATER_HEIGHT 18

#define PERIOD_BEETWEEN_SHOOT	3000

class Floater : public Enemy
{
private:
	ULONGLONG lastShoot = 0, timeDelay = 0;
	bool firstAppear;
public:
	Floater(int timeDelay);
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
};

