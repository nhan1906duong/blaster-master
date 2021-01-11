#include "EyeBallBullet.h"
#include "Player.h"
#include "Brick.h"
#include "Game.h"
#include "Area2OverworldScene.h"


EyeBallBullet::EyeBallBullet(float deltaX, float deltaY)
{
	animation_set = CAnimationSets::GetInstance()->Get(24);
	if (deltaX == 0)
	{
		if (deltaY < 0)
		{
			vy = V_SPEED;
		}
		else
		{
			vy = -V_SPEED;
		}
	}

	if (deltaY == 0)
	{
		if (deltaX < 0)
		{
			vx = V_SPEED;
		}
		else
		{
			vx = -V_SPEED;
		}
	}

	int ny;
	if (deltaY < 0)
	{
		ny = 1;
	}
	else
	{
		ny = -1;
	}

	if (deltaX < 0)
	{
		nx = 1;
	}
	else
	{
		nx = -1;
	}

	float ratio = deltaX * nx / deltaY * ny;

	if (ratio < 0)
	{
		vx = nx * V_SPEED;
		vy = V_SPEED / ratio * ny;
	}
	else
	{
		vx = V_SPEED * ratio * nx;
		vy = ny * V_SPEED;
	}

	power = 1;
}

void EyeBallBullet::Render()
{
	animation_set->at(0)->Render(x, y);
}

void EyeBallBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BULLET_SIZE;
	bottom = y - BULLET_SIZE;
}
void EyeBallBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	Bullet::Update(dt, coObjects);

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
		float deltaMin = 9999;
		LPCOLLISIONEVENT minEvent = NULL;

		for (UINT i = 0; i < coEvents.size(); i++)
		{
			LPCOLLISIONEVENT e = coEvents[i];
			if (!dynamic_cast<CPlayer*>(e->obj) &&
				!dynamic_cast<CBrick*>(e->obj))
				continue;

			float min = e->dx < e->dy ? e->dx : e->dy;
			if (min < deltaMin)
			{
				minEvent = e;
				deltaMin = min;
			}
		}
		if (deltaMin >= 9999)
		{
			x += dx;
			y += dy;
		}
		else
		{

			if (minEvent)
			{
				if (dynamic_cast<CPlayer*>(minEvent->obj))
				{
					CPlayer::GetInstance()->StartUntouchable();
				}
				PrepareToRemove();
				float left, top, right, bottom;
				minEvent->obj->GetBoundingBox(left, top, right, bottom);
				x += minEvent->t * dx + minEvent->nx * 0.1f;
				y += minEvent->t * dy + minEvent->ny * 0.1f;
				((Area2OverworldScene*)CGame::GetInstance()->GetCurrentScene())->AddCollision(x, y);
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


