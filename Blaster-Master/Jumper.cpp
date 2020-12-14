#include "Jumper.h"

Jumper::Jumper()
{

}

void Jumper::Render()
{
	animation_set->at(0)->Render(x, y);
}

void Jumper::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void Jumper::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + JUMPER_WIDTH;
	bottom = y - JUMPER_HEIGHT;
}