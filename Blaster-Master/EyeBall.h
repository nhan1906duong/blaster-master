#pragma once
#include "Enemy.h"

#define EYEBALL_WIDTH 18
#define EYEBALL_HEIGHT 9

#define VX		0.08f
#define VY		0.07f

#define TIME_NHA_DAN_AND_MOVE	3000

class EyeBall : public Enemy
{
private:
	DWORD startNhaDan;
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
	
public:
	EyeBall();
};

