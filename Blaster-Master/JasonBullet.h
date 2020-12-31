#pragma once
#include "PlayerBullet.h"

#define SIZE	4
#define V_SPEED		0.1f

class JasonBullet: public PlayerBullet
{
private:
	int nx;
public:
	JasonBullet(int nx);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	void Render();
	void GetBoundingBox(float&, float&, float&, float&);
};

