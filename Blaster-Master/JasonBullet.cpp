#include "JasonBullet.h"

#include "Enemy.h"
#include "Mine.h"
#include "Area2Scene.h"
#include "Player.h"
#include "EnemyBullet.h"
#include "Portal.h"
#include "Brick.h"

int JasonBullet::GetAniBullet()
{
	if (type == 0) {
		return 21;
	}
	else if (type == 1) {
		return 33;
	}
	else return 34;
}

JasonBullet::JasonBullet(int nx, int type)
{
	power = 1;
	this->nx = nx;
	this->type = type;
	animation_set = CAnimationSets::GetInstance()->Get(GetAniBullet());
	SetVx(nx*V_JASON_SPEED);
	SetVy(0);
}

void JasonBullet::Render()
{
	animation_set->at(0)->Render(x, y);
}

void JasonBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 4;
	bottom = y - 4;
}

void JasonBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (start_X == -1.0f)
	{
		start_X = x;
	}

	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;

		if (vx < 0 && start_X - x > 112 || vx > 0 && x - start_X > 112)
		{
			PrepareToRemove();
			((Area2Scene*)CGame::GetInstance()->GetCurrentScene())->AddCollision(x, y);
		}
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
			((Area2Scene*)CGame::GetInstance()->GetCurrentScene())->AddCollision(x, y);
		}
		else
		{
			x += dx;
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}