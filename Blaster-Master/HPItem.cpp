#include "HPItem.h"

#include "Player.h"

HPItem::HPItem()
{
	animation_set = CAnimationSets::GetInstance()->Get(20);
}

void HPItem::Render()
{
	animation_set->at(0)->Render(x, y);
}

void HPItem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + HP_WIDTH;
	bottom = y - HP_HEIGHT;
}

void HPItem::OnCollision()
{
	CPlayer::GetInstance()->OnGetHPItem();
}