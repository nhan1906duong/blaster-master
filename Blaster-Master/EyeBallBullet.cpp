#include "EyeBallBullet.h"

EyeBallBullet::EyeBallBullet()
{
	animation_set = CAnimationSets::GetInstance()->Get(24);
}

void EyeBallBullet::Render()
{
	animation_set->at(0)->Render(x, y);
}

void EyeBallBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BULLET_SIZE;
	bottom = y - BULLET_SIZE;
}

