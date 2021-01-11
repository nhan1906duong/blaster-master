#include "MineBomb.h"

#include "GameDefine.h"

MineBomb::MineBomb()
{
	animation_set = CAnimationSets::GetInstance()->Get(24);
	SetVy(0.1);
}

void MineBomb::Render()
{
	animation_set->at(0)->Render(x, y);
}

void MineBomb::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	vy += GameDefine::ACCELERATOR_GRAVITY;
	CGameObject::Update(dt);
	x += dx;
	y += dy;
}

void MineBomb::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 9;
	bottom = y - 9;
}