#include "CangBoss.h"

CangBoss::CangBoss()
{
	animation_set = CAnimationSets::GetInstance()->Get(37);
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
	animation_set->at(0)->Render(x, y);
}