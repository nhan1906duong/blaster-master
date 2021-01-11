#pragma once
#include "PlayerBullet.h"

#define SIZE	4
#define V_JASON_SPEED		0.25f

class JasonBullet: public PlayerBullet
{
private:
	int nx;
	float start_X = -1.0f;
public:
	JasonBullet(int nx);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	void Render();
	void GetBoundingBox(float&, float&, float&, float&);
};

