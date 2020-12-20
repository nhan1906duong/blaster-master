#include "Insect.h"

Insect::Insect()
{
	animation_set = CAnimationSets::GetInstance()->Get(14);
}

void Insect::Render()
{
	animation_set->at(0)->Render(x, y);
}

void Insect::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void Insect::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + INSECT_WIDTH;
	bottom = y - INSECT_HEIGHT;
}