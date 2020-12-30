#include "Insect.h"

#include "Brick.h"

Insect::Insect(float l, float t, float r, float b, int nx, int ny)
{
	blood = 4;

	bouncingLeft = l;
	bouncingTop = t;
	bouncingRight = r;
	bouncingBottom = b;
	
	if (nx < 0)
	{
		vx = -VX_SPEED;
		nx = -1;
	}
	else
	{
		vx = VX_SPEED;
		nx = 1;
	}

	if (ny < 0)
	{
		vy = -VY_SPEED;
	}
	else
	{
		vy = VY_SPEED;
	}

	SetState(STATE_FLY);

	animation_set = CAnimationSets::GetInstance()->Get(14);
}

void Insect::Render()
{
	animation_set->at(beenShot ? 1 : 0)->Render(x, y, 255, nx > 0);
}

void Insect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	Enemy::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		if (state == STATE_FALL && (vy < 0 && (start_y - y > S_FALL) || vy > 0 && y - start_y > S_FALL))
		{
			SetState(STATE_FLY);
			if (vy < 0)
			{
				vy = VY_SPEED;
			}
			else
			{
				vy = -VY_SPEED;
			}
		}
		else
		{
			_Random();
		}
	}
	else
	{
		float min_tx, min_ty, brickNx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, brickNx, ny, rdx, rdy);

		x += min_tx * dx + brickNx * 0.1f;
		y += min_ty * dy + ny * 0.1f;

		if (nx != 0)
		{
			vx = -vx;
			nx = -nx;
		}

		if (ny == 1)
		{

			vy = VY_SPEED;
			if (state == STATE_FALL)
			{
				SetState(STATE_FLY);
			}
		}
		else
		{
			if (ny == -1)
			{
				if (state == STATE_FALL)
				{
					SetState(STATE_FLY);
				}
				vy = -VY_SPEED;
			}
			_Random();
		}
	}
	if (x < bouncingLeft)
	{
		nx = 1;
		vx = VX_SPEED;
	}
	if (x > bouncingRight)
	{
		nx = -1;
		vx = -VX_SPEED;
	}
	if (y > bouncingTop)
	{
		vy = -VY_SPEED;
	}
	if (y < bouncingBottom)
	{
		vy = VY_SPEED;
	}
}

void Insect::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + INSECT_WIDTH;
	bottom = y - INSECT_HEIGHT;
}

void Insect::_Random()
{
	int randomState = rand() % 100;
	if (randomState > 97)
	{
		if (state == STATE_FALL) return;
		SetState(STATE_FALL);
		vy = -7 * VY_SPEED;
		start_x = x;
		start_y = y;
	}
	else if (randomState > 94)
	{
		if (state == STATE_FALL) return;
		SetState(STATE_FALL);
		vy = 7 * VY_SPEED;
		start_x = x;
		start_y = y;
	}
	else if (randomState > 87)
	{
		if (state == STATE_FLY)
		{
			vy = VY_SPEED;
		}
	}
	else if (randomState > 85)
	{
		if (state == STATE_FLY)
		{
			vy = -VY_SPEED;
		}
	}
	else if (randomState < 1)
	{
		vx = -vx;
		nx = -nx;
	}
}