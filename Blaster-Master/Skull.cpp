#include "Skull.h"

#include "Player.h"


Skull::Skull()
{
	vx = -VX;
	nx = -1;
	animation_set = CAnimationSets::GetInstance()->Get(16);
}

void Skull::Render()
{
	animation_set->at(0)->Render(x, y, 255, nx > 0);
}

void Skull::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt);

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
		float min_tx, min_ty, brickNx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, brickNx, ny, rdx, rdy);

		x += min_tx * dx + 0.01f * brickNx;
		y += min_ty * dy + 0.01f * ny;
	}

	float left, top, right, bottom;
	CPlayer::GetInstance()->GetBoundingBox(left, right, top, bottom);

	if (vx != 0 && x <= left + 5)
	{
		nx = -nx;
		vy = VY;
		vx = 0;
	}
}

void Skull::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + SKULL_WIDTH;
	bottom = y - SKULL_HEIGHT;
}