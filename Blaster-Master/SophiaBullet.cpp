#include "SophiaBullet.h"

#include "Enemy.h"
#include "Brick.h"
#include "Portal.h"
#include "SecretWall.h"
#include "Area2Scene.h"

#include "Mine.h"

#include "EnemyBullet.h"

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
		vx = V_SOPHIA_SPEED;
	}
	else if (direct == 2)
	{
		vx = -V_SOPHIA_SPEED;
	}
	else
	{
		vy = V_SOPHIA_SPEED;
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
	//RenderBoundingBox();
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
			if (dynamic_cast<CPlayer*>(e->obj)) continue;
			float min = e->dx < e->dy ? e->dx : e->dy;
			if (min < deltaMin)
			{
				minEvent = e;
				deltaMin = min;
			}
		}
		bool createCollision = false;
		if (deltaMin >= 9999) return;
		if (minEvent)
		{
			if (dynamic_cast<EnemyBullet*>(minEvent->obj))
			{
				EnemyBullet* enemyBullet = dynamic_cast<EnemyBullet*>(minEvent->obj);
				if (enemyBullet->GetPower() > GetPower())
				{
					enemyBullet->ChangePower(GetPower());
					PrepareToRemove();
				}
				else if (enemyBullet->GetPower() < GetPower())
				{
					//enemyBullet->ChangePower(GetPower());
					enemyBullet->PrepareToRemove();
				}
				else
				{
					PrepareToRemove();
					enemyBullet->PrepareToRemove();
					createCollision = true;
				}
			}
			else
			{
				if (dynamic_cast<Enemy*>(minEvent->obj))
				{
					Enemy* enemy = dynamic_cast<Enemy*>(minEvent->obj);
					if (dynamic_cast<Mine*>(enemy))
					{
						dynamic_cast<Mine*>(enemy)->PrepareToRemove();
					}
					else
					{
						enemy->BeenShot(this);
					}
					createCollision = true;
				}
				if (dynamic_cast<CPortal*>(minEvent->obj) || dynamic_cast<CBrick*>(minEvent->obj))
				{
					createCollision = true;
				}
			}
		}

		if (createCollision)
		{
			PrepareToRemove();
			float left, top, right, bottom;
			minEvent->obj->GetBoundingBox(left, top, right, bottom);
			x += minEvent->t * dx + minEvent->nx * 0.1f;
			y += minEvent->t * dy + minEvent->ny * 0.1f;
			((Area2Scene*)CGame::GetInstance()->GetCurrentScene())->AddCollision(x, y);
		}
		else
		{
			x += dx;
			y += dy;
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
}