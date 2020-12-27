#pragma once
#include "Enemy.h"


#include "Brick.h"

#define JUMPER_WIDTH 17
#define JUMPER_HEIGHT 26

#define STATE_WALKING	0
#define STATE_JUMPING	1
#define STATE_FALLING	2

#define VX	0.05f

class Jumper: public Enemy
{
private:
	CBrick* currentBrick;
public:
	Jumper();
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
};

