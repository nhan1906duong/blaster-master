#pragma once
#include "Enemy.h"

#define INSECT_WIDTH	18
#define INSECT_HEIGHT	18

#define VY_SPEED	0.02f
#define VX_SPEED	0.01f

#define	STATE_FLY	0
#define	STATE_FALL	1

#define S_FALL	25.0f

class Insect: public Enemy
{
private:
	float bouncingLeft, bouncingTop, bouncingRight, bouncingBottom;
	float start_x, start_y;
	void _Random();
public:
	Insect(float l, float t, float r, float b, int nx, int ny);

	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
};

