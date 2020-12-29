#pragma once
#include "EnemyBullet.h"

#define V_SPEED	0.07f

class FloaterBullet: public EnemyBullet
{
public:
	FloaterBullet(float deltaX, float deltaY);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	void Render();
	void GetBoundingBox(float&, float&, float&, float&);
};

