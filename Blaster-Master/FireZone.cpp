#include "FireZone.h"

FireZone::FireZone(float left, float top, float right, float bottom)
{
	x = left;
	y = top;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}

FireZone::~FireZone()
{

}

void FireZone::Render()
{
	//RenderBoundingBox();
}

void FireZone::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = left;
	t = top;
	r = right;
	b = bottom;
}
