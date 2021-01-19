#include "DotChanBoss.h"

#include "Boss.h"

DotChanBoss::DotChanBoss()
{
	animation_set = CAnimationSets::GetInstance()->Get(36);
}

void DotChanBoss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 18;
	bottom = y - 17;
}

void DotChanBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void DotChanBoss::Render()
{
	float bossX, bossY;
	Boss::GetInstance()->GetPosition(bossX, bossY);
	x = bossX + tempX;
	y = bossY + tempY;
	animation_set->at(0)->Render(x, y);
}