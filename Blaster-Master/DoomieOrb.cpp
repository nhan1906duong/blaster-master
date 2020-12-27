#include "DoomieOrb.h"

#include "GameDefine.h"

DoomieOrb::DoomieOrb()
{
	SetState(STATE_WALKING);
	vx = -VX;
	nx = -1;
}

void DoomieOrb::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

		if (brickNx != 0)
		{
			vx = -vx;
			nx = -nx;
		}
	}

	if (STATE_AROUND == state && GetTickCount() - startTime < AROUND_TIME)
	{
		return;
	}

	int randomState = rand() % 100;
	if (randomState > 97)
	{
		startTime = GetTickCount();
		state = STATE_AROUND;
		vy = -VY;
	}
	else if (randomState > 95)
	{
		startTime = GetTickCount();
		state = STATE_AROUND;
		vy = VY;
	}
	else
	{
		state = STATE_WALKING;
		vy = 0;
	}
}