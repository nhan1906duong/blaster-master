#pragma once
#include "Bullet.h"

#define SIZE	4
#define VX		0.1f

class JasonBullet: public Bullet
{
private:
	int nx;
public:
	JasonBullet(int nx);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	void Render();
	void GetBoundingBox(float&, float&, float&, float&);
};

