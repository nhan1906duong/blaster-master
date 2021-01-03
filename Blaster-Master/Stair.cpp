#include "Stair.h"


Stair::Stair(float left, float top, float right, float bottom, float jumpPoint)
{
	x = left;
	y = top;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->jumpPoint = jumpPoint;
}

Stair::~Stair()
{

}

void Stair::Render()
{
	RenderBoundingBox();
}

void Stair::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = left;
	t = top;
	r = right;
	b = bottom;
}
