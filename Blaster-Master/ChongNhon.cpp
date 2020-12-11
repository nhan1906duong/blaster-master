#include "ChongNhon.h"

ChongNhon::ChongNhon(int identity, float left, float top, float right, float bottom)
{
	this->identity = identity;
	x = left;
	y = top;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}

ChongNhon::~ChongNhon()
{

}

void ChongNhon::Render()
{
	RenderBoundingBox();
}

void ChongNhon::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = left;
	t = top;
	r = right;
	b = bottom;
}
