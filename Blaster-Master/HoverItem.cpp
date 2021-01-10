#include "HoverItem.h"

HoverItem::HoverItem()
{
	animation_set = CAnimationSets::GetInstance()->Get(27);
}

void HoverItem::Render()
{
	animation_set->at(0)->Render(x, y);
}

void HoverItem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + HP_WIDTH;
	bottom = y - HP_HEIGHT;
}