#pragma once
#include "GameObject.h"
class CollisionExplosion: public CGameObject
{
private:
	int current;
	bool shouldRender;
	int times;
public:
	CollisionExplosion();
	void Render();
	void GetBoundingBox(float&, float&, float&, float&);
};

