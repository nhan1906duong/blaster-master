#pragma once
#include "Static.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public Static
{
private:
	int identity;
	float left;
	float top;
	float right;
	float bottom;
public:
	CBrick(int identity, float left, float top, float right, float bottom);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};