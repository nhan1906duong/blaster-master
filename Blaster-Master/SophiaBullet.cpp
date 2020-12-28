#include "SophiaBullet.h"

#include "Enemy.h"
#include "Brick.h"
#include "Portal.h"
#include "SecretWall.h"
#include "Area2Scene.h"

/** direct	1	LeftToRight
*			2	RightToLeft
*			3	BottomToTop
*/
SophiaBullet::SophiaBullet(int direct)
{
	power = 2;
	this->direct = direct;
	if (direct == 1)
	{
		vx = V_SPEED;
	}
	else if (direct == 2)
	{
		vx = -V_SPEED;
	}
	else
	{
		vy = V_SPEED;
	}
	animation_set = CAnimationSets::GetInstance()->Get(18);
}

void SophiaBullet::Render()
{
	int ani;
	if (direct == 3)
	{
		ani = 1;
	} 
	else
	{
		ani = 0;
	}
	animation_set->at(ani)->Render(x, y, 255, direct == 1);
	RenderBoundingBox();
}

void SophiaBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	if (direct == 3)
	{
		right = x + SOPHIA_BULLET_HEIGHT;
		bottom = y - SOPHIA_BULLET_WIDTH;
	}
	else
	{
		right = x + SOPHIA_BULLET_WIDTH;
		bottom = y - SOPHIA_BULLET_HEIGHT;
	}
}

void SophiaBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
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
			float min = e->dx < e->dy ? e->dx : e->dy;
			if (min < deltaMin)
			{
				minEvent = e;
				deltaMin = min;
			}
		}
		if (deltaMin >= 9999) return;
		if (minEvent)
		{
			if (dynamic_cast<Enemy*>(minEvent->obj))
			{
				Enemy* enemy = dynamic_cast<Enemy*>(minEvent->obj);
				enemy->BeenShot(this);
			}
			PrepareToRemove();
			float left, top, right, bottom;
			minEvent->obj->GetBoundingBox(left, top, right, bottom);
			if (direct == 1)
			{
				x = left;
			}
			else if (direct == 2)
			{
				x = right;
			}
			else if (direct == 3)
			{
				y = bottom;
			}
			((CArea2Scene*)CGame::GetInstance()->GetCurrentScene())->AddCollision(x, y);
		}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
}