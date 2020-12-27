#pragma once
#include "Enemy.h"

#define ORB_WIDTH	18
#define ORB_HEIGHT	18

#define STATE_WALKING	0
#define STATE_AROUND	1

class Orb: public Enemy
{
private:
public:
	Orb();
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Render();
};

