#include "HomingMissileItem.h"

HomingMissileItem::HomingMissileItem()
{
	animation_set = CAnimationSets::GetInstance()->Get(31);
}

void HomingMissileItem::Render()
{
	animation_set->at(0)->Render(x, y);
}

void HomingMissileItem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + HP_WIDTH;
	bottom = y - HP_HEIGHT;
}