#pragma once
#include "Enemy.h"

#define ORB_WIDTH	18
#define ORB_HEIGHT	18

#define STATE_WALKING	0
#define STATE_AROUND	1

#define AROUND_TIME		200

#define DoomieOrb_VX	0.07f
#define DoomieOrb_VY 0.04f

class Orb: public Enemy
{
private:
public:
	Orb();
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Render();
};

