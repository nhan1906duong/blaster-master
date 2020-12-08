#include "Portal.h"


CPortal::CPortal(int identity, float l, float t, float r, float b, int scene_id)
{
	this->identity = identity;
	left = l;
	top = t;
	right = r;
	bottom = b;
	this->scene_id = scene_id;
	x = left;
	y = top;
}

void CPortal::Render()
{
	RenderBoundingBox();
}

void CPortal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = left;
	t = top;
	r = right;
	b = bottom;
}