#pragma once
#include "Static.h"

class Stair: public Static
{
private:
public:
	float left, top, right, bottom;
	float jumpPoint;

	Stair(float left, float top, float right, float bottom, float jumpPoint);
	~Stair();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();

	float GetJumpPoint() { return jumpPoint; }
};

