#pragma once

#include "Item.h"
#include "EnemyBullet.h"

#define BULLET_SIZE	9
#define V_SPEED	0.08f

class EyeBallBullet : public EnemyBullet
{
public:
	EyeBallBullet(float deltaX, float deltaY);
	void Render();
	void GetBoundingBox(float&, float&, float&, float&);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
};



