#include "Dome.h"

Dome::Dome()
{

}

void Dome::Render()
{
	animation_set->at(0)->Render(x, y);
}

void Dome::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void Dome::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + DOME_WIDTH;
	bottom = y - DOME_HEIGHT;
}