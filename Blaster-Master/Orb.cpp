#include "Orb.h"

Orb::Orb()
{
	animation_set = CAnimationSets::GetInstance()->Get(15);
}

void Orb::Render()
{
	int ani;
	bool flip = false;
	if (state == STATE_WALKING)
	{
		ani = 1;
		flip = nx > 0;
	}
	else
	{
		ani = 0;
	}
	animation_set->at(ani)->Render(x, y, 255, flip);
}

void Orb::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ORB_WIDTH;
	bottom = y - ORB_HEIGHT;
}