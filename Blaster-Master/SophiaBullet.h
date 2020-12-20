#pragma once
#include "Bullet.h"

#define SOPHIA_BULLET_WIDTH		24
#define SOPHIA_BULLET_HEIGHT	8

#define V_SPEED	0.12f

class SophiaBullet: public Bullet
{
private:
	int direct;
public:
	SophiaBullet(int);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	void Render();
	void GetBoundingBox(float&, float&, float&, float&);
};

