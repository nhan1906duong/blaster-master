#pragma once
#include "Enemy.h"
#define JUMPER_WIDTH 17
#define JUMPER_HEIGHT 26
class Jumper: public Enemy
{
private:
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
public:
	Jumper();
};

