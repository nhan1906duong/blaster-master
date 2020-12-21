#pragma once
#include "GameObject.h"

class FireZone: public CGameObject
{
private:
public:
	float left, top, right, bottom;

	FireZone(float left, float top, float right, float bottom);
	~FireZone();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();
};

