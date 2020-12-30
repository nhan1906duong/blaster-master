#include "Orb.h"

Orb::Orb()
{
	blood = 4;
	animation_set = CAnimationSets::GetInstance()->Get(15);
}

void Orb::Render()
{
	int ani;
	bool flip = false;
	if (state == STATE_WALKING)
	{
		ani = 2;
		flip = nx > 0;
	}
	else
	{
		ani = 0;
	}
	animation_set->at(beenShot ? ani + 1 : ani)->Render(x, y, 255, flip);
}

void Orb::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ORB_WIDTH;
	bottom = y - ORB_HEIGHT;
}