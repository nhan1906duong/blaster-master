#include "Skull.h"


Skull::Skull()
{
	animation_set = CAnimationSets::GetInstance()->Get(16);
}

void Skull::Render()
{
	animation_set->at(0)->Render(x, y);
}

void Skull::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void Skull::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + SKULL_WIDTH;
	bottom = y - SKULL_HEIGHT;
}