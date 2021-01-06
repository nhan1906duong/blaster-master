#include "EyeBall.h"
#include "Player.h"
#include "FloaterBullet.h"

EyeBall::EyeBall()
{
	animation_set = CAnimationSets::GetInstance()->Get(23);
}


void EyeBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + EYEBALL_WIDTH;
	bottom = y - EYEBALL_HEIGHT;
}

void EyeBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		// Va cham
	}

	Enemy::Update(dt, coObjects);

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void EyeBall::Render()
{
	animation_set->at(0)->Render(x, y, 255, nx > 0);
}