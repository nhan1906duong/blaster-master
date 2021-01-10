#include "ThunderBreakItem.h"

ThunderBreakItem::ThunderBreakItem()
{
	animation_set = CAnimationSets::GetInstance()->Get(28);
}

void ThunderBreakItem::Render()
{
	animation_set->at(0)->Render(x, y);
}

void ThunderBreakItem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + HP_WIDTH;
	bottom = y - HP_HEIGHT;
}