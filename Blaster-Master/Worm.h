#pragma once
#include "Enemy.h"

#define CONSAU_WIDTH 18
#define CONSAU_HEIGHT 10

#define ANIMATION_IDLE 0
#define ANIMATION_MOVE 1

#define STATE_FALL 0
#define STATE_MOVE 1

#define MOVE_SPEED 0.05f

class Worm : public Enemy
{
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
public:
	Worm();
};

