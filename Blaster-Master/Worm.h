#pragma once
#include "Enemy.h"

#define CONSAU_WIDTH 18
#define CONSAU_HEIGHT 9

#define ANIMATION_IDLE 0
#define ANIMATION_MOVE 1

#define STATE_MOVE		0
#define STATE_FALLING	1
#define STATE_JUMPING	2

#define MOVE_SPEED 0.05f

class Worm : public Enemy
{
	void SetState(int state);
public:
	Worm();
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
};

