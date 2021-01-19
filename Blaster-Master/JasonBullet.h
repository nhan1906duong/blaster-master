#pragma once
#include "PlayerBullet.h"

#define SIZE	4
#define V_JASON_SPEED		0.25f
#define V_JASON_SPEED_OVERWORLD		0.5f
#define DISTANCE_BOMB		50

class JasonBullet: public PlayerBullet
{
private:
	int type = 0; // 0: Bullet Area
				  //1: Overworld 2 DIK_X
				  //2: Overworld 2 DIK_Z
	int nx;
	int ny;
	float start_X = -1.0f;
	float start_Y = -1.0f;
public:
	JasonBullet(int nx, int type);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	void Render();
	void GetBoundingBox(float&, float&, float&, float&);
	int GetAniBullet();
};

