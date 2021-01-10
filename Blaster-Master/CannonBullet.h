#pragma once

#include "EnemyBullet.h"

#define BULLET_SIZE	9
#define VBULLTET	0.3f

class CannonBullet : public EnemyBullet
{
public:
	bool isVerState;
	float VectorBullter;
	CannonBullet();
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	void GetBoundingBox(float&, float&, float&, float&);
};

