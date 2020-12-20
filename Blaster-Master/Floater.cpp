#include "Floater.h"

Floater::Floater()
{
	animation_set = CAnimationSets::GetInstance()->Get(12);
}

void Floater::Render()
{
	animation_set->at(0)->Render(x, y);
}

void Floater::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void Floater::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FLOATER_WIDTH;
	bottom = y - FLOATER_HEIGHT;
}