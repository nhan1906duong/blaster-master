#include "Portal.h"


CPortal::CPortal(int identity, float l, float t, float r, float b, int scene_id, float cam_x, float cam_y)
{
	this->identity = identity;
	left = l;
	top = t;
	right = r;
	bottom = b;
	this->scene_id = scene_id;
	x = left;
	y = top;

	this->cam_x = cam_x;
	this->cam_y = cam_y;
}

void CPortal::Render()
{
	//RenderBoundingBox();
}

void CPortal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = left;
	t = top;
	r = right;
	b = bottom;
}