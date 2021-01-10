#include "MultiwarheadMissileItem.h"

MultiwarheadMissileItem::MultiwarheadMissileItem()
{
	animation_set = CAnimationSets::GetInstance()->Get(29);
}

void MultiwarheadMissileItem::Render()
{
	animation_set->at(0)->Render(x, y);
}

void MultiwarheadMissileItem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + HP_WIDTH;
	bottom = y - HP_HEIGHT;
}