#include "CangBoss.h"

#include "Boss.h"

CangBoss::CangBoss(int side)
{
	nx = side;
	animation_set = CAnimationSets::GetInstance()->Get(37);
	blood = 200;
}

void CangBoss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 18;
	bottom = y - 32;
}

void CangBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void CangBoss::Render()
{
	float bossX, bossY;
	Boss::GetInstance()->GetPosition(bossX, bossY);
	x = bossX + tempX;
	y = bossY + tempY;
	animation_set->at(0)->Render(x, y, 255, nx > 0);
}