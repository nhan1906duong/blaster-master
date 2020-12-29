#pragma once
#include "Enemy.h"

#define FLOATER_WIDTH 18
#define FLOATER_HEIGHT 18

#define PERIOD_BEETWEEN_SHOOT	3000

class Floater : public Enemy
{
private:
	DWORD lastShoot;
	bool firstAppear;
	int timeDelay;
public:
	Floater(int timeDelay);
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
};

