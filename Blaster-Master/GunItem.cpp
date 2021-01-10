#include "GunItem.h"

GunItem::GunItem()
{
	animation_set = CAnimationSets::GetInstance()->Get(30);
}

void GunItem::Render()
{
	animation_set->at(0)->Render(x, y);
}

void GunItem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + HP_WIDTH;
	bottom = y - HP_HEIGHT;
}