#pragma once
#include "GameObject.h"
#define TIME_DELAY_COLLISION	400

class CollisionExplosion: public CGameObject
{
private:
	int current;
	bool shouldRender;
	int times;
	int typeCollisioExplosion;
	DWORD timeDelay;
public:
	CollisionExplosion(int typeCollisioExplosion);
	void Render();
	void GetBoundingBox(float&, float&, float&, float&);
};

