#include "Orb.h"

Orb::Orb()
{
	animation_set = CAnimationSets::GetInstance()->Get(15);
}

void Orb::Render()
{
	animation_set->at(0)->Render(x, y);
}

void Orb::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void Orb::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ORB_WIDTH;
	bottom = y - ORB_HEIGHT;
}