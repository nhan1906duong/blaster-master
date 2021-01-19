#pragma once
#include "Enemy.h"

class DotChanBoss: public Enemy
{
private:
	float tempX, tempY;
public:
	DotChanBoss();
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
	void SetTemp(float x, float y)
	{
		tempX = x;
		tempY = y;
	}
};

