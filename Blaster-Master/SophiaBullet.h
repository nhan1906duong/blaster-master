#pragma once
#include "PlayerBullet.h"

#define SOPHIA_BULLET_WIDTH		24
#define SOPHIA_BULLET_HEIGHT	8

#define V_SOPHIA_SPEED	0.2f

class SophiaBullet: public PlayerBullet
{
private:
	int direct;
public:
	SophiaBullet(int);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	void Render();
	void GetBoundingBox(float&, float&, float&, float&);
};

