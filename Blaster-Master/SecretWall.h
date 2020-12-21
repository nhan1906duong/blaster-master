#pragma once
#include "GameObject.h"

class SecretWall : public CGameObject
{
private:
public:
	float left, top, right, bottom;

	SecretWall(float left, float top, float right, float bottom);
	~SecretWall();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();
};

