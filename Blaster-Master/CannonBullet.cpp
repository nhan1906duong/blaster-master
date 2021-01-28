#include "CannonBullet.h"

#include "Player.h"
#include "Brick.h"
#include "Bomb.h"
#include "Area2OverworldScene.h"
#include "Game.h"

CannonBullet::CannonBullet(int type)
{
	switch (type)
	{
	case 1:
		VectorBullter = VBULLTET;
		isVerState = true;
		break;
	case 2:
		VectorBullter = -VBULLTET;
		isVerState = true;
		break;
	case 3:
		VectorBullter = VBULLTET;
		isVerState = false;
		break;
	case 4:
		VectorBullter = -VBULLTET;
		isVerState = false;
		break;
	}
	animation_set = CAnimationSets::GetInstance()->Get(24);
}

void CannonBullet::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CannonBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isVerState) {
		SetVx(0.0f);
		SetVy(VectorBullter);
	}
	else {
		SetVy(0.0f);
		SetVx(VectorBullter);
	}

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

void CannonBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BULLET_SIZE;
	bottom = y - BULLET_SIZE;
}
