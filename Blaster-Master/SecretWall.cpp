#include "SecretWall.h"

SecretWall::SecretWall(float left, float top, float right, float bottom)
{
	x = left;
	y = top;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}

SecretWall::~SecretWall()
{

}

void SecretWall::Render()
{
	RenderBoundingBox();
}

void SecretWall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = left;
	t = top;
	r = right;
	b = bottom;
}
