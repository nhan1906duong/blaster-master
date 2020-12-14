#include "Mine.h"


Mine::Mine()
{

}

void Mine::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void Mine::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void Mine::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + MINE_WIDTH;
	bottom = y - MINE_HEIGHT;
}
