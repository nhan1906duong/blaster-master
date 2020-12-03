#include "Brick.h"

CBrick::CBrick(int identity, float left, float top, float right, float bottom)
{
	this->identity = identity;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	x = left;
	y = top;
}

void CBrick::Render()
{
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = left;
	t = top;
	r = right;
	b = bottom;
}