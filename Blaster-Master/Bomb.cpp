#include "Bomb.h"

#include "Area2Scene.h"

Bomb::Bomb(int nx)
{
	SetState(STATE_ROI);
	time = 0;
	this->nx = nx;
	if (nx < 0)
	{
		vx = -VX_START_SPEED;
	}
	else
	{
		vx = VX_START_SPEED;
	}
	vy = 0;
	blood = 4;
	animation_set = CAnimationSets::GetInstance()->Get(22);
}

void Bomb::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BOMB_SIZE;
	bottom = y - BOMB_SIZE;
}

void Bomb::Render()
{
	animation_set->at(beenShot ? 1 : 0)->Render(x, y);
}

void Bomb::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == STATE_NAY && (time == 1 && y - start_y >= S_MID || time == 2 && y - start_y >= S_END))
	{
		SetState(STATE_ROI);
		vy = 0;
	}

	if (state == STATE_ROI)
	{
		vy += VY_GRAVITY;
	}
	else
	{
		vy -= VY_GRAVITY;
	}
	Enemy::Update(dt, coObjects);

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
			nx = -nx;
			vx = -vx;
		}

		if (ny == 1)
		{
			vy = 0;
			if (time < 2)
			{
				start_y = y;
				SetState(STATE_NAY);
				++time;
			}
		}
	}

	if (time == 2 && vy == 0 && state == STATE_ROI)
	{
		if (start_x == 0)
		{
			start_x = GetTickCount();
		}
		if (GetTickCount() - start_x > 1500)
		{
			PrepareToRemove();
			((Area2Scene*)CGame::GetInstance()->GetCurrentScene())->AddCollision(x, y + 12);
		}
	}
}