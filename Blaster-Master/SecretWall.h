#pragma once
#include "Static.h"

class SecretWall : public Static
{
private:
public:
	float left, top, right, bottom;

	SecretWall(float left, float top, float right, float bottom);
	~SecretWall();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();
};

