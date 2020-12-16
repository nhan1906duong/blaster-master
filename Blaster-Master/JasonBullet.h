#pragma once
#include "Bullet.h"

class JasonBullet: public Bullet
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	void Render();
	void GetBoundingBox(float&, float&, float&, float&);
};

