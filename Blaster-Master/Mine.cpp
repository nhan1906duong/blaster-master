#include "Mine.h"


Mine::Mine()
{
	animation_set = CAnimationSets::GetInstance()->Get(17);
}

void Mine::Render()
{
	animation_set->at(0)->Render(x, y);
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
