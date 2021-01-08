#pragma once

#include "Item.h"
#include "EnemyBullet.h"

#define BULLET_SIZE	9

class EyeBallBullet : public EnemyBullet
{
public:
	EyeBallBullet();
	void Render();
	void GetBoundingBox(float&, float&, float&, float&);
};



